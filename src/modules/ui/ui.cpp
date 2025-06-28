/**
 * @file ui.cpp
 * @brief User interface module
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#include "ui.hpp"



/* public ctor */
UI::UI() {}




/* public method */
void UI::print_incoming_message(const std::string& msg)
{
    std::lock_guard<std::mutex> lock(IO_mutex_);
    std::cout << msg << std::endl;
}




/* public method */
void UI::print_outcoming_message(const std::string &msg)
{
    std::lock_guard<std::mutex> lock(IO_mutex_);
    std::cout << msg << std::endl;
}




/* public method */
template<typename OutcomingMessageFunctor>
void UI::run_async(OutcomingMessageFunctor&& outcoming_msg_callback)
    requires requires { outcoming_msg_callback(std::declval<const std::string&>()); }
{
    static bool running = false;

    if(running)
        throw std::runtime_error("void UI::run_async(...) is already running!");

    running = true;

    std::thread runner([this, callback = std::forward<OutcomingMessageFunctor>(outcoming_msg_callback)]()
    {
        while(true)
        {
            std::string input;
            if(std::getline(std::cin, input))
            {
                /* send msg */
                callback(input);
            }
        }
    });

    runner.detach();
}
