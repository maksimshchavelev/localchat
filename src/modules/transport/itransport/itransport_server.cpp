/**
 * @file itransport_server.cpp
 * @brief Interface for itransport_server.
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */



#include "itransport_server.hpp"



/* public method */
ITransportServer::ITransportServer(const IProtocol& protocol) : protocol_(protocol) {}
