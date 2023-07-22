#include "logger.h"
#include <fstream>
#include <iostream>

Logger::Logger(const std::string& logdir, const std::string& logfile)
    : logfile(logfile), logdir(logdir) {}

void Logger::set_logfile(const std::string& logfile) {
    this->logfile = logfile;
}

void Logger::set_logdir(const std::string& logdir) {
    this->logdir = logdir;
}

void Logger::logtext(const std::string& message) {
    std::ofstream file(logdir + "/" + logfile, std::ios::app);
    if (file.is_open()) {
        file << message;
        file.close();
    } else {
        std::cout << "Logger:: File can not be open.\n";
    }
}

void Logger::set_time_1() {
    time_1 = std::chrono::high_resolution_clock::now();
}

void Logger::set_time_2() {
    time_2 = std::chrono::high_resolution_clock::now();
}

void Logger::log_laptime(const std::string& prefix, const std::string& suffix, int precision) {
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(time_2 - time_1).count();
    logNumber(prefix, duration, suffix, precision);
}
