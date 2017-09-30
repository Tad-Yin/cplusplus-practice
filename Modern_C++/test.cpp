/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月30日 10时37分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tad Yin (), yinkejie1992@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

//========================================client
#include "compose.hpp"
#include "not.hpp"
#include <cassert>
#include <iostream>

//test not
int icharCompare(char c1, char c2){
    int ic1 = tolower(static_cast<unsigned char>(c1));
    int ic2 = tolower(static_cast<unsigned char>(c2));
    if(ic1 < ic2) return -1;
    if(ic1 > ic2) return 1;
    return 0;
}
int istringCompareImpl(const std::string& s1, const std::string& s2, int type);

int istringCompare(const std::string &s1, const std::string& s2, int type){
    if(s1.size() <= s2.size()) return istringCompareImpl(s1, s2, type);
    else return -istringCompareImpl(s2, s1, type);
}

int istringCompareImpl(const std::string& s1, const std::string& s2, int type){
    using PSCI = std::pair<std::string::const_iterator, std::string::const_iterator>;
    std::function<bool(char, char)> f = icharCompare;
    PSCI p;
    if(type == 1)
        p = mismatch(s1.begin(), s1.end(), s2.begin(), yin::not2x1(f));
    else if(type == 2)
        p = mismatch(s1.begin(), s1.end(), s2.begin(), yin::not2x2(f));
    else if(type == 3)
        p = mismatch(s1.begin(), s1.end(), s2.begin(), yin::not2x3(f));

    if(p.first == s1.end()){
        if(p.second == s2.end()) return 0;
        else return -1;
    }
    return icharCompare(*p.first, *p.second);
}

int main(int argc, char *argv[])
{
    // test compose
    auto x = [](int x, int y){
        return (x + 1) * y;
    };
    auto y = [](int _x){
        return _x * 3 + 1;
    };
    //assert(4 == (yin::compose<decltype(x), decltype(y)>(x, y)(1, 2)));
    assert(10 == (yin::make_compose(x, y, 1, 2)));

    // test not
    for(int i=1; i<=3; i++){
        std::cout << "test: " << i << "\n";
        std::string s = "testfd";
        std::string t = "testfd";
        std::cout << "compair " << s << " and " << t << " " << istringCompare(s, t, i) << "\n";
        t = "testff";
        std::cout << "compair " << s << " and " << t << " " << istringCompare(s, t, i) << "\n";
        t = "testaf";
        std::cout << "compair " << s << " and " << t << " " << istringCompare(s, t, i) << "\n";
    }
    return 0;
}

