#pragma once

#include <string>
#include <iomanip>

class Logger {
private:
    std::string logfile;
    std::string logdir;

public:
    Logger(const std::string& logdir, const std::string& logfile);
    void set_logfile(const std::string& logfile);
    void set_logdir(const std::string& logdir);
    void logtext(const std::string& message);
    template <typename T>
    void logNumber(const std::string& prefix, T number, const std::string& suffix, int precision);
};

// テンプレートメソッドの実装をヘッダファイルに記述
template <typename T>
void Logger::logNumber(const std::string& prefix, T number, const std::string& suffix, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << number;
    Logger::logtext(prefix + oss.str() + suffix);
};
