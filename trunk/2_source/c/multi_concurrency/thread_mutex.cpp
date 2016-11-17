#include "thread_mutex.h"

#ifdef __STD_BOOST_MACRO__ //使用BOOST封装锁

//#include "boost/thread/mutex.hpp"

//boost::mutex Thread_Mutex::m_mutex;

void Thread_Mutex::lock()
{
    m_mutex.lock();
}

void Thread_Mutex::unlock()
{
    m_mutex.unlock();
}


#endif //end of __STD_BOOST_MACRO__
