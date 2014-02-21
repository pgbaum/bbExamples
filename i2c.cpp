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

