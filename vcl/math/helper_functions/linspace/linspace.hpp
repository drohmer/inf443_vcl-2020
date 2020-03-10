#pragma once

#include "vcl/containers/buffer/buffer.hpp"
#include "vcl/math/vec/vec.hpp"

namespace vcl
{

buffer<float> linspace(float x_min, float x_max, size_t N);
buffer2D<vec2> linspace(vec2 const& p_min, vec2 const& p_max, size_t2 N);
buffer3D<vec3> linspace(vec3 const& p_min, vec3 const& p_max, size_t3 N);

}
