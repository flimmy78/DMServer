#include "DMLogManager.h"

DMLogManager::DMLogManager():_log_mask(0)
{
    init();
}

DMLogManager::~DMLogManager()
{
    
}

void DMLogManager::init()
{
    get_log_config(); 
    set_log_level();
}

void DMLogManager::get_log_config()
{
    _log_name = DMJsonCfg::instance()->GetItemString("service_info", "service_name");
    _log_level = DMJsonCfg::instance()->GetItemString("service_config", "log_level");
    _log_name.append(".log");
}

inline  void DMLogManager::open_log_file()
{
    _log_file = fopen(_log_name.c_str(), "a");
    if (nullptr == _log_file)
    {    
        return;
    }    
}

inline  void DMLogManager::close_log_file()
{
    fclose(_log_file);
}

void DMLogManager::set_log_level()
{
    if ("DEBUG" == _log_level)
    {
        _log_mask = 0x1111;
    }
    else if ("INFO" == _log_level)
    {
        _log_mask = 0x0111;
    }
    else if ("WARNING" == _log_level)
    {
        _log_mask = 0x0011;
    }
    else if ("ERROR" == _log_level)
    {
        _log_mask = 0x0001;
    }
}

void DMLogManager::print_log(const DM_CHAR* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    string log_info = fmt;
    log_info.append("\n");
    ACE_OS::vfprintf(stdout, log_info.c_str(), ap);  
    
    va_end (ap);
}

void DMLogManager::trace_log(string file, string func, DM_INT line, const DM_CHAR* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
   
    time_t sec_time = time(NULL);
    tm* t= localtime(&sec_time);
  
    ACE_OS::printf("[%d-%02d-%02d][%02d:%02d:%02d][DM_TRACE][%s][%s][%d]:",t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, file.c_str(), func.c_str(), line);    
    string log_info = fmt;
    log_info.append("\n");    
    ACE_OS::vfprintf(stdout, log_info.c_str(), ap);  

    va_end (ap);
}

void DMLogManager::write_log(DM_INT log_level, string file, string func, DM_INT line, const DM_CHAR* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    
    open_log_file();
    
    time_t sec_time = time(NULL);
    tm* t= localtime(&sec_time);
  
    switch (log_level)
    {
        case DM_DEBUG:
        {
            if (DM_DEBUG & _log_mask)
            {               
                ACE_OS::fprintf(_log_file, "[%d-%02d-%02d][%02d:%02d:%02d][DM_DEBUG][%s][%s][%d]:",t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, file.c_str(), func.c_str(), line);   
                string log_info = fmt;
                log_info.append("\n");                  
                ACE_OS::vfprintf(_log_file, log_info.c_str(), ap);  
            }            
            break;
        }
        case DM_INFO:
        {
            if (DM_INFO & _log_mask)
            {
                ACE_OS::fprintf(_log_file, "[%d-%02d-%02d][%02d:%02d:%02d][DM_INFO][%s][%s][%d]:",t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, file.c_str(), func.c_str(), line);     
                string log_info = fmt;
                log_info.append("\n");                  
                ACE_OS::vfprintf(_log_file, log_info.c_str(), ap);  
            }
            break;
        }
        case DM_WARNING:
        {
            if (DM_WARNING & _log_mask)
            {
                ACE_OS::fprintf(_log_file, "[%d-%02d-%02d][%02d:%02d:%02d][DM_WARNING][%s][%s][%d]:",t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, file.c_str(), func.c_str(), line);       
                string log_info = fmt;
                log_info.append("\n");                  
                ACE_OS::vfprintf(_log_file, log_info.c_str(), ap);  
            }
            break;
        }
        case DM_ERROR:
        {
            if (DM_ERROR & _log_mask)
            {
                ACE_OS::fprintf(_log_file, "[%d-%02d-%02d][%02d:%02d:%02d][DM_ERROR][%s][%s][%d]:",t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, file.c_str(), func.c_str(), line);  
                string log_info = fmt;
                log_info.append("\n");                  
                ACE_OS::vfprintf(_log_file, log_info.c_str(), ap);       
            }
            break;
        }
    }
    
    close_log_file();
    va_end (ap);
}

