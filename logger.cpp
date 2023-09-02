#include "logger.h"
#include <fstream>
#include <iostream>
// #include <filesystem>
#include <string>
#include <ctime>

// namespace fs = std::filesystem;

std::string msg_prefix = "Logger: ";

Logger::Logger(const std::string& logdir, const std::string& logfile)
    : logfile(logfile), logdir(logdir) {}

Logger::~Logger(){
    // std::cout<<"Logger destructor\n";
    if (fp.is_open()) fp.close();
}

void Logger::set_logfile(const std::string& logfile) {
    this->logfile = logfile;
}

void Logger::set_logdir(const std::string& logdir) {
    this->logdir = logdir;
}

// bool Logger::check_exist(){
//     return fs::is_regular_file(logdir+"/"+logfile);
// }

std::string Logger::prepend_timestamp(const std::string& message){
    std::chrono::system_clock::time_point now_p=std::chrono::system_clock::now();
    std::time_t now_t=std::chrono::system_clock::to_time_t(now_p);
    std::string now_str=std::ctime(&now_t);
    now_str.resize(now_str.size()-1);
    std::string time_message=now_str+": "+message;
    return time_message;
}

void Logger::logtext(const std::string& message, const bool timestamp_flg) {
    std::string message_tmp;
    if (timestamp_flg) message_tmp=prepend_timestamp(message);
    else message_tmp=message;

    if (fp.is_open()) {
        fp << message_tmp;
    } else {
        fp.open(logdir + "/" + logfile, std::ios::app);
        if (!fp.is_open()){
            std::cout<< msg_prefix + "Log file can not be opend.\n";
        }else{
            fp << message_tmp;
            fp.close();
        }
    }
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
    if (fp.is_open()) fp.close();
    else std::cout<< msg_prefix + "Log file is already closed.\n";
}
