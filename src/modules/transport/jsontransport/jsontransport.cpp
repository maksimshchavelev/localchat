/**
 * @file jsontransport.cpp
 * @brief Implementation of transport uses json protocol.
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */



#include "jsontransport.hpp"




/* public method */
JsonTransport::JsonTransport(const JsonProtocol &protocol) : protocol_(protocol) {}



/* public method */
void JsonTransport::run_server_async(
    std::function<void(decltype(std::declval<IProtocol>().deserialize(std::any())))> callback) const
{
    static bool running = false;

    if(running)
        throw std::runtime_error("void JsonTransport::run_server_async(...) is already running!");

    running = true;

    std::thread runner([this, &callback]()
    {
        auto listener = net::listen("0.0.0.0", Config::port);

        while(true)
        {
            net::Address clientAddress;
            auto client = listener->accept(&clientAddress);

            std::string data;

            if(client->recvline(data, 32768, 100) <= 0)
                continue; /* if error */

            auto deserialized_result = protocol_.deserialize(Json::Value(data));

            callback(deserialized_result);
        }
    });

    runner.detach();
}
