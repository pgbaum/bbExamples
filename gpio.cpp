
#include "gpio.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <map>
#include <cstring>

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
   };

   int getNumberFromName( const char *name )
   {
      auto p( nameMap.find( name ) );
      if( p == nameMap.end() )
         throw std::invalid_argument( "Invalid GPO Name" );
      return p->second;
   }
}


void GPO::unexport( )
{
   const std::string path(  "/sys/class/gpio/" );
   std::fstream f( (path + "unexport" ).c_str(), std::ios_base::out );
   f << gpio;
   f.close();
}

GPO::GPO( int gpio_ ) : gpio( gpio_ )
{
   const std::string path(  "/sys/class/gpio/" );
   std::fstream f( (path + "export" ).c_str(), std::ios_base::out );
   f.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
   f << gpio;
   f.close();

   try
   {
      f.open( (path + "gpio" + std::to_string( gpio ) + "/direction").c_str(),
            std::ios_base::out );
      f << "out";
      f.close();
      fstr.open( (path + "gpio" + std::to_string( gpio ) + "/value").c_str(),
            std::ios_base::out );
      fstr.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
   }
   catch( ... )
   {
      unexport( );
      throw;
   }
}

GPO::GPO( const char *name ) : GPO( getNumberFromName( name ) )
{
}

GPO::~GPO( )
{
   if( fstr.is_open() )
      close();
}

void GPO::set( bool val )
{
   fstr << (int)val;
   fstr.flush();
}

void GPO::close( )
{
   fstr.close();
   unexport();
}
