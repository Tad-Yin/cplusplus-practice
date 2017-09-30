/*
 * =====================================================================================
 *
 *       Filename:  c++17.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/28/2017 02:49:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tad Yin (), yinkejie1992@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <map>
#include <tuple>
#include <string>
#include <algorithm>
#include <vector>
#include <cassert>
#include <mutex>
#include <iostream>
#include <optional>
#include <cstdio>
#include <cstring>
#include <variant>
#include <numeric>
#include <experimental/filesystem>
//#include <execution>
//copy elision
std::mutex a_mutex;
auto getlock(){
    return std::lock_guard<std::mutex>(a_mutex);
}
// inline variable
inline int a;
//namespace in namespace
namespace na::nb
{
    int a = 3;
}

// if constexpr
template <typename...Ts>
int f(Ts... args){
    if constexpr(sizeof...(args)>0)
        return 1;
    else
        return 0;
}
//template non-class parameter auto
template<auto C>
struct Size{
    static constexpr size_t size=sizeof(C);
};

//lambda progress
struct Foo{
    using type=int;
    int val=42;
    int f(){
        return [*this]() {return val;}();
    }
};

//SFINAE
template<class,class=std::void_t<>>
struct has_type_member: std::false_type{};

template<class T>
struct has_type_member<T,std::void_t<typename T::type>> : std::true_type{};

//variant/optional/any
std::optional<const char*> get_foo(int choice){
    if(choice==1){
        return "yes";
    }else{
        return {};
    }
}


//fold expression
template<typename...Ts>
constexpr int sum(Ts...args){
    return (0+...+args);
}


//test
int main(int argc, char *argv[])
{
    {
        //template parameter derivation
        std::pair x(1,1.2);
        std::tuple y(1,1,1);
        static_assert(std::is_same<decltype(x), std::pair<int,double>>::value, "pair diff");
        static_assert(!std::is_same<decltype(y), std::tuple<int,double,int>>::value, "tuple diff");
    }
    {
        //evalution order optimze
        std::vector<int> a{1,2,3,4,5};
        auto x=1;
        a[x++]=x;
        assert(a[0]==1);
        assert(a[1]==1);
    }
    {
        //copy elision
        auto locak=getlock();
    }
    {
        //if statement with initilizer
        std::vector<int> a{1,2,3,4,5};
        if(auto it=std::find(a.begin(),a.end(),1);it!=a.end()){
            assert(*it=1);
        }
    }
    {
        //stuctured binding
        std::map<int,int> m;
        auto [iter,ok]=m.insert({1,2});
        static_assert(std::is_same<std::remove_reference_t<decltype(*iter)>,std::pair<const int,int>>::value);
        assert(ok==true);
    }
    {
        //string view
        std::string cppstr="foo";
        std::string_view cppstr_v(&cppstr[0], cppstr.size());
    }
    {
        //namespace in namespace
        assert(na::nb::a == 3);
    }
    {
        //test if constexpr
        assert(0==f());
        assert(1==f(1));
    }
    {
        //template auto
        static_assert(Size<3>::size==sizeof(3));
        static_assert(Size<(void*)0>::size==sizeof(void*));
    }
    {
        //lambda progress
        Foo obj{42};
        assert(obj.f()==42);

        //lambda progress2
        constexpr Foo obj2{32};
        auto getSize=[](auto o){return sizeof(o);};
        static_assert(getSize(obj2)==sizeof(Foo));
    }
    {
        //SFINAE progress void_t, to detect ill-formed types
        static_assert(has_type_member<Foo>::value,"SFINAE error");
    }
    {
        //variant optional any
        assert(strcmp(get_foo(1).value_or("no"),"yes")==0);
        assert(strcmp(get_foo(0).value_or("no"),"no")==0);
        std::variant<int,float> v,w;
        v=12;
        int i=std::get<int>(v);
        w=std::get<int>(v);
        w=std::get<0>(v);
        w=v;
    }
    {
        //algorithm progress
        //std::vector<int> v{3,2,3,4,5,1,2,3,5,6,7,8,1};
        //std::sort(std::execution::par, std::begin(v), std::end(v));
        //std::vector<int> v2{1,2,4,5,0};
        //assert(12==std::reduce(std::execution::par, std::begin(v2), std::end(v2)));
    }
    {
        //filesystem
    }
    {
        //aligned dynamic allocation
    }
    {
        //move between points in collection
        std::map<int,std::string> src{{1,"one"},{2,"two"},{3,"buckle my shoe"}};
        std::map<int,std::string> dst{{3,"three"}};
        dst.insert(src.extract(src.find(1)));
        dst.insert(src.extract(2));
        assert(dst[1]=="one");
        assert(dst[2]=="two");
        assert(dst[3]=="three");
    }
    {
        //fold expression
        static_assert(10==sum(2,3,5));
    }
    return 0;
}
