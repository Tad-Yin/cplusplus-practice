/*
 * =====================================================================================
 *
 *       Filename:  make_half.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年01月16日 13时40分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tad Yin (), yinkejie1992@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <memory>
#include <functional>
#include <type_traits>
#include <typeinfo>


// template specify
template<class T>
struct make_half;

template<>
struct make_half<std::uint64_t>{
    using type = std::uint32_t;
};

template<class T>
using make_half_t = typename make_half<T>::type;

// function overload
auto make_type(std::uint64_t) -> std::uint32_t;

template<class T>
using make_half_tt = decltype(make_type(std::declval<T>()));


// if and conditional
template<class T>
using make_halt_ttt = std::conditional_t<std::is_same<T, std::int64_t>::value,  std::int32_t,
                      std::conditional_t<std::is_same<T, std::uint_fast32_t>::value, uint_fast16_t,
                      void>>;

int main(){
    static_assert(std::is_same<make_half_t<uint64_t>, uint32_t>(), "not same");
    static_assert(std::is_same<make_half_tt<uint64_t>, uint32_t>(), "not same");
    static_assert(std::is_same<make_halt_ttt<int64_t>, int32_t>(), "not smae");
}
