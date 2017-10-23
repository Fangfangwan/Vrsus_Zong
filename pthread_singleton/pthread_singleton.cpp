#include <cstdio>
#include <cstdlib>    // atexit( void (*function_ptr)(void) );
#include <pthread.h>

/*

This is a thread-safe singleton implementation using pthread.
To compile: g++ singleton_template_mt.cpp -std=c++1x -lpthread

# pthread_once() ensures the function it takes in (here is init().) only 
executed once.

# Memory cleaning for singleton object:

  assign atexit() inside get_instance():
  Thus destructor() will be activated before the program's termination.

*/

template <class T>
class pthread_singleton {

public:

  // since C++11, disable the use of certain operator(s)
  /* constructor, destructor and copy constructor shall never be called
     if the object is a singleton */
  pthread_singleton() = delete;
  ~pthread_singleton() = delete;
  pthread_singleton(const pthread_singleton&) = delete;
  void operator=(const pthread_singleton&) = delete;

  /* static member function can be called WITHOUT declaring
     corresponding object */
  static T* get_instance() {

    pthread_once(&ctl, init);
    return data;
  }

private:

  // As a member function, in order to be passed into pthread_once(), it has
  // to be defined as 'static'
  static void init() { 

    printf("init()\n"); 
    data = new T(); 
    atexit( &destructor );        // specify our destructor here
  }

  static void destructor() { delete data; data = nullptr; }

  static pthread_once_t ctl;
  static T* data;
};

/* static variable(s) MUST BE initialized OUTSIDE OF class
   Include the following initialization code in the calling cpp file.
   
template<class T> 
pthread_once_t pthread_singleton<T>::ctl = PTHREAD_ONCE_INIT;

template<class T> 
T* pthread_singleton<T>::data = nullptr;
*/
