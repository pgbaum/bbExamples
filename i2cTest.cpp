#include <stdexcept>
#include <iostream>
#include <chrono>
#include <thread>

#include "i2c.h"

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
