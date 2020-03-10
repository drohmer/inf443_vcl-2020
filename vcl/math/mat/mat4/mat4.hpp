#pragma once

#include "../mat/mat.hpp"
#include "../../vec/vec4/vec4.hpp"



namespace vcl {
using mat3 = mat<3,3>;
using vec3 = vec<3>;

using mat4 = mat<4,4>;

template <> struct mat<4,4> {

    float xx,xy,xz,xw;
    float yx,yy,yz,yw;
    float zx,zy,zz,zw;
    float wx,wy,wz,ww;

    mat<4,4>();
    mat<4,4>(float xx,float xy,float xz,float xw,
             float yx,float yy,float yz,float yw,
             float zx,float zy,float zz,float zw,
             float wx,float wy,float wz,float ww);
    mat<4,4>(const vcl::mat3& R, const vcl::vec3& t);

    static mat4 identity();
    static mat4 zero();
    static mat4 perspective(float angle_of_view, float image_aspect, float z_near, float z_far);
    /**
     * Return the block matrix
     * ( L00 L01 L02 | tx )
     * ( L10 L11 L12 | ty )
     * ( L20 L21 L22 | tz )
     * (  0   0   0  | 1  )
     *
     * where L: linear part, t: translation
     */
    static mat4 from_mat3_vec3(const vcl::mat3& linear_block, const vcl::vec3& translation_block);

    /** Return the matrix
     * (s 0 0 0)
     * (0 s 0 0)
     * (0 0 s 0)
     * (0 0 0 1)  */
    static mat4 from_scaling(float s);
    /** Return the matrix
     * (sx 0 0 0)
     * (0 sy 0 0)
     * (0 0 sz 0)
     * (0 0 0  1)  */
    static mat4 from_scaling(const vcl::vec3& s);
    /** Return the matrix
     * ( m00 m01 m02 | 0 )
     * ( m10 m11 m12 | 0 )
     * ( m20 m21 m22 | 0 )
     * (  0   0   0  | 1  )
     *  */
    static mat4 from_mat3(const vcl::mat3& m);
    /** Return the matrix
     * (  0   0   0  | tx )
     * (  0   0   0  | ty )
     * (  0   0   0  | tz )
     * (  0   0   0  |  1 )
     *  */
    static mat4 from_translation(const vcl::vec3& t);

    vec4 row(std::size_t offset) const;
    vec4 col(std::size_t offset) const;
    mat4& set_row(std::size_t offset, const vec4& v);
    mat4& set_col(std::size_t offset, const vec4& v);


    const float& operator[](std::size_t offset) const;
    float& operator[](std::size_t offset);

    const float& operator()(std::size_t index1, std::size_t index2) const;
    float& operator()(std::size_t index1, std::size_t index2);


    vcl::mat3 mat3() const;
    mat4& set_mat3(const vcl::mat3& m);
    vcl::vec3 vec3() const;
    mat4& set_vec3(const vcl::vec3& tr);


};








}
