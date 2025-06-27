/**
 * @file broadcast_sender.cpp
 * @brief Class to send broadcast requests to 255.255.255.255
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#include "broadcast_sender.hpp"



/* public method */
BroadcastSender::BroadcastSender(std::chrono::seconds interval) : interval_(interval) {}



/* public method */
void BroadcastSender::run_async()
{
    static bool running = false;

    if(running)
        throw std::runtime_error("void BroadcastSender::run_async() is already running!");

    running = true;
    std::thread runner([this]()
    {
        auto socket = net::openudp("255.255.255.255", 14570, "0.0.0.0", 0, true);

        while(true)
        {
            socket->sendstr("localchat");
            std::this_thread::sleep_for(interval_);
        }
    });

    runner.detach();
}
