/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description: unary
 *
 *        Version:  1.0
 *        Created:  2016年10月18日 11时54分02秒
 *       Revision:  none
 *       Compiler:  visual stuio 2015
 *
 *         Author:  Tad Yin (), yinkejie1992@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
using namespace std;
template <class T>

//c++98 add factor
class my_bind2nd : public unary_function<
                   typename T::first_argument_type,
                   typename T::result_type>
{
public:
    my_bind2nd(T op1, typename T::second_argument_type val) {
        op = op1;
        value = val;
    }
    typename T::result_type operator()(const typename T::second_argument_type& x) const
    {
        return op(x, value);
    }
private:
    T op;
    typename T::second_argument_type value;
};

template<class T, class V>
inline my_bind2nd<T> bind2nd2(T t, V val) {
    typedef typename T::second_argument_type se;
    return my_bind2nd<T>(t, se(val));
}

template<class T>
class my_plus {
public:
    T operator()(const T& t1, const  T& t2) const
    {
        return t1 + t2;
    }
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef T result_type;
};

//c++98 compose implement
template <class Fun1, class Fun2>
class compose :public std::unary_function<
               typename Fun2::argument_type,
               typename Fun1::result_type>
{
protected:
    Fun1 f;
    Fun2 g;

public:
    compose(const Fun1& _f, const Fun2& _g)
        : f(_f), g(_g) { }

    typename Fun1::result_type operator()(const typename Fun2::argument_type& x) const
    {
        return f(g(x));
    }
};

template <class A, class B>
inline compose<A, B> compose2(const A& f, const B& g){
    return compose<A, B>(f, g);
}


//test
int main(int argc, char *argv[]){
    int array[5] = {1, 3, 5, 7, 9};
    vector<int> v(array, array + 5);
    transform(v.begin(), v.end(), ostream_iterator<int>(cout, " "), compose2(bind2nd2(my_plus<int>(), 3), bind2nd(plus<int>(), 2)));
    return 0;
}
