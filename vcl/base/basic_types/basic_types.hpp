#pragma once

#include <string>

namespace vcl
{

bool is_equal(int a, int b);
bool is_equal(unsigned int a, unsigned int b);
bool is_equal(size_t a, size_t b);
bool is_equal(float a, float b);
bool is_equal(double a, double b);


constexpr size_t size(int a);
constexpr size_t size(unsigned int a);
constexpr size_t size(unsigned long a);
constexpr size_t size(float a);
constexpr size_t size(double a);





template <typename T1, typename T2> T1 clamp(T1 x, T2 x_min, T2 x_max);

}

// Template implementation
namespace vcl
{
template <typename T1, typename T2>
T1 clamp(T1 x, T2 x_min, T2 x_max)
{
    if( x<x_min )
        return x_min;
    if( x>x_max )
        return x_max;
    return x;
}



}
