//
// Created by User on 08.04.2025.
//

#ifndef SKY_RND_H
#define SKY_RND_H

#include <iostream>
#include <chrono>
#include <random>

class RND {
private:
    //static auto s_instance = RND {};
    std::random_device m_rd;
    std::mt19937::result_type m_seed;
    std::mt19937 m_gen;

    RND() : m_rd {}, m_seed {m_rd() ^ (
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count() )}, m_gen {m_seed} {}
public:
    static RND& instance()
    {
        static RND instance = RND{};
        return instance;
    }
    int get(int min, int max)
    {
        std::uniform_int_distribution<unsigned> distrib(min, max);
        return distrib(m_gen);
    }
    double get(double min, double max)
    {
        std::uniform_real_distribution<double> distrib(min, max);
        return distrib(m_gen);
    }
};


#endif //SKY_RND_H
