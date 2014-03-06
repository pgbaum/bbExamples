#ifndef LEDMATRIX_H_INCLUDED
#define LEDMATRIX_H_INCLUDED

#include "i2c.h"

class LedMatrix
{
public:
   static const int BUF_SIZE = 16;
   static const int GREEN = 1,
                    RED = 2,
                    YELLOW = GREEN|RED;

   LedMatrix( const char *dev, int address );
   ~LedMatrix();

   void switchOn( bool on );
   void setBrightness( int k );
   void setBlinkrate( int k );

   void clearBuffer();
   void setBuffer( const uint8_t *p );
   const uint8_t *getBuffer( ) const;
   void displayBuffer();
   void setDot( int x, int y, int color );
   void setSquare( int x0, int y0, int x1, int x2, int color );
   // return width of character
   int setChar( char c, int color );

   int getXResolution() const;
   int getDotWidth() const;

private:
   I2C i2c;
   uint8_t buffer[BUF_SIZE];
};

#endif
