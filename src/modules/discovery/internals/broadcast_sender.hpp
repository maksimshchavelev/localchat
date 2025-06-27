/**
 * @file broadcast_sender.hpp
 * @brief Class to send broadcast requests to 255.255.255.255
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include <chrono>
#include <thread>
#include <AlexandreRouma-net/net.h>


/**
 * @brief Class to send broadcast requests to 255.255.255.255
 */
class BroadcastSender
{
public:
    /**
     * @brief BroadcastSender constructor
     * @param interval Interval between requests
     */
    BroadcastSender(std::chrono::seconds interval = std::chrono::seconds(1));


    /**
     * @brief Run async sending broadcast messages
     * @note Can be runned only once.
     * @throw std::runtime error when trying to run again or a socket error
     */
    void run_async();

private:
    std::chrono::seconds interval_;
};
