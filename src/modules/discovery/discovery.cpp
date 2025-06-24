/**
 * @file iprotocol.hpp
 * @brief Class to discover other LocalChat users in local network
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#include "discovery.hpp"


Discovery &Discovery::get() noexcept { return discovery_; }
