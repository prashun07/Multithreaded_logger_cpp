#include<iostream>
#include<fstream>
#include<string>
#include<thread>
//user defined headers
#include"logger.h"
#include "test_logger.h"

void threadFun(logger &logger, int id)
{
    for(int ind=0;ind<5;ind++)
    {
        logger.log(loglevel::DEBUG , "Message from thread "+ std::to_string(id)+"\n");
        
    }
}

int main()
{  logger logger("run_log.txt"); //logger object
    test_logger test;

    std::thread t1(threadFun, std::ref(logger),1);
    //std::thread t2(threadFun, std::ref(logger)),2);
    std::thread t2(&test_logger::read_logger_message, &test);
    
    // test.set_message("This is test logging message\n");
    // // test.take_user_input();
    // logger.log(loglevel::INFO, test.get_message());
    // std::cout<<"\n\n\n*****************Log file message******************\n\n\n";
    // test.read_logger_message();

    t1.join();
    t2.join();

    return 0;
}