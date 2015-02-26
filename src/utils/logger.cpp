#include <utils/logger.hpp>

namespace utils {
    logger log("log", fatal, true);

    logger::logger(std::string file, log_level filter, bool trunc) noexcept
    : filter_(filter) {
        if (trunc) {
            fstream_.open(file, std::ofstream::trunc);
        } else {
            fstream_.open(file, std::ofstream::app);
        }
        if (!fstream_.is_open()) {
            std::cout << "FATAL : No log file! Exit." << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    logger::~logger() {
        if (fstream_.is_open()) {
            fstream_.close();
        }
    }

    logger& logger::operator() (log_level level) noexcept {
        current_level_ = level;
        new_line_ = true;
        return *this;
    }

    logger& logger::operator<<(std::ostream& (*os_fun)(std::ostream&)) {
        os_fun(std::cout);
        os_fun(fstream_);
        if (current_level_ == fatal) {
            std::exit(EXIT_FAILURE);
        }
        return *this;
    }

    void logger::print_time(std::stringstream& stream) {
        std::time_t t = std::time(nullptr);
        std::tm* local = std::localtime(&t);
        stream << (local->tm_year + 1900) << "/";
        if (local->tm_mon < 10) {
            stream << "0";
        }
        stream << local->tm_mon << "/";
        if (local->tm_mday < 10) {
            stream << "0";
        }
        stream << local->tm_mday << " [";
        if (local->tm_hour < 10) {
            stream << "0";
        }
        stream << local->tm_hour << ":";
        if (local->tm_min < 10) {
            stream << "0";
        }
        stream << local->tm_min << ":";
        if (local->tm_sec < 10) {
            stream << "0";
        }
        stream << local->tm_sec << "] ";
    }

    void logger::print_level(std::stringstream& stream) {
        if (current_level_ == info) {
            stream << "INFO";
        } else if (current_level_ == debug) {
            stream << "DEBUG";
        } else if (current_level_ == warning) {
            stream << "WARNING";
        } else if (current_level_ == error) {
            stream << "ERROR";
        } else if (current_level_ == fatal) {
            stream << "FATAL";
        }
        stream << " : ";
    }
}