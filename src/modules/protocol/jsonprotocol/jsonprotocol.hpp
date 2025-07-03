/**
 * @file jsonprotocol.hpp
 * @brief Json protocol implementation
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once

#include <json/json.h>
#include "../iprotocol/iprotocol.hpp"


class JsonProtocol : public IProtocol
{
public:

    /**
     * @brief Serializes message to json
     * @param msg Message
     * @return std::any with Json::Value inside
     * @note Message type is not serialized
     */
    std::any serialize(const Message& msg) const override;


    /**
     * @brief Deserializes message from json
     * @param input std::any with Json::Value inside
     * @return Message
     * @note Fill in the message type manually (incoming or outgoing)
     */
    Message deserialize(const std::any& input) const override;
};
