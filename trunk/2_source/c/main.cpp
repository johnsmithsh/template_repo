/**
 * 文件:
 * 说明
 *   该文件提供一个应用程序开始的模板
 *   虽然编码程序入口简单，但想要编写好
 *   比较困难。
 *   一个优秀的程序入口需要考虑参数、配置、管理、资源、运维；
 *   而一个优秀的程序还需要考虑调试、日志、性能、监控.
 * 设计方案如下:
 *   1.创建一个全局变量,该变量保存命令行解析的参数.
 *   2.进入程序先解析命令行参数;
 *   3.main函数只负责处理命令行参数、运维、管理等.
 *   3.增加一个应用控制台app_console,只有进入该app_console才算进入到业务逻辑;
 * 作者:
 * 修改历史:
 *   
 **/

#include <stdio.h>

//程序版本信息,这些信息在构建时会发送变化
#define PROG_VERSION 1.0.0.1 //版本号
#define BUILD_VERSION 20160718 14:22:45 //构建日期
#define Module_Name  "Application Arcitecture Sample" //模块名      

struct Program_Config
{
   //进程锁 该锁保证在本操作系统内唯一;
   Process_Mutex m_proc_lock;

   //其他参数及默认配置
};

struct Program_Config g_proc_cfg;//程序配置信息;与业务关系无关;

App_Console g_app_console;//应用程序控制台;
int main(int argc, char **argv)
{
   //解析命令行参数

   //处理命令行参数(与具体业务无关的部分,与程序管理、运维、监控登功能有关)
   //运维命令从命令行/socket/事件通知等方式获取.
   //...
   
   //该程序是否只能启动一个实例,如果是，则获取进程锁,判断是否是否已经存在;
   //获取到锁,说明尚未运行，可以继续运行;
   if(!g_proc_cfg.m_proc_lock.try_lock())
   {
      printf("程序已经运行!\n");
      exit(0);
    }


   int rc=g_app_console.start();//该函数执行完成,说明程序即将退出;

   g_proc_cfg.m_proc_lock.unlock();//释放进程锁

   if(rc<0)
   {
      printf("Error:启动失败!rc=[%d]", rc);
      exit(1);
   }

   printf("服务运行完成,即将退出!\n");
   return 0;  
}


/**
 * 使用getopt()函数处理命令行参数
 * 适用范围: linux
 * 使用方式:
 *    int getopt( int argc, char *const argv[], const char *optstring)
 *  说明:
 *    字符串optstring可以下列元素:
 *    1.单个字符，表示选项，
 *    2.单个字符后接一个冒号：表示该选项后必须跟一个参数。参数紧跟在选项后或者以空格隔开。该参数的指针赋给optarg。
 *    3 单个字符后跟两个冒号，表示该选项后必须跟一个参数。参数必须紧跟在选项后不能以空格隔开。该参数的指针赋给optarg。（这个特性是GNU的扩张,注:也可能没有参数值
 *    4.注意的是默认情况下getopt会重新排列命令行参数的顺序，所以到最后所有不包含选项的命令行参数都排到最后。
 *    如getopt.exe -a ima -b host -ckeke -d haha, 都最后命令行参数的顺序是： -a -b host -ckeke -d ima haha
 *    5.W是getopt保留项,
 * 示例: getopt.ext -h -v -p 1024 -Wall
 **/
#include <getopt.h>
int cmd_para_opt(int argc, char **argv)
{
    int ch;
    while((ch=getopt(argc, argv,"hvp:W::"))!=-1)
    {
       switch(ch)
       {
          case 'h':
             printf("帮助信息\n");
             break;
          case 'v':
             printf("版本信息\n");
             break;
          case 'p':
             printf("该参数含有值,且与参数之间使用空格隔开,如-p port,参数值在全局变量optarg\n");
             break;
          case 'W': 
             printf("该参数与参数值之间没有空格分割,如-Wall,参数值见全局变量optarg\n");
             break;
          case '?':
             printf("解析到一个未知参数,见全局变量optopt\n");
             break;
          case ':'
             printf("漏掉一个可选字符\n");
             break;
          default:
             printf("不会执行到此处\n");
             break;
       }
    }

    return 0;

}

/**
 * 使用getopt_long()函数处理命令行参数
 *
 *
 **/
int cmd_para_optlong(int argc, char **argv)
{
}

/*
 *处理命令行参数
 */
int cmd_para_boost(int argc, char **argv)
{
}


