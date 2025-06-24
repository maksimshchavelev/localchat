/**
 * @file deserializer.hpp
 * @brief Abstract Deserializer class for Protocol module
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include <any>
#include "message.hpp"


/**
 * @name IDeserializer
 * @brief The abstract IDeserializer class to deserialize messages
 */
class IDeserializer
{
public:

    /**
     * @brief Deserializes message
     * @param input std::any object with serialized message
     * @return Message object with deserialized message
     */
    virtual Message deserialize(const std::any& input) = 0;
};

