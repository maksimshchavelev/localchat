/**
 * @file iprotocol.hpp
 * @brief Class to discover other LocalChat users in local network
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include <drogon/drogon.h>


/**
 * @name Discovery
 * @brief The Discovery class to discover other LocalChat users in local network
 * @details The singleton class
 */
class Discovery
{
public:
    /**
     * @brief Get `Discovery` instance
     * @return Discovery instance
     */
    Discovery& get() noexcept;


private:
    Discovery();

    static Discovery discovery_;
};
