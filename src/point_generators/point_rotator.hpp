#pragma once

#include <cmath>
#include <cstdio>
#include "../point.hpp"
#include <vector>

#define _USE_MATH_DEFINES

class PointRotator
{
public:
    static Point rotate(const Point& p, const Point& center, const double& rad) {
        std::vector<std::vector<double>> mat =
        {
            {double(p.x) - double(center.x), double(p.y) - double(center.y)}
        };

        std::vector<std::vector<double>> rotationMatrix = 
        {
            {std::cos(rad), -std::sin(rad)},
            {std::sin(rad), std::cos(rad)},
        };

        auto res = multiplyMatrix(mat, rotationMatrix);
        return Point{size_t(round(res[0][0])) + center.x, size_t(round(res[0][1])) + center.y};
    }

    static double d2r(double d) {
        return (d / 180.0) * ((double) 3.14159265358979323846);
    }

    static std::vector<std::vector<double>> multiplyMatrix(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b){
        int m = a.size();
        int n = a[0].size();

        int p = b.size();
        int q = b[0].size();

        std::vector<std::vector<double>> c;
        for (size_t i = 0; i < m; i++) {
            c.push_back(std::vector<double>(q, 0xFFFFFF));
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < q; j++) {
                c[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }

        return c;
    }
};

