#include "ga.h"
#include "expr.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <iostream>

GA::GA(int num, int chosen, int original_length, int chance, int mutate_times, std::vector<void (*)(const float &, const float &, float &)> avops, std::vector<std::string> avops_symb, int ran_max, int ran_min, float k_a, float k_b, std::vector<std::pair<float, float>> train_data)
{
    GA::avops = avops;
    GA::num = num;
    GA::chosen = chosen;
    GA::chance = chance;
    GA::avops_symb = avops_symb;
    GA::ran_max = ran_max;
    GA::ran_min = ran_min;
    GA::k_a = k_a;
    GA::k_b = k_b;
    GA::mutate_times = mutate_times;
    GA::train_data = train_data;
    GA::original_length = original_length;
    for (int i = 0; i < num; i++)
    {
        Expression temp = Expression(avops, avops_symb, ran_max, ran_min);
        temp.generate_random(original_length);
        GA::expressions.push_back(std::pair<Expression *, float>(temp.get_copy(), 0.0));
    }
}
GA::~GA()
{
    for (auto i = GA::expressions.begin(); i != GA::expressions.end(); i++)
    {
        delete i->first;
        i->first = NULL;
    }
}
void GA::evaluate()
{
    for (auto i = GA::expressions.begin(); i != GA::expressions.end(); i++)
    {
        // average error
        i->second = 0.0;
        for (auto it = GA::train_data.begin(); it != GA::train_data.end(); it++)
        {
            i->second += GA::evaluate_error(i->first, it->first, it->second);
        }
        i->second /= GA::train_data.size();
    }
}
void GA::iterate()
{
    //mutate and calculate fitness
    for (auto i = GA::expressions.begin(); i != GA::expressions.end(); i++)
    {
        int m_times = rand() % GA::mutate_times;
        for (int t = 0; t < m_times; t++)
        { 
            i->first->mutate(GA::chance);
        }
        // average error
        i->second = 0.0;
        for (auto it = GA::train_data.begin(); it != GA::train_data.end(); it++)
        {
            i->second += GA::evaluate_error(i->first, it->first, it->second);
        }
        i->second /= GA::train_data.size();
    }
    //selection
    GA::sort();
    // copy best
    std::vector<Expression *> chosens;
    for (int i = 0; i < GA::chosen; i++)
    {
        chosens.push_back(GA::expressions.at(i).first->get_copy());
    }
    for (int i = 0; i < GA::num; i++)
    {
        delete GA::expressions.at(i).first;
        GA::expressions.at(i).first = chosens.at(i % chosen)->get_copy();
    }
    for (auto it = chosens.begin(); it != chosens.end(); it++)
    {
        delete *it;
    }
}
std::string GA::get_solution()
{
    GA::evaluate();
    GA::sort();
    return GA::expressions.at(0).first->get_str();
}
std::vector<std::pair<Expression *, float>> GA::get_results()
{
    GA::evaluate();
    GA::sort();
    return GA::expressions;
}
float GA::evaluate_error(Expression *index, float x, float y)
{
    // mean error
    return std::abs((index->calculate(x) - y)) * GA::k_a + std::abs(index->get_length() - GA::original_length) * GA::k_b;
}
float GA::get_error()
{
    GA::evaluate();
    GA::sort();
    return GA::expressions.at(0).second;
}
void GA::print_results()
{
    GA::evaluate();
    GA::sort();
    for (int i = 0; i < num; i++)
    {
        std::printf("%d: %f\n", i, GA::expressions.at(i).second);
    }
}
void GA::print_error()
{
    GA::evaluate();
    GA::sort();
    std::printf("error: %f\n", GA::expressions.at(0).second);
}
void GA::sort()
{
    std::sort(GA::expressions.begin(), GA::expressions.end(), [](std::pair<Expression *, float> a, std::pair<Expression *, float> b)
              {
                  if (std::isnan(a.second) || std::isinf(a.second))
                  {
                      return false;
                  }
                  return a.second < b.second;
              });
}
