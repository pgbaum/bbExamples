#include <stdexcept>
#include <iostream>
#include <chrono>
#include <thread>

#include "i2c.h"
#include "ledMatrix.h"

void dotSteps( LedMatrix *m, int x, int y, int col )
{
   m->clearBuffer();
   m->setDot( x, y, col );
   m->displayBuffer();
   std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
}

void dotSquare( LedMatrix *m, int offset, int col )
{
   for( int x = offset; x < 8 - offset; ++x )
      dotSteps( m, x, offset, col );
   for( int y = offset + 1; y < 8 - offset; ++y )
      dotSteps( m, 7 - offset, y, col );
   for( int x = 6 - offset; x >= offset; --x )
      dotSteps( m, x, 7 - offset, col );
   for( int y = 6 - offset; y > offset; --y )
      dotSteps( m, offset, y, col );
}

void showHorse( LedMatrix *l )
{
   l->clearBuffer();
   // lawn
   l->setSquare( 0, 0, 7, 0, LedMatrix::GREEN );
   // shoes
   l->setDot( 2, 1, LedMatrix::RED );
   l->setDot( 5, 1, LedMatrix::RED );
   // legs
   l->setSquare( 2, 2, 2, 4, LedMatrix::YELLOW );
   l->setSquare( 5, 2, 5, 3, LedMatrix::YELLOW );
   // body
   l->setSquare( 3, 4, 5, 5, LedMatrix::YELLOW );
   // head
   l->setSquare( 0, 4, 0, 6, LedMatrix::YELLOW );
   l->setDot( 1, 5, LedMatrix::YELLOW );
   // tail
   l->setDot( 6, 5, LedMatrix::RED );
   l->setSquare( 7, 2, 7, 4, LedMatrix::RED );
   // mane
   l->setDot( 0, 7, LedMatrix::RED );
   l->setDot( 1, 6, LedMatrix::RED );
   l->setDot( 2, 5, LedMatrix::RED );
   l->displayBuffer();
}

void showCharacters( LedMatrix *l )
{
   for( char c = ' '; c <= '~'; ++c )
   {
      int color = LedMatrix::GREEN;
      switch( c % 3 )
      {
         case 0: color = LedMatrix::RED; break;
         case 1: color = LedMatrix::GREEN; break;
         case 2: color = LedMatrix::YELLOW; break;
      }
      l->clearBuffer();
      l->setChar( c, color );
      l->displayBuffer();
      std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
   }
}


void doIt( )
{
   LedMatrix ledMatrix( "/dev/i2c-1", 0x70 );

   showHorse( &ledMatrix );
   std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );

   // set pixel
   const uint8_t greenCross[LedMatrix::BUF_SIZE] = {
      0x81, 0, 0x42, 0, 0x24, 0, 0x18, 0, 0x18, 0, 0x24, 0, 0x42, 0, 0x81, 0 };

   ledMatrix.clearBuffer( );
   ledMatrix.setSquare( 0, 0, 7, 7, LedMatrix::RED );
   ledMatrix.displayBuffer();
   std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

   ledMatrix.clearBuffer( );
   ledMatrix.setSquare( 0, 0, 7, 7, LedMatrix::GREEN );
   ledMatrix.displayBuffer();
   std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

   ledMatrix.clearBuffer( );
   ledMatrix.setSquare( 0, 0, 7, 7, LedMatrix::YELLOW );
   ledMatrix.displayBuffer();
   for( int k = 1; k <= 15; ++k )
   {
      ledMatrix.setBrightness( k );
      std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
   }
   for( int k = 14; k >= 0; --k )
   {
      ledMatrix.setBrightness( k );
      std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
   }

   // turn blink on
   for( int k = 1; k <= 3; ++k )
   {
      ledMatrix.setBlinkrate( k );
      std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
      ledMatrix.setBlinkrate( 0 );
      std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
   }

   ledMatrix.clearBuffer( );
   ledMatrix.displayBuffer();
   std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
   ledMatrix.setBuffer( greenCross );
   ledMatrix.displayBuffer();
   std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

   showCharacters( &ledMatrix );

   dotSquare( &ledMatrix, 0, LedMatrix::GREEN );
   dotSquare( &ledMatrix, 1, LedMatrix::GREEN );
   dotSquare( &ledMatrix, 2, LedMatrix::GREEN );
   dotSquare( &ledMatrix, 3, LedMatrix::GREEN );

   dotSquare( &ledMatrix, 0, LedMatrix::RED );
   dotSquare( &ledMatrix, 1, LedMatrix::RED );
   dotSquare( &ledMatrix, 2, LedMatrix::RED );
   dotSquare( &ledMatrix, 3, LedMatrix::RED );

   dotSquare( &ledMatrix, 0, LedMatrix::YELLOW );
   dotSquare( &ledMatrix, 1, LedMatrix::YELLOW );
   dotSquare( &ledMatrix, 2, LedMatrix::YELLOW );
   dotSquare( &ledMatrix, 3, LedMatrix::YELLOW );
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
