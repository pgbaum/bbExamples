/*
Copyright (c) 2014, Peter G. Baum
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "gpio.h"
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <string>
#include <stdexcept>
#include <map>
#include <cstring>
#include <cassert>

#define SYSFS_GPIO_DIR "/sys/class/gpio/"

namespace
{
   struct Comp
   {
      bool operator()( const char *a, const char *b ) const
      {
         return strcmp( a, b ) < 0;
      }
   };

   const std::map<const char *,int, Comp> nameMap =
   {
      { "P8.3", 32 + 6 },
      { "P8.4", 32 + 7 },
      { "P8.5", 32 + 2 },
      { "P8.6", 32 + 3 },
      { "P8.7", 64 + 2 },
      { "P8.8", 64 + 3 },
      { "P8.9", 64 + 5 },
      { "P8.10", 64 + 4 },
      { "P8.11", 32 + 13 },
      { "P8.12", 32 + 12 },
      { "P8.13", 0 + 23 },
      { "P8.14", 0 + 26 },
      { "P8.15", 32 + 15 },
      { "P8.16", 32 + 14 },
      { "P8.17", 0 + 27 },
      { "P8.18", 64 + 1 },
      { "P8.19", 0 + 22 },
      { "P8.20", 32 + 31 },
      { "P8.21", 32 + 30 },
      { "P8.22", 32 + 5 },
      { "P8.23", 32 + 4 },
      { "P8.24", 32 + 1 },
      { "P8.25", 32 + 0 },
      { "P8.26", 32 + 29 },
      { "P8.27", 64 + 22 },
      { "P8.28", 64 + 24 },
      { "P8.29", 64 + 23 },
      { "P8.30", 64 + 25 },
      { "P8.31", 0 + 10 },
      { "P8.32", 0 + 11 },
      { "P8.33", 0 + 9 },
      { "P8.34", 64 + 17 },
      { "P8.35", 0 + 8 },
      { "P8.36", 64 + 16 },
      { "P8.37", 64 + 14 },
      { "P8.38", 64 + 15 },
      { "P8.39", 64 + 12 },
      { "P8.40", 64 + 13 },
      { "P8.41", 64 + 10 },
      { "P8.42", 64 + 11 },
      { "P8.43", 64 + 8 },
      { "P8.44", 64 + 9 },
      { "P8.45", 64 + 6 },
      { "P8.46", 64 + 7 },
      { "P9.11", 0 + 30 },
      { "P9.12", 32 + 28 },
      { "P9.13", 0 + 31 },
      { "P9.14", 32 + 18 },
      { "P9.15", 32 + 16 },
      { "P9.16", 32 + 19 },
      { "P9.17", 0 + 5 },
      { "P9.18", 0 + 4 },
      { "P9.19", 0 + 13 },
      { "P9.20", 0 + 12 },
      { "P9.21", 0 + 3 },
      { "P9.22", 0 + 2 },
      { "P9.23", 32 + 17 },
      { "P9.24", 0 + 15 },
      { "P9.25", 96 + 21 },
      { "P9.26", 0 + 14 },
      { "P9.27", 96 + 19 },
      { "P9.28", 96 + 17 },
      { "P9.29", 96 + 15 },
      { "P9.30", 96 + 16 },
      { "P9.31", 96 + 14 },
      // LEDs
      { "USR0", 32 + 21 },
      { "USR1", 32 + 22 },
      { "USR2", 32 + 23 },
      { "USR3", 32 + 24 },
   };

   int getNumberFromName( const char *name )
   {
      if( strncmp( name, "GPIO", 4 ) == 0 )
      {
         const int bank = atoi( name + 4 );
         const char *p = strchr( name, '_' );
         if( p == nullptr )
            throw std::invalid_argument( "Invalid GPIO name" );
         const int num = atoi( p + 1 );
         return bank * 32 + num;
      }
      auto p( nameMap.find( name ) );
      if( p == nameMap.end() )
         throw std::invalid_argument( "Invalid header name" );
      return p->second;
   }
}


GPIO::GPIO( int gpio_, int direction ) : gpio( gpio_ )
{
   int fd = open( SYSFS_GPIO_DIR "export", O_WRONLY );
   if( fd < 0 )
      throw std::invalid_argument( strerror( errno ) );
   std::string str = std::to_string( gpio );
   write( fd, str.c_str(), str.size() + 1 );
   ::close( fd );

   fd = open( ( std::string( SYSFS_GPIO_DIR "gpio" )
         + std::to_string( gpio ) + "/direction").c_str(), O_WRONLY );
   if( fd < 0 )
   {
      close();
      throw std::invalid_argument( strerror( errno ) );
   }
   switch( direction )
   {
      case LOW:  write( fd, "low", 4 ); break;
      case HIGH: write( fd, "high", 5 ); break;
      case IN:   write( fd, "in", 3 ); break;
      case OUT:  write( fd, "out", 4 ); break;
      default: throw std::invalid_argument( "GPIO direction" );
   }
   ::close( fd );
}

int GPIO::getNum( ) const
{
   return gpio;
}

void GPIO::close( )
{
   int fd = open( SYSFS_GPIO_DIR "unexport", O_WRONLY );
   std::string str = std::to_string( gpio );
   write( fd, str.c_str(), str.size() + 1 );
   ::close( fd );
}

GPIO::~GPIO( )
{
   try
   {
      close();
   }
   catch( ... )
   {
   }
}

GPO::GPO( int gpio_, bool val ) : gpio( gpio_, val ? GPIO::HIGH : GPIO::LOW )
{
   fd = open( ( std::string( SYSFS_GPIO_DIR "gpio"  )
         + std::to_string( gpio_ ) + "/value" ).c_str(), O_WRONLY );
   if( fd < 0 )
      throw std::invalid_argument( strerror( errno ) );
}

GPO::GPO( const char *name, bool val ) : GPO( getNumberFromName( name ), val )
{
}

GPO::~GPO( )
{
   if( fd > 0 )
      close();
}

void GPO::set( bool val )
{
   write( fd, val ? "1": "0", 2 );
}

void GPO::close( )
{
   ::close( fd );
   fd = 0;
   gpio.close();
}

GPI::GPI( int gpio_ ) : gpio( gpio_, GPIO::IN )
{
   fd = open( ( std::string( SYSFS_GPIO_DIR "gpio"  )
         + std::to_string( gpio_ ) + "/value" ).c_str(), O_RDONLY );
   if( fd < 0 )
      throw std::invalid_argument( strerror( errno ) );
}

GPI::GPI( const char *name ) : GPI( getNumberFromName( name ) )
{
}

GPI::~GPI( )
{
   if( fd > 0 )
      close();
}

void GPI::setEdge( int edge )
{
   const int ff = open( ( std::string( SYSFS_GPIO_DIR "gpio" )
         + std::to_string( gpio.getNum() ) + "/edge" ).c_str(), O_WRONLY );
   if( ff < 0 )
      throw std::invalid_argument( strerror( errno ) );
   switch( edge )
   {
      case NONE:    write( ff, "none", 5 ); break;
      case RISING:  write( ff, "rising", 7 ); break;
      case FALLING: write( ff, "falling", 8 ); break;
      case BOTH:    write( ff, "both", 5 ); break;
      default: ::close( ff );
               throw std::invalid_argument( "GPI::setEdge()" );
   }
   ::close( ff );
}

bool GPI::wait( )
{
   struct pollfd fdset[1];
   fdset[0].fd = fd;
   fdset[0].events = POLLPRI;

   switch( poll( fdset, 1, -1 ) )
   {
      case 1:  assert( fdset[0].revents & POLLPRI );
               return get();
      default:
               throw std::runtime_error( "poll failed" );
   }
}

bool GPI::get( )
{
   char buf;
   if( lseek( fd, 0, SEEK_SET ) != 0
         || read( fd, &buf, 1 ) != 1 )
      throw std::invalid_argument( strerror( errno ) );
   return buf == '1';
}

void GPI::close( )
{
   ::close( fd );
   fd = 0;
   gpio.close();
}
