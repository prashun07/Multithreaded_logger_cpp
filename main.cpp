#include<iostream>
#include<fstream>
#include<string>
#include<thread>
#include <unistd.h>
//user defined headers
#include"logger.h"
#include "test_logger.h"
#define MAX_SIZE 5


void threadFun(logger &logger)
{
    for(int ind=0;ind<MAX_SIZE;ind++)
    {
        std::stringstream ss;
        ss << std::this_thread::get_id();
        logger.log(loglevel::DEBUG , "Message from thread " + ss.str());  
    }
}

int main()
{  logger logger("run_log.txt"); //logger object
    test_logger test;

    std::thread t1(threadFun, std::ref(logger)); //thread write to log file
    sleep(1);
    std::thread t2(&test_logger::read_logger_message, &test); //thread read from log file
    
    t1.join();
    t2.join();

    return 0;
}