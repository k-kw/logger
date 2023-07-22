#pragma once

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

class Logger {
private:
    std::string logfile;
    std::string logdir;
    std::chrono::high_resolution_clock::time_point time_1;
    std::chrono::high_resolution_clock::time_point time_2;

public:
    Logger(const std::string& logdir, const std::string& logfile);
    void set_logfile(const std::string& logfile);
    void set_logdir(const std::string& logdir);
    void logtext(const std::string& message);
    template <typename T>
    void lognumber(const std::string& prefix, T number, const std::string& suffix, int precision);

    void set_time_1();
    void set_time_2();
    void loglaptime(const std::string& prefix, const std::string& suffix, int precision);
};

template <typename T>
void Logger::lognumber(const std::string& prefix, T number, const std::string& suffix, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << number;
    logtext(prefix + oss.str() + suffix);
}
