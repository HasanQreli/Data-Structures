#pragma once

#include <cmath>

struct IdPair
{
    int vertexId0;
    int vertexId1;
};

struct Double3
{
    double x, y, z;

    static double Distance(Double3 left, Double3 right);
};

inline
double Double3::Distance(Double3 left, Double3 right)
{
    //TODO:
    return std::sqrt(std::pow(left.x - right.x , 2) + std::pow(left.y - right.y , 2) + std::pow(left.z - right.z , 2));
}