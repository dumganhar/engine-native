/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "Color.h"

Color::Color()
: r(0.0F),
  g(0.0F),
  b(0.0F),
  a(0.0F) {
}

Color::Color(float r, float g, float b, float a)
: r(r),
  g(g),
  b(b),
  a(a) {
}

Color::Color(const float *src) {
    set(src);
}

Color::Color(const Color &p1, const Color &p2) {
    set(p1, p2);
}

Color::Color(const Color &copy) {
    set(copy);
}

void Color::set(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Color::set(const float *array) {
    r = array[0];
    g = array[1];
    b = array[2];
    a = array[3];
}

void Color::set(const Color &c) {
    this->r = c.r;
    this->g = c.g;
    this->b = c.b;
    this->a = c.a;
}

void Color::set(const Color &p1, const Color &p2) {
    r = p2.r - p1.r;
    g = p2.g - p1.g;
    b = p2.b - p1.b;
    a = p2.a - p1.a;
}