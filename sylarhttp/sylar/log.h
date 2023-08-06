#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__

#include<string>
#include<stdint.h>
#include<vector>
#include<memory>
#include <functional>
#include<list>
#include<sstream>
#include<map>
#include<time.h>
#include<string.h>
#include<fstream>
#include<sstream>
#include<stdarg.h>
#include<stdint.h>
#include<iostream>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include"util.h"
#include"singleten.h"

#define SYLAR_LOG_LEVEL(logger,level) \
    if(logger->getLevel()<=level) \
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger,level,__FILE__,__LINE__,0,sylar::GetThreadId(),sylar::GetFiberId(),time(0)))).getSS()

#define SYLAR_LOG_DEBUG(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::DEBUG)
#define SYLAR_LOG_INFO(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::INFO)
#define SYLAR_LOG_WARN(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::WARN)
#define SYLAR_LOG_ERROR(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::ERROR)
#define SYLAR_LOG_FATAL(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::FATAL)

#define SYLAR_LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if(logger->getLevel() <= level) \
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, sylar::GetThreadId(),\
                sylar::GetFiberId(), time(0)))).getEvent()->format(fmt, __VA_ARGS__)

#define SYLAR_LOG_FMT_DEBUG(logger, fmt, ...) SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::DEBUG, fmt, __VA_ARGS__)
#define SYLAR_LOG_FMT_INFO(logger, fmt, ...)  SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::INFO, fmt, __VA_ARGS__)
#define SYLAR_LOG_FMT_WARN(logger, fmt, ...)  SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::WARN, fmt, __VA_ARGS__)
#define SYLAR_LOG_FMT_ERROR(logger, fmt, ...) SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::ERROR, fmt, __VA_ARGS__)
#define SYLAR_LOG_FMT_FATAL(logger, fmt, ...) SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::FATAL, fmt, __VA_ARGS__)

#define SYLAR_LOG_ROOT() sylar::LoggerMgr::GetInstance()->getRoot()
#define SYLAR_LOG_NAME(name) sylar::LoggerMgr::GetInstance()->getLogger(name)

namespace sylar{

class Logger;
class LoggerManager;

class LogLevel{
public:

        //定义日志级别
    enum Level{
        UNKNOW=0,
        DEBUG=1,
        INFO=2,
        WARN=3,
        ERROR=4,
        FATAL=5
    };
    static const char* ToString(LogLevel::Level level);
    static LogLevel::Level FromString(const std::string& str);
};

//日志事件
class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(std::shared_ptr<Logger> logger,LogLevel::Level level, const char* file,int32_t line,uint32_t elapse,uint32_t thread_id,
                uint32_t fiber_id,uint64_t time);


    const char* getFile() const {return m_file;}
    int32_t getLine() const {return m_line;}
    uint32_t getElapse() const{return m_elapse;};
    uint32_t getThreadId() const {return m_threadId;}
    uint32_t getFiberId() const {return m_fiberId;}
    uint32_t getTime() const {return m_time;}
    std::string getContent() const {return m_ss.str();}
    std::shared_ptr<Logger>  getLogger() const {return m_logger;}
    LogLevel::Level getLevel() const {return m_level;}

    std::stringstream& getSS() {return m_ss;}
    void format(const char* fmt,...);
    void format(const char* fmt,va_list al);
private:
    const char* m_file=nullptr;//文件名
    int32_t m_line=0;//行号
    uint32_t m_elapse=0;//程序启动开始到现在的毫秒数
    uint32_t m_threadId=0;//线程id
    uint32_t m_fiberId=0;//协程id
    uint64_t m_time=0;//时间戳
    std::stringstream m_ss;//日志内容流

    std::shared_ptr<Logger> m_logger;//日志器
    LogLevel::Level m_level;//日志等级
};
//对日志事件进行封装
class LogEventWrap{
public:
    LogEventWrap(LogEvent::ptr e);
    ~LogEventWrap();
    LogEvent::ptr getEvent() const { return m_event;}
    std::stringstream& getSS();
private:
    LogEvent::ptr m_event;
};



//日志格式器可以将传入的日志格式进行解析，并可以和 LogEvent 指针结合将特定格式的日志信息输出到 stringstream 中，等待 LogEventWrap 析构的时候将日志信息写入到指定的 Appender 中。
//格式化输出
class LogFormatter{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string& pattern);

    std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
public:
    class FormatItem{
    //负责将解析后的模板，按照不同类型构建item类，并放入vector<> m_items中
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        
        virtual ~FormatItem(){}

        virtual void format(std::ostream& os,std::shared_ptr<Logger> logger,LogLevel::Level level, LogEvent::ptr event)=0;
    };
    void init();
    bool isError() const{return m_error;}

private:
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;
    bool m_error=false;
};

//日志输出地可以将日志信息输出到不同的位置。
//一个 Logger 可以有多个 Appender，LogAppender 有单独的日志级别，因此可以通过设置不同级别的 Appender 从而将日志输出到不同的位置。
//此外每一个 LogAppender 也都会有自己单独的日志格式，从而方便进行管理。还可以通过 scoket 套接字，将日志输出到服务器上。
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender(){}

    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level,LogEvent::ptr event)=0;

    void setFormatter(LogFormatter::ptr val){m_formatter=val;}
    LogFormatter::ptr getFormatter() const {return m_formatter;}
    LogLevel::Level getLevel() const {return m_level;}
    void setLevel(LogLevel::Level val) {m_level=val;}
protected:
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
};


//日志器每一个 Logger 类含有多个 LoggerAppender，可以通过指针把 Logger 类传递给 LogEvent 从而使日志事件能够获取 Logger 类的一些信息。
class Logger:public std::enable_shared_from_this<Logger>{
friend class LoggerManager;
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string& name="root");

    void log(LogLevel::Level level,LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    void clearAppenders();
    LogLevel::Level getLevel() const {return m_level;}
    void setLevel(LogLevel::Level val){m_level=val;}

    const std::string& getName() const {return m_name;}
    void setFormatter(LogFormatter::ptr val);
    void setFormatter(const std::string& val);

    LogFormatter::ptr getFormatter();
private:
    std::string m_name;//日志名称
    LogLevel::Level m_level;//日志的级别
    std::list<LogAppender::ptr> m_appenders;//Appender集合
    LogFormatter::ptr m_formatter;//格式化输出

    Logger::ptr m_root;
};

//输出到控制台的Appender
class StdoutLogAppender:public LogAppender{
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override;

private:
};

//输出到文件的Appender
class FileLogAppender:public LogAppender{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& filename);
    void log(Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override;
    bool reopen();//重新打开文件，打开成功返回true
    
private:
    std::string m_filename;
    std::ofstream m_filestream;
};

class LoggerManager
{
public:
    LoggerManager();
    Logger::ptr getLogger(const std::string& name);

    void init();
    Logger::ptr getRoot() const {return m_root;}
private:
    std::map<std::string,Logger::ptr> m_loggers;//所有的日志器
    Logger::ptr m_root;//默认有一个根日志器
};
typedef sylar::Singleton<LoggerManager> LoggerMgr;


}

#endif