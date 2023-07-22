#pragma once

#include <string>

class Logger {
private:
    std::string logfile;
    std::string logdir;

public:
    Logger(const std::string& logdir, const std::string& logfile);
    void set_logfile(const std::string& logfile);
    void set_logdir(const std::string& logdir);
    void logtext(const std::string& message);
};
