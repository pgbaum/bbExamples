#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

class GPIO
{
   int gpio;

public:
   enum { IN, OUT };
   GPIO( int gpio_, int direction );
   ~GPIO( );
   void close( );
};

class GPO
{
   int fd;
   GPIO gpio;

public:
   GPO( int gpio_ );
   GPO( const char *name );
   ~GPO( );
   void set( bool val = true );
   void close( );
};

#endif

