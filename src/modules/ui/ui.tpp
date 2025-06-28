/**
 * @file ui.tpp
 * @brief Implementation of template methods and functions
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include "ui.hpp"


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

