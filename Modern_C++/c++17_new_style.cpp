/*
 * =====================================================================================
 *
 *       Filename:  template.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2017年09月26日 11时19分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tad Yin (), yinkejie1992@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#include <functional>

// implement of is_same
template<class T, class U>
struct is_same : std::false_type {};
template<class T>
struct is_same<T, T> : std::true_type {};

// implement of typeof

template<class T>
struct type_wrapper {};

template<class T>
constexpr auto typeof = type_wrapper<T>{};

template<class T, class U>
constexpr auto operator==(type_wrapper<T>, type_wrapper<U>) -> std::false_type {
    return {};
}

template<class T>
constexpr auto operator==(type_wrapper<T>, type_wrapper<T>) -> std::true_type {
    return {};
}


//implement of add in template
template<int a, int b>
struct add{
    const static int result = a + b;
};

//implement of add in function overloading
template<class T, T res = 0>
struct parse_helper{
    constexpr std::integral_constant<T, res> result(){ return {}; }
    template<char digit>
    constexpr decltype(auto) operator>>(std::integral_constant<char, digit>){
        return parse_helper<T, res * 10 + digit - '0'>{};
    }
};
template<char... digits>
constexpr decltype(auto) operator""_int() {
    return (parse_helper<int>{} >> ... >> std::integral_constant<char, digits>{}).result();
}
template<class T, T a, T b>
constexpr decltype(auto) operator+(
        std::integral_constant<T, a>,
        std::integral_constant<T, b>){
    return std::integral_constant<T, a+b>{};
}

//implement of fib
template<int N>
struct fib{
    const static int result = fib<N-1>::result + fib<N-2>::result;
};
template<>
struct fib<0>{
    const static int result = 0;
};
template<>
struct fib<1>{
    const static int result = 1;
};

int main(int argc, char *argv[])
{
    //is_same
    static_assert(!is_same<int, double>::value, "std::is_same");
    static_assert(!(typeof<int> == typeof<double>).value, "typeof");
    //add
    static_assert(add<1, 2>::result == 3, "template add");
    static_assert(6 == (3_int + 3_int).value, "new add");
    //fold test
    static_assert(fib<3>::result == 2,"no fold ok");
    return 0;
}
