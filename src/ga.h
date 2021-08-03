#ifndef GA_H
#define GA_H
#include <vector>
#include "expr.h"

class GA{
    private:
        std::vector<std::pair<Expression *,float>> expressions;
        unsigned int num;
        unsigned int original_lentgh;
        int chance;
        std::vector<void(*)(const float & ,const float & ,float & )> avops;
        std::vector<std::string> avops_symb;
        std::vector<std::pair<float,float>> train_data;
        int ran_max,ran_min;
        float evaluate_error(Expression * index,float x, float y); // value, expected result
        float k_a,k_b;
    public:
        GA(
            unsigned int num,
            unsigned int original_lentgh,
            int chance,
            std::vector<void(*)(const float & ,const float & ,float & )> avops,
            std::vector<std::string> avops_symb,
            int ran_max,
            int ran_min,
            float k_a,
            float k_b,
            std::vector<std::pair<float,float>> train_data
        );
        ~GA();
        void iterate();
        std::string get_solution();
        std::vector<std::pair<Expression*, float> > get_results();
};

#endif // !GA_H