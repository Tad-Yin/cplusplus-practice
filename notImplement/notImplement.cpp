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
#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <string>
#include <memory>
#include <iterator>
#include <vector>
#include <cctype>
using namespace std;

//not implement1: factor
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
function<bool(T, U)> not2x2(function<bool(T, U)> pred){
    return [=](T t, U s){return !pred(t, s);};
}


//not implement3
template<typename... T>
function<bool(T...)> not2x3(function<bool(T...)> pred){
    return [pred](T... rest){return !pred(rest...);};
}


//========================================client

int icharCompare(char c1, char c2){
    int ic1 = tolower(static_cast<unsigned char>(c1));
    int ic2 = tolower(static_cast<unsigned char>(c2));
    if(ic1 < ic2) return -1;
    if(ic1 > ic2) return 1;
    return 0;
}
int istringCompareImpl(const string& s1, const string& s2, int type);

int istringCompare(const string &s1, const string& s2, int type){
    if(s1.size() <= s2.size()) return istringCompareImpl(s1, s2, type);
    else return -istringCompareImpl(s2, s1, type);
}

int istringCompareImpl(const string& s1, const string& s2, int type){
    using PSCI = pair<string::const_iterator, string::const_iterator>;
    std::function<bool(char, char)> f = icharCompare;
    PSCI p;
    if(type == 1)
        p = mismatch(s1.begin(), s1.end(), s2.begin(), not2x1(f));
    else if(type == 2)
        p = mismatch(s1.begin(), s1.end(), s2.begin(), not2x2(f));
    else if(type == 3)
        p = mismatch(s1.begin(), s1.end(), s2.begin(), not2x3(f));

    if(p.first == s1.end()){
        if(p.second == s2.end()) return 0;
        else return -1;
    }
    return icharCompare(*p.first, *p.second);
}

int main(int argc, char *argv[])
{
    for(int i=1; i<=3; i++){
        cout << "test: " << i << "\n";
        string s = "testfd";
        string t = "testfd";
        cout << "compair " << s << " and " << t << " " << istringCompare(s, t, i) << "\n";
        t = "testff";
        cout << "compair " << s << " and " << t << " " << istringCompare(s, t, i) << "\n";
        t = "testaf";
        cout << "compair " << s << " and " << t << " " << istringCompare(s, t, i) << "\n";
    }
    return 0;
}
