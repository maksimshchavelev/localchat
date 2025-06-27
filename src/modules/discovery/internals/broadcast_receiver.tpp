/**
 * @file broadcast_receiver.tpp
 * @brief template run_async implementation
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include "broadcast_receiver.hpp"


/* public method */
template <typename Callback>
void BroadcastReceiver::run_async(Callback&& callback) requires requires { callback(std::move(std::string()), std::move(net::Address())); }
{
    static bool running = false;

    if(running)
        throw std::runtime_error("void BroadcastReceiver::run_async() is already running!");

    running = true;
    std::thread runner([this, cb = std::forward<Callback>(callback)]()
    {
        auto socket = net::openudp(net::Address(), "0.0.0.0", 14570, true);

        while(true)
        {
            char msg[64];
            net::Address remote_address;
            int len = socket->recv(reinterpret_cast<uint8_t*>(msg), sizeof(msg)-1, false, 150, &remote_address);
            msg[len] = '\0';

            if(len <= 0) continue;

            /* if we received request from other device */
            if(local_interfaces_addresses_.find(remote_address.getIP()) == local_interfaces_addresses_.end())
            cb(msg, std::move(remote_address));
        }
    });

    runner.detach();
}
