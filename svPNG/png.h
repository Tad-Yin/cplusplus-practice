/*
 * =====================================================================================
 *
 *       Filename:  png.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年07月29日 14时59分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tad Yin (), yinkejie1992@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __PNG_H__
#define __PNG_H__

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
namespace tad{
    enum class Alpha {
        haveAlpha,
        noAlpha
    };
    struct PNGException {
        std::string aError;
        PNGException(std::string _in) :aError(_in) {}
    };
    void svpng(std::string, uint32_t, uint32_t, unsigned char*, Alpha alpha);
}

#endif /* ifndef __PNG_H__ */
