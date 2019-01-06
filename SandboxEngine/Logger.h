#pragma once
#include <fstream>
#include <string>

/*
 * ��ɫ��Ϣ
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
	 * ��ȡloggerʵ��
	 */
	static Logger& GetLogger()
	{
		static Logger logger;
		return logger;
	}

	/*
	 * ��ӡһ����־\n
	 * ����ʹ�ú�����ӡ��־
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