#pragma once

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <fstream>
// #include <filesystem>
#include <vector>

// namespace fs = std::filesystem;

class Logger {
private:
    std::string logfile;
    std::string logdir;
    std::chrono::high_resolution_clock::time_point time_1;
    std::chrono::high_resolution_clock::time_point time_2;
    std::ofstream fp;

public:
    // constructor
    Logger(const std::string& logdir, const std::string& logfile);
    // destructor
    ~Logger();

    // prohibition of copy constructor
    Logger(const Logger&)=delete;
    // prohibition of copy operator
    Logger& operator=(const Logger&)=delete;

    // allow of move constructor
    Logger(Logger&&)=default;
    // allow of move operator
    Logger& operator=(Logger&&)=default;

    void set_logfile(const std::string& logfile);
    void set_logdir(const std::string& logdir);

    // bool check_exist();
    std::string prepend_timestamp(const std::string& message);

    void logtext(const std::string& message, const bool timestamp_flg);
    void logtext(const std::string& message);
    template <typename T>
    void lognumber(const std::string& prefix, T number, const std::string& suffix, int precision);

    void set_time_1();
    void set_time_2();
    void loglaptime(const std::string& prefix, const std::string& suffix, int precision);

    template <class... Args>
    void logcsvformat(const Args&... msgs);

    void openfp();
    void closefp();
};

template <typename T>
void Logger::lognumber(const std::string& prefix, T number, const std::string& suffix, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << number;
    logtext(prefix + oss.str() + suffix);
}

template <class... Args>
void Logger::logcsvformat(const Args&... msgs){
    std::string tmp;
    std::initializer_list<std::string> inputs{msgs...};
    int list_pnt=0;
    for (auto msg : inputs){
        if (list_pnt >= inputs.size()-1) msg+="\n";
        else msg+=",";
        tmp+=msg;
        list_pnt++;
    }

    this->logtext(tmp);
}
