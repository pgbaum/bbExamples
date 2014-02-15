#ifndef SIGNAL_H_INCLUDED
#define SIGNAL_H_INCLUDED

#include <thread>
#include <mutex>
#include <chrono>

class Signal
{
public:
   Signal( ) : signaled( false ) {}
   bool reset( )
   {
      std::lock_guard<std::mutex> lock( mtx );
      signaled = false;
   }
   bool isSignaled( )
   {
      std::lock_guard<std::mutex> lock( mtx );
      const bool ret = signaled;
      return ret;
   }
   void signal( )
   {
      std::lock_guard<std::mutex> lock( mtx );
      signaled = true;
      cond.notify_all();
   }

   bool wait( std::chrono::milliseconds d )
   {
      std::unique_lock<std::mutex> lock( mtx );
      cond.wait_for( lock, d, [this] { return signaled; } );
      return signaled;
   }

private:
   std::mutex mtx;
   std::condition_variable cond;
   bool signaled;
};

#endif

