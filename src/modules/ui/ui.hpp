/**
 * @file ui.hpp
 * @brief User interface module
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include <thread>
#include <iostream>
#include <string>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>


/**
 * @brief The UI class
 */
class UI
{
public:
    UI();


    /**
     * @brief Run UI async without blocking parent thread
     * @notice Can be runned only once!
     * @param outcoming_msg_callback Callback with `const std::string&` arg which is called when sending a message
     */
    template <typename OutcomingMessageFunctor>
    void run_async(OutcomingMessageFunctor&& outcoming_msg_callback)
        requires requires { outcoming_msg_callback(std::declval<const std::string&>()); };


    /**
     * @brief Print incoming message.
     * @param msg Message
     * @param sender Sender username
     * @param time Send time
     */
    void print_incoming_message(const std::string& sender, const std::string& time, const std::string& msg);


    /**
     * @brief Print outcoming message
     * @param msg Formatted message string
     */
    void print_outcoming_message(const std::string& msg);



private:
    std::mutex IO_mutex_; /* mutex for blocking input-output */

    std::vector<ftxui::Element> messages_;
    std::shared_ptr<ftxui::ScreenInteractive> screen_;
};



#include "ui.tpp"



