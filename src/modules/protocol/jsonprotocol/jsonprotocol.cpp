/**
 * @file jsonprotocol.cpp
 * @brief Json protocol implementation
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#include "jsonprotocol.hpp"



std::any JsonProtocol::serialize(const Message& msg) const
{
    uint64_t timestamp_minutes =
        std::chrono::duration_cast<std::chrono::minutes>(msg.send_time.time_since_epoch()).count();

    Json::Value root;

    root["sender"] = from_byteVector<std::string>(msg.sender);
    root["send_time"] = std::to_string(timestamp_minutes);
    root["data"] = from_byteVector<std::string>(msg.data);

    return root;
}




Message JsonProtocol::deserialize(const std::any& input) const
{
    const Json::Value& root = std::any_cast<const Json::Value&>(input);

    std::string sender = root["sender"].asString();
    std::string data = root["data"].asString();
    std::string timestamp_minutes = root["send_time"].asString();

    std::chrono::system_clock::time_point send_time(std::chrono::minutes(std::stoll(timestamp_minutes)));

    Message msg
        {
            .sender = ByteVector(to_byteVector(sender)),
            .data = ByteVector(to_byteVector(data)),
            .send_time = send_time,
            .message_type = Message::Type::UNKNOWN
        };

    return msg;
}

