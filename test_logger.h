#include<iostream>
#include<fstream>
#include<string>

class test_logger{

    private:
    std::string message;
    public:
    std::string get_message();
    void set_message(std::string log_message);
    void take_user_input();
    void read_logger_message();
};
std::string test_logger::get_message()
{
    return message;
}
void test_logger::set_message(std::string log_message)
{
    this->message = log_message;
}

void test_logger:: take_user_input()
{
    std::cout<<"Please enter message to log: "<<std::endl;
    std::string user_input;
    //std::cin>>user_input; //stops at first space use getline instead
    std::getline(std::cin ,user_input);
    this->message+=user_input;
}
void test_logger::read_logger_message()
{
    std::ifstream file("run_log.txt"); //open to read;

    std::string line;
    if(file.is_open())
    {
        while(getline(file,line))
        {
            std::cout<<line<<std::endl;
        }
        file.close();
    }else {
        std::cout << "Error reading file\n";
    }
}
