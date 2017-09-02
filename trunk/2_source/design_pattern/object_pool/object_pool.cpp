#include "object_pool.h"

/*
 * 功能: 构造函数
 * 参数:
 *   [in]chunk_size: 预分配对象个数
 */ 
template<typename object>
ObjectPool<object>::ObjectPool(int chunk_size /*=DP_OBJECT_POOL_DEFAULT_CHUNK_SIZE*/): m_chunk_size(chunk_size)
{
   if(m_chunk_size>0)
   {
      allocate_chunk();//申请对象空间
   }
   else
   {
      throw std::invalid_argument("chunk_size must be positive!");
   }
}

/*
 * 功能: 预分配对象
 * 参数: 无
 * 返回值: 无
 * 备注:
 *    对象需要支持默认构造函数;
 */
template<typename object>
void ObjectPool<object>::allocate_chunk()
{
   object *new_objects = new object[m_chunk_size];
   m_all_objects.push_back(new_objects);
   for(int i=0; i<m_chunk_size; i++)
   {
     m_free_obj_deque.push_back(&new_objects[i]);
   }
}

/*
 * 功能: 删除new[]分配的数组
 * 参数:
 *    [in]obj:数组指针
 */ 
template<typename object>
void ObjectPool<object>::array_delete_object(object *obj)
{
   delete [] obj;
}

//析构函数
template<typename object>
ObjectPool<object>::~ObjectPool()
{
   for_each(m_all_objects.begin(), m_all_objects.end(), array_delete_object);
}

//功能: 获取一个空闲、未使用对象
template<typename object>
object& ObjectPool<object>::acquire_object()
{
   if(m_free_obj_deque.empty())
   {
      allocate_chunk();
   }
   object *obj=m_free_obj_deque.pop();
   return (*obj);
}

//功能: 将acquire_object返回的对象释放到对象池中
template<typename object>
void ObjectPool<object>::release_object(object & obj)
{
   m_free_obj_deque.push(&obj);
}

