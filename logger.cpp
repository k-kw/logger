#include "logger.h"
#include <fstream>
#include <iostream>
#include <string>

std::string msg_prefix = "Logger: ";

Logger::Logger(const std::string& logdir, const std::string& logfile)
    : logfile(logfile), logdir(logdir) {}

void Logger::set_logfile(const std::string& logfile) {
    this->logfile = logfile;
}

void Logger::set_logdir(const std::string& logdir) {
    this->logdir = logdir;
}

void Logger::logtext(const std::string& message) {
    if (fp.is_open()) {
        fp << message;
    } else {
        fp.open(logdir + "/" + logfile, std::ios::app);
        if (!fp.is_open()){
            std::cout<< msg_prefix + "Log file can not be opend.\n";
        }else{
            fp << message;
            fp.close();
        }
    }
}

void Logger::set_time_1() {
    time_1 = std::chrono::high_resolution_clock::now();
}

void Logger::set_time_2() {
    time_2 = std::chrono::high_resolution_clock::now();
}

void Logger::loglaptime(const std::string& prefix, const std::string& suffix, int precision) {
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(time_2 - time_1).count();
    lognumber(prefix, duration, suffix, precision);
}

void Logger::openfp(){
    if (fp.is_open()){
        std::cout<< msg_prefix + "Log file is already opend.\n";
    }else{
        fp.open(logdir + "/" + logfile, std::ios::app);
        if (!fp.is_open()){
            std::cout<< msg_prefix + "Log file can not be opend.\n";
        }
    }
}

void Logger::closefp(){
    if (fp.is_open()){
        fp.close();
    }
    else{
        std::cout<< msg_prefix + "Log file is already closed.\n";
    }
}
