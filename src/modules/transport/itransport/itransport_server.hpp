/**
 * @file itransport_server.hpp
 * @brief Interface for itransport_server.
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include "../../protocol/iprotocol/iprotocol.hpp"
#include <functional>


class ITransportServer
{
public:
    /**
     * @brief ITransportServer constructor
     * @param protocol IProtocol interface
     */
    ITransportServer(const IProtocol& protocol);


    /**
     * @brief Run listeting requests async
     * @param callback Callback which will be called upon receipt of the request
     */
    virtual void run_async(
        std::function<void>(decltype(std::declval<IProtocol>().deserialize(std::any())) callback)) const = 0;


protected:
    const IProtocol& protocol_;
};
