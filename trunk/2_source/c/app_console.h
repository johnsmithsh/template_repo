#ifndef __APP_CONSOLE_H__
#define __APP_CONSOLE_H__

#define MC_SHOW       0 //
#defien MC_START      1
#define MC_STOP       2 //stop program
#define MC_UPDATE_CFG 3 //set ini config file
#define MC_LOG_LEVEL  4 //set log level,return old log level
typedef struct __st_mng_cmd
{
    int cmd_type;    
} ST_MANAGE_CMD;
class App_Console
{
 public:
    App_Console();
    ~App_Console();

 public:
    int start();
    int stop();

 private:
    //1-support receive manageCommand from socket; 0-NoSupport
    //default value: 0
    int m_is_use_sock_cmd;
    std::queue<ST_MANAGE_CMD> m_cmd_queue;//store management command
    /* this thread is for receive command from socket
       because of low usage frequency,so won't create a new class,a function can
       satified the requirement.
    */
    int start_thread_recv_cmd(int port=9090);
};

#endif

