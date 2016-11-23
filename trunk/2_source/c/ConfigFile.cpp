/**
    配置文件类

**/

#include "common.h"
#include "ConfigFile.h"

#include <string.h>

//#include "Func.h"

char g_comment_str[4]="//"; //define comment flag

//find the first non-blank char, then return the pointer,NULL-
inline char *find_non_blank(char *buffer, int buffer_len)
{
    if( (NULL==buffer) || (buffer_len<=0) ) return NULL;

    //char *ptr_str=buffer;
    //while( (*ptr_str!=0) && (ptr_str<(buffer+buffer_len)) )
    //{
    //    if((' '!=*ptr_str) || ('\t'!=*ptr_str))
    //        return ptr_str;
    //    ++ptr_str;
    //}
    //return NULL;

    int num=strspn(buffer, " \t");
    if(num>=buffer_len) return NULL;
    return buffer+num;
}

inline char *rfind_non_blank(char *buffer, int buffer_len)
{
    if((NULL==buffer)||(buffer_len<=0)) return NULL;
    char *ptr_str=buffer+buffer_len-1;
    while( (is_blank(*ptr_str)) && ((--ptr_str)>=buffer));

    if(ptr_str<buffer) return NULL;
    return ptr_str;
}

// check if the data is comment
int is_comment(char *buffer, int buffer_len)
{
    if((NULL==buffer) || (buffer_len<0))
        return 0;
    //find the first non-blank char
    char *ptr_str=find_non_blank(buffer, buffer_len);
    if(NULL == ptr_str) return 0;

    if(0==strncmp(ptr_str, g_comment_str, strlen(g_comment_str)))
        return 1;
    else
        return 0;
}

int is_section(char *buffer, int buffer_len,
               char *sec_buff=NULL, char sec_len=0)
{
    if( (NULL==buffer) || (buffer_len<=0) ) return 0;

    char *beg_ptr_str=find_non_blank(buffer, buffer_len);
    if( (NULL==beg_ptr_str) || ('['!=*beg_ptr_str) ) return 0;

    char *end_ptr_str=rfind_non_blank(buffer, buffer_len);
    if( (NULL==end_ptr_str) || (']'!=*end_ptr_str) ) return 0;

    if(end_ptr_str+1-beg_ptr_str<=2) //no section name
        return 0;
    
    if(NULL != sec_buff)
    {
        int len = end_ptr_str-beg_ptr_str-2;
        len=(len>sec_len) ? sec_len : len;
        strncpy(sec_buff, beg_ptr_str+1, len);
        trim(sec_buff);
    }

    return 1;    
}

int split_profile_value(char *buffer, int buffer_len,
                        char *key_buff, int key_len,
                        char *value_buff, int value_len,
                        char *comment_buff=NULL, int comment_len=0)
{
    if(NULL!=key_buff)     *key_buff=0;
    if(NULL!=value_buff)   *value_buff=0;
    if(NULL!=comment_buff) *comment_buff=0;

    char *key_ptr=find_non_blank(buffer, buffer_len);
    char *split_ptr=strchr(key_ptr, '=');
    char *comment_ptr=strstr(key_ptr, g_comment_str);

    //no key,then return error
    if((NULL==key_ptr) || (split_ptr==key_ptr))
        return -1;
    else if(comment_ptr<=split_ptr)
        return -2;

    int len=0;
    //get key
    if(NULL==split_ptr)//no split char, may be only have key_name
    {
        if(NULL != comment_ptr)//have comemnt
            len = comment_ptr-key_ptr;
        else //no comment
            len = buffer+buffer_len-key_ptr;
    }
    else // have split char
        len = split_ptr-key_ptr;
    len = (len>key_len) ? key_len : len;
    strncpy(key_buff, key_ptr, len);
    *(key_buff+len)=0;

    trim(key_buff);
    if(strlen(key_buff)<=0)
        return -3;

    //get value
    if(NULL==split_ptr) //no value
        return 0;
    if(NULL!=comment_ptr) //have comment
        len=comment_ptr-split_ptr-1;
    else   //no comment
        len = buffer+buffer_len-split_ptr-1;
    len = (len>value_len) ? value_len : len;
    strncpy(value_buff, split_ptr+1, len);
    *(value_buff+len)=0;
    trim(value_buff);

    //get comment
    if(NULL != comment_buff)
    {
        len = buffer+buffer_len-comment_ptr;
        len = (len>comment_len) ? comment_len : len;
        strncpy(comment_buff, comment_ptr, len);
        *(comment_buff+len)=0;
    }
    return 0;
    
}

//////////////////////////////////////////////////////////////////////////
// CConfigFile类实现

// -----------------------------------------------------------------------
ConfigFile::ConfigFile()
{
  m_file_stream=NULL;
}

// -----------------------------------------------------------------------
ConfigFile::ConfigFile(const char *filename)
{
  ConfigFile();
  load_cfg_file(filename);
}

// -----------------------------------------------------------------------
ConfigFile::~ConfigFile()
{
   if(NULL!=m_file_stream)
   {
     fclose(m_file_stream);
     m_file_stream=NULL;
   }

}

// -----------------------------------------------------------------------
int ConfigFile::load_cfg_file(const char *filename)
{
	if (filename == NULL || *filename == '\0')
		return -1;

        if(NULL!=m_file_stream)
        {
            fclose(m_file_stream);
            m_file_stream=NULL;
        }
	FILE *pFile = fopen(filename, "rb");
        if(NULL==pFile)
           return -2;

        m_file_stream=pFile;
	
	return 0;
}


// -----------------------------------------------------------------------
char* ConfigFile::read_profile_string(const char *section_str, char *key_str, char *value_buf, int value_len)
{
    if( (NULL==section_str) || (strlen(section_str)<=0) )// no section name, then return;
        return NULL;
    if( (NULL==key_str) || (strlen(key_str)<=0)) //no key
        return NULL;
    if(NULL!=value_buf) *value_buf=0;
    
    FILE *pFileStream=NULL;

    if(NULL==pFileStream)
        return NULL;

    fseek(pFileStream, 0, SEEK_SET);//start the begining of file

    char section_name[MAX_INI_SECTION_NAME_LEN];
    char key_name[MAX_INI_KEY_NAME_LEN];
    char opt_value[MAX_INI_VALUE_LEN];

    char buff_line[MAX_INI_LINE_LEN];
    bool sec_flag=false;
    while(fgets(buff_line, sizeof(buff_line), pFileStream)!=NULL)
    {
        trim_right(buff_line, '\n');
        trim_right(buff_line, '\r');
        trim(buff_line);

        
        if(0==is_comment(buff_line, strlen(buff_line)))
            continue;

        //find the section specified by parameter {section_str}
        memset(section_name, 0, sizeof(section_name));
        if(0!=is_section(buff_line, strlen(buff_line), section_name, sizeof(section_name)-1))
        {
            if(0==strcmp(section_name, section_str))
            {
                sec_flag=true;                   
            }
            else if(sec_flag)
                break;
          
            continue;
        }

        if(!sec_flag)
            continue;

        memset(key_name, 0, sizeof(key_name));
        memset(opt_value, 0, sizeof(opt_value));
        if(split_profile_value(buff_line, strlen(buff_line),
                               key_name, sizeof(key_name)-1,
                               opt_value, sizeof(opt_value)-1,
                               NULL, 0)<0)
            continue;

        if(0!=strcmp(key_name, key_str))
            continue;

        int len=strlen(opt_value);
        len = (len>value_len) ? value_len : len;
        strncpy(value_buf, opt_value, len);
        *(value_buf+len)=0;
        return value_buf;
    }

    return NULL;
}
