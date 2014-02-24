#include "ledMatrix.h"
#include <algorithm>
#include <utility>

/*
   This implements a bicolor matrix with
   Holtek HT16K33 controller
*/

namespace {
const size_t charTable[][5] {
   { 0x00,  0x00,  0x00,  0x00,  0x00, },  // 0x20, Space
   { 0x00,  0x00,  0x7d,  0x00,  0x00, },  // 0x21, !
   { 0x10,  0x60,  0x00,  0x10,  0x60, },  // 0x22, "
   { 0x14,  0x7f,  0x14,  0x7f,  0x14, },  // 0x23, #
   { 0x12,  0x2a,  0x7f,  0x2a,  0x24, },  // 0x24, $
   { 0x63,  0x64,  0x08,  0x13,  0x63, },  // 0x25, %
   { 0x06,  0x39,  0x45,  0x3a,  0x05, },  // 0x26, &
   { 0x00,  0x10,  0x60,  0x00,  0x00, },  // 0x27, '
   { 0x00,  0x1c,  0x22,  0x41,  0x00, },  // 0x28, (
   { 0x00,  0x41,  0x22,  0x1c,  0x00, },  // 0x29, )
   { 0x2a,  0x1c,  0x7f,  0x1c,  0x2a, },  // 0x2a, *
   { 0x08,  0x08,  0x3e,  0x08,  0x08, },  // 0x2b, +
   { 0x00,  0x01,  0x06,  0x00,  0x00, },  // 0x2c, ,
   { 0x08,  0x08,  0x08,  0x08,  0x08, },  // 0x2d, -
   { 0x00,  0x03,  0x03,  0x00,  0x00, },  // 0x2e, .
   { 0x03,  0x04,  0x08,  0x10,  0x60, },  // 0x2f, /
   { 0x3e,  0x45,  0x49,  0x51,  0x3e, },  // 0x30, 0
   { 0x00,  0x21,  0x7f,  0x01,  0x00, },  // 0x31, 1
   { 0x21,  0x43,  0x45,  0x49,  0x31, },  // 0x32, 2
   { 0x22,  0x41,  0x49,  0x49,  0x36, },  // 0x33, 3
   { 0x0c,  0x14,  0x24,  0x7f,  0x04, },  // 0x34, 4
   { 0x72,  0x51,  0x51,  0x51,  0x4e, },  // 0x35, 5
   { 0x1e,  0x29,  0x49,  0x49,  0x06, },  // 0x36, 6
   { 0x40,  0x47,  0x48,  0x50,  0x60, },  // 0x37, 7
   { 0x36,  0x49,  0x49,  0x49,  0x36, },  // 0x38, 8
   { 0x30,  0x49,  0x49,  0x4a,  0x3c, },  // 0x39, 9
   { 0x00,  0x36,  0x36,  0x00,  0x00, },  // 0x3a, :
   { 0x00,  0x35,  0x36,  0x00,  0x00, },  // 0x3b, ;
   { 0x08,  0x14,  0x22,  0x41,  0x00, },  // 0x3c, <
   { 0x14,  0x14,  0x14,  0x14,  0x14, },  // 0x3d, =
   { 0x00,  0x41,  0x22,  0x14,  0x08, },  // 0x3e, >
   { 0x20,  0x40,  0x45,  0x48,  0x30, },  // 0x3f, ?
   { 0x3e,  0x41,  0x5d,  0x55,  0x3d, },  // 0x40, @
   { 0x1f,  0x24,  0x44,  0x24,  0x1f, },  // 0x41, A
   { 0x7f,  0x49,  0x49,  0x49,  0x36, },  // 0x42, B
   { 0x3e,  0x41,  0x41,  0x41,  0x22, },  // 0x43, C
   { 0x41,  0x7f,  0x41,  0x41,  0x3e, },  // 0x44, D
   { 0x7f,  0x49,  0x49,  0x41,  0x41, },  // 0x45, E
   { 0x7f,  0x48,  0x48,  0x48,  0x48, },  // 0x46, F
   { 0x3e,  0x41,  0x41,  0x45,  0x27, },  // 0x37, G
   { 0x7f,  0x08,  0x08,  0x08,  0x7f, },  // 0x48, H
   { 0x00,  0x41,  0x7f,  0x41,  0x00, },  // 0x49, I
   { 0x42,  0x41,  0x41,  0x7e,  0x40, },  // 0x4a, J
   { 0x7f,  0x08,  0x14,  0x22,  0x41, },  // 0x4b, K
   { 0x7f,  0x01,  0x01,  0x01,  0x01, },  // 0x4c, L
   { 0x7f,  0x20,  0x10,  0x20,  0x7f, },  // 0x4d, M
   { 0x7f,  0x10,  0x08,  0x04,  0x7f, },  // 0x4e, N
   { 0x3e,  0x41,  0x41,  0x41,  0x3e, },  // 0x4f, O
   { 0x7f,  0x48,  0x48,  0x48,  0x30, },  // 0x50, P
   { 0x3e,  0x41,  0x45,  0x42,  0x3d, },  // 0x51, Q
   { 0x7f,  0x48,  0x4c,  0x4a,  0x31, },  // 0x52, R
   { 0x32,  0x49,  0x49,  0x49,  0x26, },  // 0x53, S
   { 0x40,  0x40,  0x7f,  0x40,  0x40, },  // 0x54, T
   { 0x7e,  0x01,  0x01,  0x01,  0x7e, },  // 0x55, U
   { 0x7c,  0x02,  0x01,  0x02,  0x7c, },  // 0x56, V
   { 0x7f,  0x02,  0x0c,  0x02,  0x7f, },  // 0x57, W
   { 0x63,  0x14,  0x08,  0x14,  0x63, },  // 0x58, X
   { 0x60,  0x10,  0x0f,  0x10,  0x60, },  // 0x59, Y
   { 0x43,  0x45,  0x49,  0x51,  0x61, },  // 0x5a, Z
   { 0x00,  0x7f,  0x41,  0x41,  0x00, },  // 0x5b, [
   { 0x60,  0x10,  0x08,  0x04,  0x03, },  // 0x5c, backslash
   { 0x00,  0x41,  0x41,  0x7f,  0x00, },  // 0x5d, ]
   { 0x10,  0x20,  0x40,  0x20,  0x10, },  // 0x5e, ^
   { 0x01,  0x01,  0x01,  0x01,  0x01, },  // 0x5f, _
   { 0x00,  0x00,  0x60,  0x10,  0x00, },  // 0x60, `
   { 0x06,  0x29,  0x29,  0x26,  0x1f, },  // 0x61, a
   { 0x7f,  0x09,  0x09,  0x06,  0x00, },  // 0x62, b
   { 0x06,  0x09,  0x09,  0x09,  0x00, },  // 0x63, c
   { 0x00,  0x06,  0x09,  0x09,  0x7f, },  // 0x64, d
   { 0x0e,  0x15,  0x15,  0x15,  0x0d, },  // 0x65, e
   { 0x08,  0x3f,  0x48,  0x40,  0x20, },  // 0x66, f
   { 0x30,  0x49,  0x49,  0x51,  0x3e, },  // 0x67, g
   { 0x7f,  0x04,  0x08,  0x08,  0x07, },  // 0x68, h
   { 0x00,  0x09,  0x2f,  0x01,  0x00, },  // 0x69, i
   { 0x02,  0x01,  0x11,  0x5e,  0x00, },  // 0x6a, j
   { 0x7f,  0x04,  0x0a,  0x11,  0x00, },  // 0x6b, k
   { 0x00,  0x40,  0x7f,  0x00,  0x00, },  // 0x6c, l
   { 0x0f,  0x10,  0x0c,  0x10,  0x0f, },  // 0x6d, m
   { 0x1f,  0x08,  0x10,  0x10,  0x0f, },  // 0x6e, n
   { 0x0e,  0x11,  0x11,  0x11,  0x0e, },  // 0x6f, o
   { 0x3f,  0x24,  0x24,  0x18,  0x00, },  // 0x70, p
   { 0x00,  0x18,  0x24,  0x24,  0x3f, },  // 0x71, q
   { 0x1f,  0x08,  0x10,  0x10,  0x08, },  // 0x72, r
   { 0x09,  0x15,  0x15,  0x15,  0x12, },  // 0x73, s
   { 0x10,  0x7e,  0x11,  0x01,  0x02, },  // 0x74, t
   { 0x1e,  0x01,  0x01,  0x02,  0x1f, },  // 0x75, u
   { 0x1c,  0x02,  0x01,  0x02,  0x1c, },  // 0x76, v
   { 0x1e,  0x01,  0x06,  0x01,  0x1e, },  // 0x77, w
   { 0x11,  0x0a,  0x04,  0x0a,  0x11, },  // 0x78, x
   { 0x32,  0x09,  0x09,  0x09,  0x3e, },  // 0x79, y
   { 0x11,  0x13,  0x15,  0x19,  0x11, },  // 0x7a, z
   { 0x08,  0x36,  0x41,  0x41,  0x00, },  // 0x7b, {
   { 0x00,  0x00,  0x77,  0x00,  0x00, },  // 0x7c, |
   { 0x00,  0x41,  0x41,  0x36,  0x08, },  // 0x7d, }
   { 0x04,  0x08,  0x04,  0x02,  0x04, },  // 0x7e, ~
};
}

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

void LedMatrix::setChar( char c, int color )
{
   if( c < 0x20 || c > 0x7E )
      throw std::invalid_argument( "0x20 <= char <= 0x7E" );
   if( color != RED )
      for( int k = 0; k < 5; ++k )
         buffer[k*2] = charTable[c-0x20][k];
   if( color != GREEN )
      for( int k = 0; k < 5; ++k )
         buffer[k*2+1] = charTable[c-0x20][k];

}
