#pragma once

#include "vcl/containers/buffer_stack/buffer_stack.hpp"

namespace vcl {

/** vec4 is an alias on the generic buffer_stack<float, 4> */
using vec4 = buffer_stack<float, 4>;

template <> struct buffer_stack<float, 4> {

    float x;
    float y;
    float z;
    float w;

    buffer_stack<float, 4>();
    buffer_stack<float, 4>(float x,float y,float z,float w);

    size_t size() const;

    const float& operator[](std::size_t index) const;
    float& operator[](std::size_t index);

    /** Get operator at given index */
    const float& operator()(std::size_t index) const;
    /** Set operator at given index */
    float& operator()(std::size_t index);

    /** Get operator at given index */
    float const& at(std::size_t index) const;
    /** Set operator at given index */
    float& at(std::size_t index);


    float* begin();
    float* end();
    float const* begin() const;
    float const* end() const;
    float const* cbegin() const;
    float const* cend() const;

};



}
