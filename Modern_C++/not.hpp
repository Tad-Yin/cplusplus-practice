/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/27/2016 11:13:35 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tad Yin (), yinkejie1992@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <functional>
//not implement1: factor
namespace yin{
    template<class Predicate>
    class NotImpl{
    protected:
        Predicate _fn;
    public:
        explicit NotImpl(const Predicate& pred) : _fn(pred){};
        bool operator ()(const typename Predicate::first_argument_type& x,
                const typename Predicate::second_argument_type& y){
            return !_fn(x, y);
        }
    };

    template<class Predicate>
    NotImpl<Predicate> not2x1(const Predicate& pred){
        return NotImpl<Predicate>(pred);
    }

    //not implement2: lambda
    template<typename T, typename U>
    std::function<bool(T, U)> not2x2(std::function<bool(T, U)> pred){
        return [=](T t, U s){return !pred(t, s);};
    }


    //not implement3
    template<typename... T>
    std::function<bool(T...)> not2x3(std::function<bool(T...)> pred){
        return [pred](T... rest){return !pred(rest...);};
    }
}
