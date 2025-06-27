/**
 * @file jsontransport.cpp
 * @brief Implementation of transport uses json protocol.
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */



#include "jsontransport.hpp"

#include <iostream>


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

            char buffer[32768];

            size_t received = client->recv(reinterpret_cast<uint8_t*>(buffer), sizeof(buffer), false, 100);
            if(received > 0)
                data = buffer;

            client->close();

            Json::Value value;
            JSONCPP_STRING err;

            Json::CharReaderBuilder builder;
            const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
            if (!reader->parse(data.c_str(), data.c_str() + data.size(), &value,
                               &err)) {
                continue;
            }

            auto deserialized_result = protocol_.deserialize(value);

            callback(deserialized_result);
        }
    });

    runner.detach();
}
