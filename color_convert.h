#ifndef _COLOR_CONVERT_
#define _COLOR_CONVERT_

#include <stdint.h>

typedef struct {
    float r;       // a fraction between 0 and 1
    float g;       // a fraction between 0 and 1
    float b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    float h;       // angle in degrees
    float s;       // a fraction between 0 and 1
    float v;       // a fraction between 0 and 1
} hsv;


extern hsv rgb2hsv(rgb in);
extern rgb hsv2rgb(hsv in);
#endif // _COLOR_CONVERT_
