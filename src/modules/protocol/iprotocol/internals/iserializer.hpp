/**
 * @file serializer.hpp
 * @brief Abstract Serializer class for Protocol module
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include <any>
#include "message.hpp"


/**
 * @name ISerializer
 * @brief The abstract ISerializer class to serialize messages
 */
class ISerializer
{
public:

    /**
     * @brief Serializes message
     * @param msg Message struct
     * @return std::any object with serialized message
     */
    virtual std::any serialize(const Message& msg) = 0;
};

