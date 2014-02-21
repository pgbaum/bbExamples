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
   void displayBuffer();
   void setDot( int x, int y, int color );

private:
   I2C i2c;
   uint8_t buffer[BUF_SIZE];
};

#endif
