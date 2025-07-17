#include<iostream>
#include<fstream>
#include<string>
#include<chrono>
#include<ctime>
#include<iomanip>
#include<sstream>
#include<mutex>
#include<exception>


//logging levels
enum loglevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR
};
class logger
{
    public:
        logger(const std::string&filename) : log_file(filename ,std::ios::out | std::ios::trunc){}
        ~logger();
        std::string level_to_string(loglevel level);
        void log(loglevel level,std::string log_message);
        std::string current_timestamp();

    private:
    std::ofstream log_file;
    std::mutex mtx;
};
logger::~logger()
{
    if(log_file.is_open())
    {
        log_file.close();
    }
}
std::string logger:: current_timestamp()
{   using namespace std::chrono;
    auto now=system_clock::now();
    std::time_t time_now = system_clock::to_time_t(now);

    std::ostringstream oss;
    oss<<std::put_time(std::localtime(&time_now),"%H:%M:%S");
    return oss.str();
}
std::string logger:: level_to_string(loglevel level)
{
    switch(level){
        case DEBUG: return "DEBUG";
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}
void logger::log(loglevel level, std::string log_message)
{       
    std::lock_guard<std::mutex> lock(mtx); //automatically handles locking and unlocking
    try {
        log_file << "[" << current_timestamp() << "]"
                 << "[" << level_to_string(level) << "] " << log_message << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error while writing to file: " << e.what() << std::endl;
    }
}

