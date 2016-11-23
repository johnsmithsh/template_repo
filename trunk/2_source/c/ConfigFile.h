/**
    ConfigFile.h
 ini

Author:

Revision History:

**/

#ifndef __CONFIGFILE_H__
#define __CONFIGFILE_H__

#include <string>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////
// ¿‡∂®“Â

#define MAX_INI_SECTION_NAME_LEN 256
#define MAX_INI_KEY_NAME_LEN     256
#define MAX_INI_VALUE_LEN   1024
#define MAX_INI_LINE_LEN  10240
class ConfigFile
{
  public:
    ConfigFile();
    ConfigFile(const char *filename);
    ~ConfigFile();

  public:
    int         read_string(const char *section_name, const char *key_name, char *value_buf, int value_len, char *default_value="");
    std::string read_string(const char *section_name, const char *key_name, char *default_value="");
    char   read_char(const char *section_name,   const char *key_name, char   default_value=0);
    int    read_int(const char *section_name,    const char *key_name, int    default_value=0);
    double read_double(const char *section_name, const char *key_name, double default_value=0.0);
  private:
    int load_cfg_file(const char *filename);
    char* read_profile_string(const char *section_str, char *key_str, char *value_buf, int value_len);
  private:
    char m_buf[4096];
    int m_err_code;

 private:
    FILE *m_file_stream;//
};

#endif //__CONFIGFILE_H__
