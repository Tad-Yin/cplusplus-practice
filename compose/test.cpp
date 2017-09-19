#include "compose.hpp"
#include <cassert>
int main(){
    auto x = [](int x, int y){
        return (x + 1) * y;
    };
    auto y = [](int _x){
        return _x * 3 + 1;
    };
    //assert(4 == (yin::compose<decltype(x), decltype(y)>(x, y)(1, 2)));
    assert(10 == (yin::make_compose(x, y, 1, 2)));
    return 0;
}
