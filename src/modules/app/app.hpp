/**
 * @file app.hpp
 * @brief Main application module
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include <thread>
#include <condition_variable>
#include "../discovery/discovery.hpp"
#include "../transport/jsontransport/jsontransport.hpp"
#include "../discovery/discovery.hpp"
#include "../ui/ui.hpp"


/**
 * @brief Main application class (singleton)
 */
class App
{
public:
    /**
     * @brief Get app instance
     * @return `App&`
     */
    friend App& app();


    /**
     * @brief Run application
     */
    void run();


    /**
     * @brief Exit from application
     */
    void exit();


    /**
     * @brief Set username which will be displayed by users when receiving a message
     * @param username Username
     */
    void set_username(const std::string& username);


private:
    std::condition_variable cv_;
    std::mutex              mutex_;
    bool                    exit_request_;

    JsonProtocol            json_protocol_;
    JsonTransport           json_transport_;

    Discovery&              discovery_;

    UI                      ui_;

    std::string             username_;


    /**
     * @brief Handle incoming message
     * @param msg Message
     */
    void _incoming_message_handler(const Message& msg);



    /**
     * @brief Handle raw outcoming message from UI
     * @param msg `std::string` with message
     */
    void _outcoming_message_handler(const std::string& msg);



    /**
     * @brief Send message to everyone
     * @param msg Message
     */
    void _send_msg_to_everyone(const Message& msg);



    /**
     * @brief App default constructor
     */
    App();
};



/* friend function */
App& app();


