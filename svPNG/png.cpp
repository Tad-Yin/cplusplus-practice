/*
 * =====================================================================================
 *
 *       Filename:  png.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年07月29日 14时59分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tad Yin (), yinkejie1992@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include "png.h"
#include <cassert>
namespace tad {
    void svpng(const std::string path, uint32_t w, uint32_t h, unsigned char* data, Alpha alpha) {
        static const unsigned t[] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
            0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
            0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
            0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };//crc table

        std::ofstream of(path, std::fstream::binary);
        uint32_t crc, a = 1, b = 0, p = w * (alpha == Alpha::haveAlpha ? 4 : 3) + 1;

        auto u32 = [&of](uint32_t u) {of.put(u >> 24);of.put((u >> 16) & 255);of.put((u >> 8) & 255);of.put(u & 255);};
        auto u8c = [&of, &crc](unsigned char u){of.put(u);crc ^= u;crc = (crc >> 4) ^ t[crc & 15];crc = (crc >> 4) ^ t[crc & 15];};
        auto u8ac = [u8c](std::string&& s){for(char c:s) u8c(c);};
        auto u16lc = [u8c](uint16_t u){u8c(u & 255);u8c((u >> 8) & 255);};
        auto u32c = [u8c](uint32_t u){u8c(u >> 24);u8c((u >> 16) & 255);u8c((u >> 8) & 255);u8c(u & 255);};
        auto u8adler = [u8c, &a, &b](unsigned char u){u8c(u);a = (a + u) % 65521; b = (b + a) % 65521;};
        auto ubegin = [u32, u8ac, &crc](std::string&& s, uint32_t l){u32(l); crc = ~0U; u8ac(std::move(s));};
        auto uend = [u32, &crc](){u32(~crc);};

        int time = 0;
        #define printc printf("%d %d\n", time++, crc)
        if (of.is_open()) {
            of.write("\x89PNG\r\n\32\n", 8);

            ubegin("IHDR", 13);
            u32c(w);
            u32c(h);
            u8c(8);
            u8c(alpha == Alpha::haveAlpha ? 6 : 2);
            u8c('\0');
            u8c('\0');
            u8c('\0');
            uend();

            ubegin("IDAT", 2 + h * (5 + p) + 4);
            u8ac("\x78\1");
            for(uint32_t y = 0; y < h; y++){
                u8c(y == h-1);
                u16lc(p); u16lc(~p);
                u8adler(0);
                for(uint32_t x = 0; x < p - 1; x++, data++){
                    u8adler(*data);
                }
            }
            u32c((b << 16) | a);
            uend();
            ubegin("IEND", 0);
            uend();
            //of << "test it";

            of.close();
        }
        else {
            throw PNGException("can not create file");
        }
    }
}
