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

    virtual void run_server_async(
        std::function<void(decltype(std::declval<IProtocol>().deserialize(std::any())))> callback) const = 0;
};
