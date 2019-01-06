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

	/*
	 * ��ӡBacktrace
	 */
	void PrintBacktrace();
};

#define Logger Logger::GetLogger()
#define LogCrash(message) {Logger.Log(\
	(std::string(message) + "\n\tCrach in function " + __FUNCTION__ + " in file " + __FILE__ + " at line:" + std::to_string(__LINE__)).c_str(),\
	"CRASH",\
	LoggerColorNormal,\
	LoggerColorRed);\
	Logger.PrintBacktrace();\
	throw std::exception(message);} Logger

#define LogError(message) {Logger.Log(\
	(std::string(message) + "\n\tError in function " + __FUNCTION__ + " in file " + __FILE__ + " at line:" + std::to_string(__LINE__)).c_str(),\
	"Error",\
	LoggerColorNormal,\
	LoggerColorRed);\
	Logger.PrintBacktrace();\
	throw std::exception(message);} Logger

#define LogWarning(message) {Logger.Log(\
	(std::string(message) + "\n\tIn function " + __FUNCTION__ + " in file " + __FILE__ + " at line:" + std::to_string(__LINE__)).c_str(),\
	"Warning",\
	LoggerColorNormal,\
	LoggerColorYellow);\
	Logger.PrintBacktrace();} Logger

#define LogInfo(message) Logger.Log(message,"Info");

#define Assert(expression) if ((expression) == 0) {LogError((std::string("Failed when assert \"") + #expression + "\".").c_str());Logger.PrintBacktrace();}Logger
#define AssertEx(expression, reason) if ((expression) == 0) {LogError((std::string("Failed when assert \"") + #expression + "\".\n\t" + reason).c_str());Logger.PrintBacktrace();}Logger