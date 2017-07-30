/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年07月29日 14时58分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tad Yin (), yinkejie1992@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include "png.h"
void test_rgb() {
    unsigned char rgb[256 * 256 * 3], *p = rgb;
    for (auto y = 0; y < 256; y++)
        for (auto x = 0; x < 256; x++) {
            *p++ = (unsigned char)x;
            *p++ = (unsigned char)y;
            *p++ = 128;
        }
    tad::svpng("test.png", 256, 256, rgb, tad::Alpha::noAlpha);
}

int main() {
    test_rgb();
	return 0;
}
