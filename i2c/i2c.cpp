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

#include "i2c.h"
#include <stdexcept>
#include <cstring>
#include <cerrno>
#include <cstdio>

extern "C" {
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
}

void I2C::registerClient( int addr )
{
   if( ioctl( dev, I2C_SLAVE, addr ) < 0 )
   {
      throw std::invalid_argument( strerror( errno ) );
   }
}

// TODO: allow more than one device
I2C::I2C( const char *device, int address )
{
   if( (dev = open( device, O_RDWR ) ) < 0)
      throw std::invalid_argument(
            std::string( "I2C: Unable to open device: " )
            + strerror( errno ) );
   registerClient( address );
}

I2C::~I2C( )
{
   close( dev );
}

void I2C::write( uint8_t cmd, uint8_t *p, int n )
{
   if( n > 32 )
      throw std::invalid_argument( "I2C: write max 32 byte allowed." );

   uint8_t buf[33];
   buf[0] = cmd;
   for( int k = 0; k < n; ++k )
      buf[k+1] = p[k];
   if( ::write( dev, buf, n + 1 ) != n + 1 )
      throw std::invalid_argument( "I2C: write failed" );
}

