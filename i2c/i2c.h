#ifndef I2C_H_INCLUDED
#define I2C_H_INCLUDED

#include <cstdint>

class I2C
{
private:
   int dev;

   void registerClient( int addr );

public:
   // TODO: allow more than one device
   I2C( const char *device, int address );
   ~I2C( );
   void write1( uint8_t cmd,  uint8_t val )
   {
      write( cmd, &val, 1 );
   }
   void write( uint8_t cmd, uint8_t *p, int n );
};


#endif
