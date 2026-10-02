#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// Constants

constexpr double Infinity = std::numeric_limits<double>::infinity();
constexpr double Pi = 3.1415926535897932385;

// Utility Functions

inline double DegreesToRadians(double degrees)
{
    return degrees * Pi / 180.0;
}

inline double RandomDouble()
{
    // Returns a random real in [0, 1)
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;

    return distribution(generator);
}

inline double RandomDouble(double minimum, double maximum)
{
    // Returns a random real in [minimum, maximum)
    return minimum + (maximum - minimum) * RandomDouble();
}

// Common Headers

#include "Utilities/Color.h"
#include "Utilities/Interval.h"
#include "Utilities/Ray.h"
#include "Utilities/Vec3.h"

#endif
