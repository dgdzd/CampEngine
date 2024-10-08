//
//  logger.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 20/06/2024.
//

#include <CampEngine/Utils/Logger.h>

std::map<std::string, Logger> Logger::loggers;
Logger Logger::standard = Logger("LOGGER");
Logger Logger::CampEngine = Logger("CampEngine++");

Logger::Logger() {}

Logger::Logger(std::string name) {
    this->name = name;
    loggers[name] = *this;
}

Logger* Logger::getLoggerByName(std::string name) {
    return &loggers[name];
}

void Logger::info(std::string msg) {
    auto t = std::time(nullptr);
    auto t_ = *std::localtime(&t);
    auto chartime = std::put_time(&t_, "%H:%M:%S");
    std::ostringstream oss;
    oss << chartime;
    
    std::cout << "["+oss.str()+"] ["+name+"/INFO]: "+msg+"\n";
}

void Logger::warn(std::string msg) {
    auto t = std::time(nullptr);
    auto t_ = *std::localtime(&t);
    auto chartime = std::put_time(&t_, "%H:%M:%S");
    std::ostringstream oss;
    oss << chartime;
    
    std::cout << "\x1b[33m["+oss.str()+"] ["+name+"/WARNING]: "+msg+"\x1b[0m\n";
}

void Logger::error(std::string msg) {
    auto t = std::time(nullptr);
    auto t_ = *std::localtime(&t);
    auto chartime = std::put_time(&t_, "%H:%M:%S");
    std::ostringstream oss;
    oss << chartime;
    
    std::cout << "\x1b[31m["+oss.str()+"] ["+name+"/ERROR]: "+msg+"\x1b[0m\n";
}
