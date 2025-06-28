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
    virtual void run_server_async(
        std::function<void(decltype(std::declval<IProtocol>().deserialize(std::any())))> callback) const = 0;
};
