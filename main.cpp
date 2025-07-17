#include<iostream>
#include<fstream>
#include<string>
#include<thread>
#include <unistd.h>
//user defined headers
#include"logger.h"
#include "test_logger.h"

void threadFun(logger &logger, int id)
{
    for(int ind=0;ind<5;ind++)
    {
        logger.log(loglevel::DEBUG , "Message from thread "+ std::to_string(id));
        
    }
}

int main()
{  logger logger("run_log.txt"); //logger object
    test_logger test;

    std::thread t1(threadFun, std::ref(logger),2); //thread write to log file
    sleep(1);
    std::thread t2(&test_logger::read_logger_message, &test); //thread read from log file
    
    t1.join();
    t2.join();

    return 0;
}