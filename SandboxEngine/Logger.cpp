#define _CRT_SECURE_NO_WARNINGS
#include "Logger.h"
#include "../SandboxEngine.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <Windows.h>
#include <DbgHelp.h>
#include <vector>

#undef Logger

//颜色相关
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define BOLDRED "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDYELLOW "\033[1m\033[33m"
#define BOLDBLUE "\033[1m\033[34m"
#define BOLDWHITE "\033[1m\033[37m"

Logger::Logger()
{
	logStream = std::ofstream("log.log", std::fstream::out);
	Log("Start Logger. Version Alpha 0.0.1.", "Logger");
}

Logger::~Logger()
{
	Log("Logger disposed.", "Logger");
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
	std::cout << "[" << prefix << "] ";
	setColor(msgColor);
	std::cout << msg << std::endl;
	setColor(LoggerColorNormal);
	logStream << "[" << formatTime << "]" << "[" << prefix << "] " << msg << std::endl;
}

void Logger::PrintBacktrace()
{
	const auto process = GetCurrentProcess();
	SymInitialize(process, nullptr, true);
	void* stack[100];
	const auto frames = CaptureStackBackTrace(0, 100, stack, nullptr);
	const auto symbol = static_cast<SYMBOL_INFO*>(calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1));
	symbol->MaxNameLen = 255;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	for (auto i = 0; i < frames; i++)
	{
		SymFromAddr(process, DWORD64(stack[i]), nullptr, symbol);
		IMAGEHLP_LINE64 lineInfo;
		DWORD displacement = 0;
		SymGetLineFromAddr64(process, symbol->Address, &displacement, &lineInfo);
		std::cout << "\tIn " << BOLDWHITE << symbol->Name << RESET << "\n\t\tAt line " << BOLDYELLOW << lineInfo.
			LineNumber << RESET << std::endl;
		logStream << "\tIn " << symbol->Name << "\n\t\tAt line " << lineInfo.LineNumber << std::endl;
	}
	free(symbol);
}
