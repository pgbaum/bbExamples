#include <stdexcept>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include <cstdint>
#include <chrono>
#include <thread>

extern "C" {
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
}

class I2C
{
private:
   int dev;

   void registerClient( int addr )
   {
      if( ioctl( dev, I2C_SLAVE, addr ) < 0 )
      {
         throw std::invalid_argument( strerror( errno ) );
      }
   }

public:
   // TODO: allow more than one device
   I2C( const char *device, int address )
   {
      if( (dev = open( device, O_RDWR ) ) < 0)
         throw std::invalid_argument( 
               std::string( "I2C: Unable to open device: " )
               + strerror( errno ) );
      registerClient( address );
   }
   ~I2C( )
   {
      close( dev );
   }
   void write1( uint8_t cmd,  uint8_t val )
   {
      write( cmd, &val, 1 );
   }
   void write( uint8_t cmd, uint8_t *p, int n )
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
};


void doIt( )
{
   I2C i2c( "/dev/i2c-1", 0x70 );
   // turn oscillator on
   i2c.write1( 0x21, 0 );
   // turn blink off
   i2c.write1( 0x81, 0 );
   // set min brightness
   i2c.write1( 0xE0, 0 );


   // set pixel
   uint8_t allOff[16] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   uint8_t allRed[16] = {
      0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF };
   uint8_t allGreen[16] = {
      0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0 };
   uint8_t greenCross[16] = {
      0x81, 0, 0x42, 0, 0x24, 0, 0x18, 0, 0x18, 0, 0x24, 0, 0x42, 0, 0x81, 0 };

   i2c.write( 0, allRed, 16 );
   std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
   // turn blink on
   i2c.write1( 0x83, 0 );
   std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
   // turn blink off
   i2c.write1( 0x81, 0 );
   i2c.write( 0, allGreen, 16 );
   std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
   i2c.write( 0, allOff, 16 );
   std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
   i2c.write( 0, greenCross, 16 );
   std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
}

int main( int argc, char *argv[] )
{
   try
   {
      doIt( );
   }
   catch( const std::exception &e )
   {
      std::cerr << "Error: " << e.what() << '\n';
      return 1;
   }
   catch( ... )
   {
      std::cerr << "Unknown error\n";
      return 1;
   }
}
