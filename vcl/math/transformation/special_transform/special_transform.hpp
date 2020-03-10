#pragma once

#include "../../vec/vec.hpp"
#include "../../mat/mat.hpp"


namespace vcl
{

mat3 rotation_from_axis_angle_mat3(const vec3& axis, float angle);
mat3 rotation_between_vector_mat3(const vec3& a, const vec3& b);

}
