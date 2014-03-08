/*
Copyright (c) 2014, Peter G. Baum
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
