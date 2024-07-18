//
//  logger.h
//  CampEngine++
//
//  Created by Noah Campagne on 20/06/2024.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>
#include <map>

class Logger {
private:
    static std::map<std::string, Logger> loggers;
    
public:
    static Logger standard;
    static Logger CampEngine;
    std::string name;
    
    Logger();
    Logger(std::string name);
    
    static Logger* getLoggerByName(std::string name);
    void info(std::string msg);
    void warn(std::string msg);
    void error(std::string msg);
};

#endif
