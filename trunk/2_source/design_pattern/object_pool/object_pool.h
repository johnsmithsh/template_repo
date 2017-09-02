#ifndef __MTRX_OBJECT_POOL_H__
#define  __MTRX_OBJECT_POOL_H__

/****************************************************************************
 * 
 * MtrxDesignPattern basic template
 * @brief
 * 说明:
 *    设计模式<模板>: 对象池 object pool
 *    该文件属于该设计模式的模板,具体使用时需要根据该文件做修改以符合需求; 
 *
 * @author Matrix
 * @email 
 * @version 0.0.0.1
 * @date 
 * @license GNU General Public License (GPL)
 *
 * @todo 多线程模式加锁问题;
 *
 * @note
 * --------------------------------------------------------------------------
 * Remark: Description
 *   
 * --------------------------------------------------------------------------
 * Change History:
 *   <date>  | <version> | <author> | <description>
 *   20170902  | 0.0.0.1 | Matrix   | create file
 ******************************************************************************/

//#include <queue>
#include <deque>
#include <vector>
#include <stdexcept>

//@def 默认预分配对象个数
#define DP_OBJECT_POOL_DEFAULT_CHUNK_SIZE  1024  //DP=design pattern


/**
 * @class ObjectPool object_pool.h
 * @brief 定义设计模式对象池的代码模板(object pool template)
 *
 * @note
 *   1. 未考虑到多线模式;
 *   2. 该类禁用拷贝构造函数与赋值操作符;
 *   3. 对象池中的对象是按引用获取和释放的, 而不是按照指针,这样可以避免客户通过指针管理或释放对象;
 *   4. 对象object需要支持默认构造函数(即不含参数的构造函数)和析构函数
 **/ 
template<typename object>
class ObjectPool
{
   private:
     //禁用拷贝构造函数
     ObjectPool(const ObjectPool<object> &obj);
     //禁用赋值操作符
     ObjectPool<object>& operator=(const ObjectPool<object> & obj);
   public:
     /*
      * @fn 函数名:ObjectPool
      * @brief
      * @author 
      * @param[in] chunk_size: 对象池预分配的对象的个数;
      * @return
      * @note
      * @remark
      * 
      * Change History
      *
      */
     ObjectPool(int chunk_size = DP_OBJECT_POOL_DEFAULT_CHUNK_SIZE);

     /*
      * @fn 函数名:~ObjectPool
      * @brief 析构函数,删除对象池中所有对象
      * @author
      * @return
      * @note
      * @remark
      *
      * Change History
      */
     virtual ~ObjectPool();
     
    
     /*
      * @fn      函数名:acquire_object
      * @brief   功能:返回空闲的对象供使用;
      * @param
      * @return  返回值:返回分配的空闲对象
      * @note    备注: 按引用获取和释放,而不是按指针,避免客户通过指针管理或释放对象;
      *    
      * @remark
      *
      * Change History
      */ 
     object& acquire_object();

     /*
      * @fn     函数名:release_object
      * @brief  功能: 将对象释放到对象池, 即释放acquire_object返回的对象(只是放入到空闲队列,并未真正回收内存)
      * @param[in] 参数: [in]obj: acquire_objec返回的对象
      * @return  返回值:无
      * @note    备注:无;
      */
     void release_object(object &obj);

   protected:
     void allocate_chunk();
     void free_chunk();
     void array_delete_object(object *obj);
   protected:
     std::deque<object *> m_free_obj_deque;//空闲对象队列
     std::vector<object *> m_all_objects;//所有已分配的对象(包括空闲对象和被使用对象)
     int m_chunk_size;//预分配的object数量(即变量m_all_objects存储的元素个数)
};

#endif
