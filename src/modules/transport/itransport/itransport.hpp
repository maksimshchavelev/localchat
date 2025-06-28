/**
 * @file itransport.hpp
 * @brief Interface for ITransport
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once

#include <functional>
#include "../../protocol/iprotocol/iprotocol.hpp"


/** @name ITransport
 *  @brief Interface for Transport class
 */
class ITransport
{
public:

    /**
     * @brief Running server async to listeting ingoing messages
     * @param callback Callback which will be called upon receipt of a new message
     */
    virtual void run_receiving_messages_async(
        std::function<void(decltype(std::declval<IProtocol>().deserialize(std::any())))> callback) const = 0;


    /**
     * @brief Send text message to the new
     * @param host IPv4 address of host (receiver)
     * @param msg Message
     * @return `true` if success, `false` if fail
     */
    virtual bool send_message(const std::string& host, const Message& msg) const = 0;
};
