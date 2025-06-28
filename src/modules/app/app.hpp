/**
 * @file app.hpp
 * @brief Main application module
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include <thread>
#include "../discovery/discovery.hpp"
#include "../transport/jsontransport/jsontransport.hpp"


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


private:
    std::condition_variable cv_;
    std::mutex              mutex_;
    bool                    exit_request_;

    JsonProtocol            json_protocol_;
    JsonTransport           json_transport_;


    /**
     * @brief Handle incoming message
     * @param msg Message
     */
    void _incoming_message_handler(Message msg);




    /**
     * @brief App default constructor
     */
    App();
};



/* friend function */
App& app();


