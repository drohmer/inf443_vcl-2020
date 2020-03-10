#pragma once

#include <vector>
#include <ostream>

#include "vcl/base/base.hpp"
#include <iostream>

/** ************************************************** **/
/**           Header                                   **/
/** ************************************************** **/

namespace vcl
{

template <typename T>
struct buffer
{
    std::vector<T> data;

    buffer();
    buffer(size_t size);
    buffer(std::initializer_list<T> arg);
    buffer(std::vector<T> const& arg);

    size_t size() const;
    void resize(size_t size);
    void push_back(T const& value);
    void clear();
    void fill(T const& value);

    T const& operator[](size_t index) const;
    T & operator[](size_t index);
    T const& operator()(size_t index) const;
    T & operator()(size_t index);
    T const& at(size_t index) const;
    T & at(size_t index);

    typename std::vector<T>::iterator begin();
    typename std::vector<T>::iterator end();
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::const_iterator end() const;
    typename std::vector<T>::const_iterator cbegin() const;
    typename std::vector<T>::const_iterator cend() const;
};


template <typename T> std::ostream& operator<<(std::ostream& s, buffer<T> const& v);
template <typename T> std::string to_string(buffer<T> const& v, std::string const& separator=" ");

template <typename T1, typename T2> bool is_equal(buffer<T1> const& a, buffer<T2> const& b);
template <typename T> bool is_equal(buffer<T> const& a, buffer<T> const& b);

template <typename T> T average(buffer<T> const& a);

template <typename T> buffer<T>  operator-(buffer<T> const& a);

template <typename T> buffer<T>& operator+=(buffer<T>& a, buffer<T> const& b);
template <typename T> buffer<T>& operator+=(buffer<T>& a, T const& b);
template <typename T> buffer<T>  operator+(buffer<T> const& a, buffer<T> const& b);
template <typename T> buffer<T>  operator+(buffer<T> const& a, T const& b);
template <typename T> buffer<T>  operator+(T const& a, buffer<T> const& b);

template <typename T> buffer<T>& operator-=(buffer<T>& a, buffer<T> const& b);
template <typename T> buffer<T>& operator-=(buffer<T>& a, T const& b);
template <typename T> buffer<T>  operator-(buffer<T> const& a, buffer<T> const& b);
template <typename T> buffer<T>  operator-(buffer<T> const& a, T const& b);
template <typename T> buffer<T>  operator-(T const& a, buffer<T> const& b);

template <typename T> buffer<T>& operator*=(buffer<T>& a, buffer<T> const& b);
template <typename T> buffer<T>  operator*(buffer<T> const& a, buffer<T> const& b);
template <typename T> buffer<T>& operator*=(buffer<T>& a, float b);
template <typename T> buffer<T>  operator*(buffer<T> const& a, float b);
template <typename T> buffer<T>  operator*(float a, buffer<T> const& b);

template <typename T> buffer<T>& operator/=(buffer<T>& a, buffer<T> const& b);
template <typename T> buffer<T>& operator/=(buffer<T>& a, float b);
template <typename T> buffer<T>  operator/(buffer<T> const& a, buffer<T> const& b);
template <typename T> buffer<T>  operator/(buffer<T> const& a, float b);
template <typename T> buffer<T>  operator/(float a, buffer<T> const& b);


}



/** ************************************************** **/
/**           IMPLEMENTATION                           **/
/** ************************************************** **/

namespace vcl
{

template <typename T>
buffer<T>::buffer()
    :data()
{}

template <typename T>
buffer<T>::buffer(size_t size)
    :data(size)
{}

template <typename T>
buffer<T>::buffer(std::initializer_list<T> arg)
    :data(arg)
{}

template <typename T>
buffer<T>::buffer(const std::vector<T>& arg)
    :data(arg)
{}

template <typename T>
size_t buffer<T>::size() const
{
    return data.size();
}

template <typename T>
void buffer<T>::resize(size_t size)
{
    data.resize(size);
}

template <typename T>
void buffer<T>::push_back(T const& value)
{
    data.push_back(value);
}

template <typename T>
void buffer<T>::clear()
{
    data.clear();
}

template <typename T>
T const& buffer<T>::operator[](size_t index) const
{
    assert_vcl(index<data.size(), "index="+str(index));
    return data[index];
}
template <typename T>
T & buffer<T>::operator[](size_t index)
{
    assert_vcl(index<data.size(), "index="+str(index));
    return data[index];
}

template <typename T>
T const& buffer<T>::operator()(size_t index) const
{
    return (*this)[index];
}

template <typename T>
T & buffer<T>::operator()(size_t index)
{
    return (*this)[index];
}

template <typename T>
T const& buffer<T>::at(size_t index) const
{
    return data.at(index);
}

template <typename T>
T & buffer<T>::at(size_t index)
{
    return data.at(index);
}

template <typename T>
void buffer<T>::fill(T const& value)
{
    size_t const N = size();
    for(size_t k=0; k<N; ++k)
        data[k] = value;
}

template <typename T>
typename std::vector<T>::iterator buffer<T>::begin()
{
    return data.begin();
}

template <typename T>
typename std::vector<T>::iterator buffer<T>::end()
{
    return data.end();
}

template <typename T>
typename std::vector<T>::const_iterator buffer<T>::begin() const
{
    return data.begin();
}

template <typename T>
typename std::vector<T>::const_iterator buffer<T>::end() const
{
    return data.end();
}

template <typename T>
typename std::vector<T>::const_iterator buffer<T>::cbegin() const
{
    return data.cbegin();
}

template <typename T>
typename std::vector<T>::const_iterator buffer<T>::cend() const
{
    return data.cend();
}

template <typename T> std::ostream& operator<<(std::ostream& s, buffer<T> const& v)
{
    std::string s_out = to_string(v);
    s << s_out;
    return s;
}
template <typename T> std::string to_string(buffer<T> const& v, std::string const& separator)
{
    return vcl::detail::to_string_container(v, separator);
}

template <typename T> T average(buffer<T> const& a)
{
    size_t const N = a.size();
    assert_vcl_no_msg(N>0);

    T value; // assume value start at zero
    for(size_t k=0; k<N; ++k)
        value += a[k];
    value /= float(N);

    return value;
}

template <typename T>
buffer<T>& operator+=(buffer<T>& a, buffer<T> const& b)
{
    assert_vcl(a.size()>0 && b.size()>0, "Size must be >0");
    assert_vcl(a.size()==b.size(), "Size do not agree");

    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] += b[k];
    return a;
}

template <typename T>
buffer<T>& operator+=(buffer<T>& a, T const& b)
{
    assert_vcl(a.size()>0, "Size must be >0");
    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] += b;
    return a;
}

template <typename T>
buffer<T>  operator+(buffer<T> const& a, buffer<T> const& b)
{
    buffer<T> res = a;
    res += b;
    return res;
}

template <typename T>
buffer<T>  operator+(buffer<T> const& a, T const& b)
{
    buffer<T> res = a;
    res += b;
    return res;
}

template <typename T>
buffer<T>  operator+(T const& a, buffer<T> const& b)
{
    size_t const N = b.size();
    buffer<T> res(N);
    for(size_t k=0; k<N; ++k)
        res[k] = a+b[k];
    return res;
}

template <typename T> buffer<T>  operator-(buffer<T> const& a)
{
    size_t const N = a.size();
    buffer<T> b(N);
    for(size_t k=0; k<N; ++k)
        b[k] = -a[k];
    return b;
}


template <typename T> buffer<T>& operator-=(buffer<T>& a, buffer<T> const& b)
{
    assert_vcl(a.size()>0 && b.size()>0, "Size must be >0");
    assert_vcl(a.size()==b.size(), "Size do not agree");

    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] -= b[k];
    return a;
}
template <typename T> buffer<T>& operator-=(buffer<T>& a, T const& b)
{
    assert_vcl(a.size()>0, "Size must be >0");
    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] -= b;
    return a;
}
template <typename T> buffer<T>  operator-(buffer<T> const& a, buffer<T> const& b)
{
    buffer<T> res = a;
    res -= b;
    return res;
}
template <typename T> buffer<T>  operator-(buffer<T> const& a, T const& b)
{
    buffer<T> res = a;
    res -= b;
    return res;
}
template <typename T> buffer<T>  operator-(T const& a, buffer<T> const& b)
{
    size_t const N = b.size();
    buffer<T> res(N);
    for(size_t k=0; k<N; ++k)
        res[k] = a-b[k];
    return res;
}


template <typename T> buffer<T>& operator*=(buffer<T>& a, buffer<T> const& b)
{
    assert_vcl(a.size()>0 && b.size()>0, "Size must be >0");
    assert_vcl(a.size()==b.size(), "Size do not agree");

    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] *= b[k];
    return a;
}
template <typename T> buffer<T>  operator*(buffer<T> const& a, buffer<T> const& b)
{
    buffer<T> res = a;
    res *= b;
    return res;
}




template <typename T> buffer<T>& operator*=(buffer<T>& a, float b)
{
    size_t const N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] *= b;
    return a;
}
template <typename T> buffer<T>  operator*(buffer<T> const& a, float b)
{
    size_t const N = a.size();
    buffer<T> res(N);
    for(size_t k=0; k<N; ++k)
        res[k] = a[k]*b;
    return res;
}
template <typename T> buffer<T>  operator*(float a, buffer<T> const& b)
{
    size_t const N = b.size();
    buffer<T> res(N);
    for(size_t k=0; k<N; ++k)
        res[k] = a*b[k];
    return res;
}

template <typename T> buffer<T>& operator/=(buffer<T>& a, buffer<T> const& b)
{
    assert_vcl(a.size()>0 && b.size()>0, "Size must be >0");
    assert_vcl(a.size()==b.size(), "Size do not agree");

    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] /= b[k];
    return a;
}
template <typename T> buffer<T>& operator/=(buffer<T>& a, float b)
{
    assert_vcl(a.size()>0, "Size must be >0");
    const size_t N = a.size();
    for(size_t k=0; k<N; ++k)
        a[k] /= b;
    return a;
}
template <typename T> buffer<T>  operator/(buffer<T> const& a, buffer<T> const& b)
{
    buffer<T> res = a;
    res /= b;
    return res;
}
template <typename T> buffer<T>  operator/(buffer<T> const& a, float b)
{
    buffer<T> res = a;
    res /= b;
    return res;
}
template <typename T> buffer<T>  operator/(float a, buffer<T> const& b)
{
    size_t const N = b.size();
    buffer<T> res(N);
    for(size_t k=0; k<N; ++k)
        res[k] = a/b[k];
    return res;
}


template <typename T1, typename T2> bool is_equal(buffer<T1> const& a, buffer<T2> const& b)
{
    size_t const N = a.size();
    if(b.size()!=N)
        return false;

    using vcl::is_equal;
    for(size_t k=0; k<N; ++k)
        if( is_equal(a[k],b[k])==false )
            return false;
    return true;
}
template <typename T> bool is_equal(buffer<T> const& a, buffer<T> const& b)
{
    return is_equal<T,T>(a,b);
}





}
