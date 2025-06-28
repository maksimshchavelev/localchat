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


