#pragma once
#include "math.h"

const float PI = 3.14159265f;
#define RAND(a, b) ((((rand()) % b) + a))

namespace ezo
{
    int clamp(int x, int min, int max);
    float clamp(float x, float min, float max);
    double clamp(double x, double min, double max);

    float degToRad(float degrees);
    float radToDeg(float radians);

    float vecLength(float x, float y);

    bool floatInRange(float arg, float perfectValue, float allowedDiff);
}
