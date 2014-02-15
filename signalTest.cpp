#include "signal.h"
#include <iostream>

void func( Signal *sig, char a )
{
   for( ;; )
   {
      // std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
      std::cout << a;
      std::cout.flush();
      if( sig->wait( std::chrono::milliseconds( 500 ) ) )
         break;
   }
   std::cout << "End " << a << " thread\n";
}

void func2( Signal *sig, char a )
{
   while( !sig->isSignaled() )
   {
      std::cout << a;
      std::cout.flush();
      std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );
   }
   std::cout << "End " << a << " thread\n";
}

int main( void )
{
   Signal sig;
   std::cout << "Hello World\n";

   std::thread t1{ func, &sig, 'a' };
   std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );
   std::thread t2{ func, &sig, 'b' };
   std::thread t3{ func2, &sig, 'c' };

   std::this_thread::sleep_for( std::chrono::milliseconds( 5000 ) );
   sig.signal();

   t1.join();
   t2.join();
   t3.join();
   std::cout << "Exit\n";
}
