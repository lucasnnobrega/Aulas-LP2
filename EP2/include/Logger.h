#ifndef ___LOGGERR___
#define ___LOGGERR___
#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <sstream>
#include "./ordered_mutex.h" 
class Logger{
	static std::string path;
	static Logger* instance;
	static ordered_mutex mut;
	static std::ofstream file;
	Logger(const char* path);
	public:
	static Logger& getInstance();
	static void start(const char* path);
	static void end();
	
	static void log(int signal, int id);
};
#endif
