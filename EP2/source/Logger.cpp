#include "../include/Logger.h"

std::string Logger::path;
std::ofstream Logger::file;
Logger* Logger::instance = nullptr;
ordered_mutex Logger::mut;

Logger::Logger(const char* path){
	Logger::file.open(path,std::ios_base::trunc);
	if(!Logger::file.is_open())
		throw std::runtime_error("Couldn't open especified file");	
}

void Logger::start(const char* path){
		Logger::instance = new Logger(path);
}

Logger& Logger::getInstance(){
		if(Logger::instance == nullptr){
			throw std::runtime_error("Logger not started");
		}
		else{
			return *Logger::instance;		
		}
}

void Logger::end(){
	Logger::getInstance().file.close();
}

void Logger::log(int signal, int id){
	mut.lock();
	std::stringstream stream;
	stream << "{ \"signal\": " << signal << ", \"id\": " << id << "}\n";
	Logger::getInstance().file << stream.str();
	mut.unlock();
}
