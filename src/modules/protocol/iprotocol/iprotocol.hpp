/**
 * @file iprotocol.hpp
 * @brief Abstract Protocol class to serialize and desirealize objects
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include "internals/iserializer.hpp"
#include "internals/ideserializer.hpp"


/**
 * @name IProtocol
 * @brief The abstract IProtocol class to serialize and deserialize messages
 */
class IProtocol : public ISerializer, public IDeserializer {};
