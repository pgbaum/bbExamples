#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

class GPIO
{
   int gpio;

public:
   enum { IN, OUT, LOW, HIGH };
   GPIO( int gpio_, int direction );
   ~GPIO( );
   void close( );
};

class GPO
{
   int fd;
   GPIO gpio;

public:
   GPO( int gpio_, bool val = false );
   GPO( const char *name, bool val = false );
   ~GPO( );
   void set( bool val = true );
   void close( );
};

class GPI
{
   int fd;
   GPIO gpio;

public:
   GPI( int gpio_ );
   GPI( const char *name );
   ~GPI( );
   bool get( );
   void close( );
};


#endif

