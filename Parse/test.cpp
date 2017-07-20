#include "parse.h"
#include "exception.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdio>
#include <cstring>
#include <cassert>

#define LOG(str) std::cout<<str<<"\n"

void testParse(ParseTree& t, std::string&& str, int ans){
    LOG("test "+str);
    t.parse(str.c_str());
    assert(t.getEval() == ans);
    LOG("test pase");
}

int main() {
    ParseTree t;

    //unit test
    LOG("begin test");
    testParse(t, "1+2*3", 7);
    testParse(t, "2-3*4-6/6", 2-3*4-6/6);
    testParse(t, "1-2*3", 1-2*3);
    testParse(t, "1+2+(40*34-22)*2", 1+2+(40*34-22)*2);
    testParse(t, "2-3*4-5/6+7*(8-(9*10+1)/2+20+2*10)-20+12",
            2-3*4-5/6+7*(8-(9*10+1)/2+20+2*10)-20+12);

    LOG("test exception");
    try {
        t.parse("(3+44");
        throw std::runtime_error("str_exception expected");
    }
    catch (StrException& e) {
        assert(std::string(e.aError) == "need right bracket");
    }

    try {
        t.parse("*5-4");
        throw std::runtime_error("str_exception expected");
    }
    catch (StrException& e) {
        assert(std::string(e.aError) == "need expression");
    }
    LOG("test pase");

    std::cout<<"\nbegin Interpreter\n";
    bool flag = true;
    std::string s;
    while (flag) {
        std::cout << "==> ";
        getline(std::cin, s);
        if(s == "q" || s == "exit") {
            std::cout<<"goodbye\n";
            break;
        }
        t.parse(s.c_str());
        std::cout << t.getEval() << "\n";
    }
    return 0;
}
