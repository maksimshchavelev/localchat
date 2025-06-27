/**
 * @file broadcast_receiver.hpp
 * @brief Class to receive broadcast requests
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include <thread>
#include <set>
#include <AlexandreRouma-net/net.h>


/**
 * @brief Class to receive broadcast requests
 */
class BroadcastReceiver
{
public:
    /**
     * @brief BroadcastReceiver constructor
     * @param local_interfaces_addresses All addresses of all local interfaces
     */
    BroadcastReceiver(const std::set<uint32_t>& local_interfaces_addresses);


    /**
     * @brief Run async listening
     * @note Can be runned only once.
     * @throw std::runtime error when trying to run again or a socket error
     * @tparam callback Callback
     * @tparam Callback Functor which is called upon receipt of the message
     *         and has `std::string&& message, net::Address&& sender` signature
     */
    template <typename Callback>
    void run_async(Callback&& callback)
        requires requires { callback(std::move(std::string()), std::move(net::Address())); };


private:
    std::set<uint32_t> local_interfaces_addresses_;
};


#include "broadcast_receiver.tpp"
