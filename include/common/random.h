#ifndef RANDOM_H
#define RANDOM_H
#include <iostream>
#include <random>
#include <time.h>
#include "singleton.h"

using namespace std;

class Random final : public Singleton<Random>
{
public:
    Random()
    {
        m_engine.seed(time(nullptr));
    }

public:
    // 随机分布 []
    int32_t UniformIntDistribution(int32_t lower, int32_t upper)
    {
        if (!CheckIntRange(lower, upper))
        {
            return lower;
        }
        std::uniform_int_distribution<int32_t> u(lower, upper);
        return u(m_engine);
    }
    // 随机分布 [)
    double UniformRealDistribution(double lower, double upper)
    {
        if (!CheckRealRange(lower, upper))
        {
            return lower;
        }

        std::uniform_real_distribution<double> u(lower, upper);
        return u(m_engine);
    }

    // 正态分布
    double NormalDistribution(double center, double half_range)
    {
        std::normal_distribution<double> u(center, half_range);
        return u(m_engine);
    }
private:
    bool CheckIntRange(int32_t& lower, int32_t& upper)
    {
        if (lower == upper)
            return false;

        if (lower > upper)
        {
            int32_t tmp_h = upper;
            upper = lower;
            lower = tmp_h;
        }
        return true;
    }

    bool CheckRealRange(double& lower, double& upper)
    {
        if (std::abs(lower - upper) < 0.0000001)
            return false;

        if (lower > upper)
        {
            double tmp_h = upper;
            upper = lower;
            lower = tmp_h;
        }
        return true;
    }
private:
    default_random_engine  m_engine;
};

#endif // RANDOM_H
