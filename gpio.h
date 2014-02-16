#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

#include <fstream>

class GPO
{
   std::fstream fstr;
   int gpio;

   void unexport( );
public:
   GPO( int gpio_ );
   GPO( const char *name );
   ~GPO( );
   void set( bool val = true );
   void close( );
};

#endif

