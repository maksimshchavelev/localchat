/**
 * @file discovery.hpp
 * @brief Class to discover other LocalChat users in local network
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */




#include "discovery.hpp"




/* public method */
Discovery &Discovery::get_instance() noexcept
{
    static Discovery discovery;
    return discovery;
}




/* public method */
std::vector<std::string> Discovery::get_clients_ip_addresses()
{
    std::vector<std::string> res;
    res.reserve(clients_.size());

    std::lock_guard<std::mutex> lock(clients_mutex_);

    for(auto& [ip, _] : clients_)
    {
        in_addr inaddr { .s_addr = ntohl(ip) };
        res.emplace_back(inet_ntoa(inaddr));
    }

    return res;
}




/* private method */
std::vector<netif::IF_ADDRS> Discovery::_get_ipv4_ifaddrses()
{
    std::vector<netif::IF_ADDRS> result;
    netif::IF_ADDRS addrs;

    /* AF_UNSPEC is an IPv4 and IPv6 addresses */
    if(netif::getAddresses(AF_UNSPEC, &addrs) == 0)
    {

    #if defined(__unix__)
        /* unix implementation */
        for(netif::IF_ADDRS current_ifaddr = addrs; current_ifaddr; current_ifaddr = current_ifaddr->ifa_next)
        {
            /* AF_INET is an IPv4 address */
            if(!current_ifaddr->ifa_addr || current_ifaddr->ifa_addr->sa_family != AF_INET)
                continue;
            /* else */
            result.push_back(current_ifaddr);
        }


    #elif defined(_WIN32) or defined(_WIN64)
        /* windows implementation */
    #else
        static_assert(false, "Unsupported platform")
    #endif
    } else {
        throw std::runtime_error("Error in function netif::getAddresses(AF_UNSPEC, &addrs)");
    }

    return result;
}





/* private method */
std::set<uint32_t> Discovery::_get_ipv4_binary_addresses()
{
    auto addrs = _get_ipv4_ifaddrses();
    std::set<uint32_t> result;

    for(auto* address : addrs)
    {
    #if defined(__unix)
        /* unix implementation */
        result.insert(ntohl(reinterpret_cast<sockaddr_in*>(address->ifa_addr)->sin_addr.s_addr));

    #elif defined(_WIN32) or defined(_WIN64)
        /* windows implementation */

    #else
        static_assert(false, "Unsupported platform")
    #endif
    }

    return result;
}





/* private method */
void Discovery::_run_clients_cleaner_async(std::chrono::seconds max_interval)
{
    static bool running = false;

    if(running)
        throw std::runtime_error("void Discovery::_clients_cleaner_async(...) is already running!");

    running = true;

    std::thread runner([this, max_interval]()
    {
        while (true)
        {
            auto sleep_time = std::chrono::duration_cast<std::chrono::milliseconds>(max_interval) / 5;
            std::this_thread::sleep_for(sleep_time);

            std::lock_guard<std::mutex> lock(clients_mutex_);

            auto now = std::chrono::steady_clock::now();

            for(auto it = clients_.begin(); it != clients_.end();)
            {
                if(now - it->second > max_interval)
                    it = clients_.erase(it);
                else
                    ++it;
            }
        }
    });

    runner.detach();
}





/* private method */
Discovery::Discovery() : broadcast_sender_(), broadcast_receiver_(_get_ipv4_binary_addresses())
{
    _run_clients_cleaner_async(std::chrono::seconds(5));

    broadcast_sender_.run_async();

    broadcast_receiver_.run_async([this](std::string&& msg, net::Address&& sender){
        std::lock_guard<std::mutex> lock(clients_mutex_);
        clients_[sender.getIP()] = std::chrono::steady_clock::now();
    });
}

