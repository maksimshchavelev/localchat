/**
 * @file discovery.hpp
 * @brief Class to discover other LocalChat users in local network
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include <unordered_map>
#include <set>
#include <vector>
#include <netif/NetIF.hpp>
#include "internals/broadcast_sender.hpp"
#include "internals/broadcast_receiver.hpp"


using namespace gmlc;


/**
 * @name Discovery
 * @brief The Discovery class to discover other LocalChat users in local network
 * @details The singleton class
 */
class Discovery
{
private:
    BroadcastSender    broadcast_sender_;
    BroadcastReceiver  broadcast_receiver_;

    /* Hashtable for storing the time of the last keep alive from each user */
    std::unordered_map<uint32_t, std::chrono::steady_clock::time_point> clients_;
    std::mutex clients_mutex_;


    Discovery();


    /**
     * @brief Get all IPv4 ifaddrses
     * @return `std::vector<ifaddrs*>`
     */
    std::vector<ifaddrs*> _get_ipv4_ifaddrses();



    /**
     * @brief Get all IPv4 binary addresses accross all interfaces
     * @return `std::vector<uint32_t>`
     */
    std::set<uint32_t> _get_ipv4_binary_addreses();



    /**
     * @brief Run async cleaning of clients from `clients_`
     * @param max_interval If during this time there were no keep alive messages from the user,
     *        he will be deleted
     * @notice Can be runned only once
     */
    void _run_clients_cleaner_async(std::chrono::seconds max_interval);



public:
    /**
     * @brief Get `Discovery` instance
     * @details Initializes Discovery object on the first call
     * @return Discovery instance
     */
    static Discovery& get_instance() noexcept;



    /**
     * @brief Get IP addresses of all clients in string format
     * @return `std::vector<std::string>`
     */
    std::vector<std::string> get_clients_ip_adresses();

};
