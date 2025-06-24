/**
 * @file message.hpp
 * @brief Message struct and conversion utils
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once

#include <vector>
#include <chrono>

using ByteVector = std::vector<std::byte>;


/**
 * @brief The Message struct (describes message)
 */
struct Message
{
    ByteVector sender;
    ByteVector data;
    std::chrono::system_clock::time_point send_time;
};



/**
 * @brief Converts `container` to ByteVector if `container` supports `data()` and `size()` methods
 * @return ByteVector
 */
template <typename Container>
ByteVector to_byteVector(Container&& container) requires requires { container.data(); container.size(); }
{
    ByteVector result(reinterpret_cast<const std::byte*>(container.data()),
                      reinterpret_cast<const std::byte*>(container.data() + container.size()));
    return result;
}



/**
 * @brief Converts `byteVector` to `Container` if `Container` is constructible from begin and end iterators
 * @tparam Container Container type
 * @return Container
 */
template <typename Container>
Container from_byteVector(const ByteVector& byteVector)
{
    Container result(reinterpret_cast<const Container::value_type*>(byteVector.data()),
                      reinterpret_cast<const Container::value_type*>(byteVector.data() + byteVector.size()));
    return result;
}
