#pragma once
#include <fstream>
#include <string>

/*
 * 颜色信息
 */
enum LoggerColor
{
	LoggerColorNormal,
	LoggerColorRed, 
	LoggerColorYellow, 
	LoggerColorGreen,
	LoggerColorBlue
};

class Logger
{
	Logger();
	~Logger();
	std::ofstream logStream;

public:
	/*
	 * 获取logger实例
	 */
	static Logger& GetLogger()
	{
		static Logger logger;
		return logger;
	}

	/*
	 * 打印一行日志\n
	 * 建议使用宏来打印日志
	 */
	void Log(const char* prefix, const char* msg, LoggerColor prefixColor = LoggerColorNormal, LoggerColor msgColor = LoggerColorNormal);
};

#define Logger Logger::GetLogger()
#define LogCrash(message) Log(\
	(std::string(message) + "\n\tCrach in function " + __FUNCTION__ + " in file " + __FILE__ + " at line:" + std::to_string(__LINE__)).c_str(),\
	"CRASH",\
	LoggerColorNormal,\
	LoggerColorRed);\
	throw std::exception(message);

#define LogError(message) Log(\
	(std::string(message) + "\n\tError in function " + __FUNCTION__ + " in file " + __FILE__ + " at line:" + std::to_string(__LINE__)).c_str(),\
	"Error",\
	LoggerColorNormal,\
	LoggerColorRed);\
	throw std::exception(message);

#define LogWarning(message) Log(\
	(std::string(message) + "\n\tIn function " + __FUNCTION__ + " in file " + __FILE__ + " at line:" + std::to_string(__LINE__)).c_str(),\
	"Warning",\
	LoggerColorNormal,\
	LoggerColorYellow);

#define LogInfo(message) Log(message,"Info");