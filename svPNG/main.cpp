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
int main() {
	std::vector<std::vector<unsigned char>> map;
	tad::svpng("test.png", map, tad::Alpha::noAlpha);
	return 0;
}
