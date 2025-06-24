/**
 * @file jsonprotocol.hpp
 * @brief Json protocol implementation
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once

#include <jsoncpp/json/json.h>
#include "../iprotocol/iprotocol.hpp"


class JsonProtocol : public IProtocol
{
public:

    /**
     * @brief Serializes message to json
     * @param msg Message
     * @return std::any with Json::Value inside
     */
    std::any serialize(const Message& msg) override
    {
        uint64_t timestamp_minutes =
            std::chrono::duration_cast<std::chrono::minutes>(msg.send_time.time_since_epoch()).count();

        Json::Value root;

        root["sender"] = from_byteVector<std::string>(msg.sender);
        root["send_time"] = std::to_string(timestamp_minutes);
        root["data"] = from_byteVector<std::string>(msg.data);

        return root;
    }


    /**
     * @brief Deserializes message from json
     * @param input std::any with Json::Value inside
     * @return Message
     */
    Message deserialize(const std::any& input) override
    {
        Json::Value root = std::any_cast<Json::Value>(input);

        std::string sender = root["sender"].asString();
        std::string data = root["data"].asString();
        std::string timestamp_minutes = root["send_time"].asString();

        std::chrono::system_clock::time_point send_time { std::chrono::minutes(std::stoi(timestamp_minutes)) };

        Message msg
        {
            .sender = ByteVector(to_byteVector(sender)),
            .data = ByteVector(to_byteVector(data)),
            .send_time = send_time
        };

        return msg;
    }
};
