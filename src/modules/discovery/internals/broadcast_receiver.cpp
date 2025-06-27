/**
 * @file broadcast_receiver.cpp
 * @brief Class to receive broadcast requests
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#include "broadcast_receiver.hpp"


/* public method */
BroadcastReceiver::BroadcastReceiver(const std::set<uint32_t>& local_interfaces_addresses) :
    local_interfaces_addresses_(local_interfaces_addresses) {}


