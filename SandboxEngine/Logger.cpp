#define _CRT_SECURE_NO_WARNINGS
#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <chrono>

#undef Logger

//颜色相关
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define BOLDWHITE "\033[1m\033[37m"

Logger::Logger()
{
	logStream = std::ofstream("log.log", std::fstream::out);
}

Logger::~Logger()
{
	logStream.close();
}

void Logger::Log(const char* msg, const char* prefix, const LoggerColor msgColor, const LoggerColor prefixColor)
{
	const auto setColor = [](const LoggerColor color)
	{
		switch (color)
		{
		case LoggerColorNormal:
			std::cout << RESET;
			break;
		case LoggerColorRed:
			std::cout << RED;
			break;
		case LoggerColorYellow:
			std::cout << YELLOW;
			break;
		case LoggerColorGreen:
			std::cout << GREEN;
			break;
		case LoggerColorBlue:
			std::cout << BLUE;
			break;
		default:
			break;
		}
	};
	//获取时间
	const auto time = std::time(nullptr);
	const auto localTime = *std::localtime(&time);
	const auto formatTime = std::put_time(&localTime, "%c");

	std::cout << BOLDWHITE;
	std::cout << "[" << formatTime << "]";
	setColor(prefixColor);
	std::cout << "[" << prefix << "]";
	setColor(msgColor);
	std::cout << msg << std::endl;
	setColor(LoggerColorNormal);
	logStream << "[" << formatTime << "]" << "[" << prefix << "]" << msg << std::endl;
}
