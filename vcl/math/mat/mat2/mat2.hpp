#pragma once

#include "../mat/mat.hpp"
#include "../../vec/vec2/vec2.hpp"

namespace vcl {
using mat2 = mat<2,2>;

template <> struct mat<2,2> {

    float xx,xy;
    float yx,yy;

    mat<2,2>();
    mat<2,2>(float xx,float xy,
             float yx,float yy);

    static mat2 identity();

    vec2 row(std::size_t offset) const;
    vec2 col(std::size_t offset) const;
    mat2& set_row(std::size_t offset, const vec2& v);
    mat2& set_col(std::size_t offset, const vec2& v);

    const float& operator[](std::size_t offset) const;
    float& operator[](std::size_t offset);

    const float& operator()(std::size_t index1, std::size_t index2) const;
    float& operator()(std::size_t index1, std::size_t index2);

};

float det(const mat2& m);
mat2 inverse(const mat2& m);





}
