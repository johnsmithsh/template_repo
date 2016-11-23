
#include "app_console.h"

#include <pthread.h> //编译需要 -lpthread

/**
  从socket获取管理命令
  命令格式: type:cmd_type:param
    type='1',单字节,表示命令采用用户友好方式;
    cmd_type: set_ini/get_ini #设置或获取配置文件
    show:info/version:显示服务消息
    log_level #日志级别
       0-全部; 2000-debug; 3000-info; 
       4000-warn; 6000-error; 8000-fatal;
  命令说明:
    每个命令及参数<=1024字节;
    
 */
int app_console::start_thread_recv_cmd(int port)
{
  pthread_t __self_thread; 
  if(pthread_create(&__self_thred, NULL, thread_function, NULL))
  {
     return -1;
  }

  int sockfd;
  struct sockaddr_in addr;
  int addr_len = sizeof(struct sockaddr_in);

  //建立socket
  if((sockfd=socket(AF_INET, SOCK_STREAM, 0)<0)
  {
     return -2;
  }

  memset(&addr, 0, sizeof(addr));
  add.sin_family = AF_INET;
  addr.sin_port = htons(port);
  adr.sin_addr.s_addr=htonl(INADDR_ANY);

  //绑定端口
  if(bind(sockfd, &addr, sizeof(addr)<0))
  {
     return -3;
  }

  if(listen(sockfd, 3)<0)//最多处理3个链接请求
  {
     return -4;
  }
 
  char recv_buf[10240];
  int recv_len=0;
  int conn_fd;
 
  char rsp_buff[1024];
  int rc;
  while(0==m_quit_flag)
  {
     if(conn_fd=accept(sockfd, &addr, &addr_len)<0)
       continue;

     //
     memset(data_buff, 0, sizeof(data_buff));
     recv_len=recv(conn_fd, recv_buff, sizeof(data_buff)-1, 0);
     if(recv_len<0)
     {
        continue;
     }
     
     rc=handle_data(conn_fd, recv_buff, recv_len, 
         rsp_buff, sizeof(rsp_buff)-1);//处理命令
     if(rc<0)//error
     {
        continue;
     }
     
     if(rc>0)//需要返回数据
     {
        int sum_count=0;
        int send_len=rc;
        while(sum_count<send_len)
        {
           rc=send(conn_fd, rsp_buff+send_count, send_len, 0);
           if(rc<0)//error
               break;
           sum_count +=rc;
           send_len   -=rc;    
        }
     }

    close(conn_fd);//关闭链接
  }

  m_quit_flag=1;

  return 0; 
}

int handle_data(int conn_fd, char *data_buff, int data_len, char *rsp_buff, int rsp_len)
{
  //转换数据结构
  
  //处理可以处理的命令,如获取配置信息、设置配置信息等
  
  //将不能处理的命令写入命令缓存队列,供对应的服务处理
  
  //返回处理结果
}
