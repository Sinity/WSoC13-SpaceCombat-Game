#include "emath.h"

namespace ezo
{

int clamp(int x, int min, int max)
{
    return x < min ? min : (x > max ? max : x);
}

float clamp(float x, float min, float max)
{
    return x < min ? min : (x > max ? max : x);
}

double clamp(double x, double min, double max)
{
    return x < min ? min : (x > max ? max : x);
}

float radToDeg(float radians)
{
    return radians * 180 / PI;
}

float degToRad(float degrees)
{
    return degrees * PI / 180;
}

float vecLength(float x, float y)
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

bool floatInRange(float arg, float perfectValue, float allowedDiff)
{
    return arg > (perfectValue - allowedDiff) && arg < (perfectValue + allowedDiff);
}

}
