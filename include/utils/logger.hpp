#ifndef __GDW_LOGGER_HPP__
#define __GDW_LOGGER_HPP__

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

namespace utils {
    enum log_level {
        info, debug, warning, error, fatal
    };
}

namespace utils {
    class logger {
    public:
        logger(std::string file = "log", log_level filter = fatal, bool trunc = false) noexcept;
        ~logger();

        logger(const logger& other) = delete;
        logger& operator=(const logger& other) = delete;

        logger(logger&& other) = delete;
        logger& operator=(logger&& other) = delete;

        auto filter() const noexcept {
            return filter_;
        }

        void filter(log_level filter) noexcept {
            filter_ = filter;
        }

        logger& operator()(log_level level) noexcept;
        logger& operator<<(std::ostream& (*os_fun)(std::ostream&));

        template <typename type>
        logger& operator<<(const type& object) {
            std::stringstream stream;
            if (filter_ >= current_level_) {
                if (new_line_) {
                    new_line_ = false;
                    print_time(stream);
                    print_level(stream);
                }
                stream << object;
                std::string out = stream.str();
                std::cout << out;
                fstream_ << out;
            }
            return *this;
        }

    private:
        void print_time(std::stringstream& stream);
        void print_level(std::stringstream& stream);

    private:
        std::ofstream fstream_;
        bool new_line_;
        log_level current_level_;
        log_level filter_;
    };
    extern logger log;
}

#endif