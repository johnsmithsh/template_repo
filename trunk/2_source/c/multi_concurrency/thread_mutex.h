#ifndef __THREAD_MUTEX_H_
#define __THREAD_MUTEX_H_

/**
 * 文件
 * 说明
 *    该文件定义线程锁，用以封装不同多线程库;
 *    此处目的不是为了定义一种新的锁机制，而是为了封装已有的线程库;
 *    不同的实现方式需要通过继承该类或直接实现该类接口。
 *    例如:在thread_mutex_boost.cpp中使用boost库结成或实现接口即可;
 *           thread_mutex_posix.cpp中使用posix标准库实现等;
 *    可通过同样的方式实现进程锁.
 * 作者:
 * 修改历史:
 * 格式: 时间 日期 修改人  注释
 *
 * */

//该类用于线程锁
//这只是一个接口
//实现方式有posix、boost等多种方式
class Thread_Mutex
{
   public:
      Thread_Mutex();
      ~Thread_Mutex();
   public:
     //加锁
     virtual void lock();
     //解锁
     virtual void unlock();
     //试图加锁
     virtual int try_lock(int milli_second=0);
};


//原理:类进入作用域申请，退出作用域释放；故可用来自动加锁与解锁
//该建议使用栈分配方式，不建议使用堆分配方式(即new)
class Auto_Thread_Mutex
{
   public:
      Auto_Thead_Mutex(Thead_Mutex *pMutex, int mill_second=0)
      {
          m_thread_lock=pMutex;
          m_thread_lock->lock();
      }
      ~Auto_Thread_Mutex()
      {
          m_thread_lock->unlock();
      }
      
      bool opertator ==(const Auto_Thread_Mutex &obj)
      {
         return this->m_thread_lock==obj.m_thread_lock;
      }
   private:
      Thread_Mutex *m_thread_lock;

   private://该函数禁止赋值与拷贝,禁止无参数构造
      //禁止无参数构造函数
      Auto_Thread_Mutex(){}
      //禁止拷贝构造
      Auto_Thread_Mutex &Auto_Thread_Mutex(const Auto_Thread_Mutex &obj) {}
      //禁止值拷贝
      Auto_Thread_Mutex & operator=(const Auto_Thread_Mutex &obj) {}
     
};

#endif
