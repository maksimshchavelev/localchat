/**
 * @file jsontransport.hpp
 * @brief Implementation of transport uses json protocol.
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#include <thread>
#include <AlexandreRouma-net/net.h>
#include "../../config/config.hpp"
#include "../itransport/itransport.hpp"
#include "../../protocol/jsonprotocol/jsonprotocol.hpp"


class JsonTransport : public ITransport
{
public:
    /**
     * @brief JsonTransport constructor
     * @param protocol JsonProtocol reference
     */
    JsonTransport(const JsonProtocol& protocol);


    /**
     * @brief Run listeting requests (server) async
     * @param callback Callback which will be called upon receipt of the request
     */
    void run_server_async(
        std::function<void(decltype(std::declval<IProtocol>().deserialize(std::any())))> callback) const override;


    /**
     * @brief Send text message to the new
     * @param host IPv4 address of host (receiver)
     * @param msg Message
     * @return `true` if success, `false` if fail
     */
    bool send_message(const std::string& host, const Message& msg) const override;



protected:
    const JsonProtocol& protocol_;


private:
    /**
     * @brief Get `Json::Value` from string
     * @return `std::optional` with `Json::Value` if success, otherwise empty `std::optional`
     */
    std::optional<Json::Value> _json_from_str(const std::string& data) const;
};

