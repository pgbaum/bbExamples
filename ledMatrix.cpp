#include "ledMatrix.h"
#include <algorithm>
#include <utility>

/*
   This implements a bicolor matrix with
   Holtek HT16K33 controller
*/

LedMatrix::LedMatrix( const char *dev, int address ) : i2c( dev, address )
{
   clearBuffer();
   switchOn( true );
   setBrightness( 0 );
}

LedMatrix::~LedMatrix( )
{
}

void LedMatrix::switchOn( bool on )
{
   // oscillator
   i2c.write1( 0x20 | on, 0 );
   // display
   i2c.write1( 0x80 | on, 0 );
}

void LedMatrix::setBrightness( int k )
{
   if( k < 0 || k > 15 )
      throw std::invalid_argument( "0 <= brightness <= 15" );
   i2c.write1( 0xE0 | k, 0 );
}

void LedMatrix::setBlinkrate( int k )
{
   if( k < 0 || k > 3 )
      throw std::invalid_argument( "0 <= blink rate <= 3" );
   i2c.write1( 0x81 | (k<<1), 0 );
}

void LedMatrix::clearBuffer()
{
   std::fill( buffer, buffer + BUF_SIZE, 0 );
}

void LedMatrix::setBuffer( const uint8_t *p )
{
   std::copy( p, p + BUF_SIZE, buffer );
}

void LedMatrix::displayBuffer()
{
   i2c.write( 0, buffer, BUF_SIZE );
}

void LedMatrix::setDot( int x, int y, int color )
{
   if( x < 0 || x > 7 || y < 0 || y > 7 )
      throw std::invalid_argument( "0 <= x,y < 7" );
   if( color < GREEN || color > YELLOW )
      throw std::invalid_argument( "1 <= color <= 3" );
   x *= 2;
   if( color == RED )
      ++x;
   buffer[x] |= 1 << y;
   if( color == YELLOW )
      buffer[x+1] |= 1 << y;
}

void LedMatrix::setSquare( int x0, int y0, int x1, int y1, int color )
{
   if( x0 > x1 )
      std::swap( x0, x1 );
   if( y0 > y1 )
      std::swap( y0, y1 );
   if( x0 < 0 || y0 < 0 || x1 > 7 || y1 > 7 )
      throw std::invalid_argument( "0 <= x,y < 7" );
   if( color < GREEN || color > YELLOW )
      throw std::invalid_argument( "1 <= color <= 3" );

   uint8_t val = 1 << y0;
   for( ++y0; y0 <= y1; ++y0 )
      val += 1 << y0;

   x0 *= 2;
   x1 = (x1 + 1 ) * 2;
   if( color == RED )
   {
      ++x0;
      ++x1;
   }

   for( uint8_t x = x0; x < x1; x += 2 )
      buffer[x] |= val;
   if( color == YELLOW )
      for( uint8_t x = x0 + 1; x < x1; x += 2 )
         buffer[x] |= val;
}
