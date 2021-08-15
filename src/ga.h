#ifndef GA_H
#define GA_H

#include <vector>
#include "expr.h"

class GA
{
private:
    std::vector<std::pair<Expression *, float>> expressions;            // array of expressions
    int num;                                                            // number of expressions
    int chosen;                                                         // number of selected expressions
    int original_length;                                                // original number of nodes
    int chance;                                                         // chance to mutate selected node
    int mutate_times;                                                   // number of nodes to be mutated
    std::vector<void (*)(const float &, const float &, float &)> avops; // available operations
    std::vector<std::string> avops_symb;                                // symbols for available operations
    std::vector<std::pair<float, float>> train_data;                    // self explanatory
    int ran_max;                                                        // max number produced by random generator for using as constants
    int ran_min;                                                        // min number produced by random generator for using as constants
    float evaluate_error(Expression *index, float x, float y);          // calculate linear error
    float k_a;                                                          // delta coeficient
    float k_b;                                                          // length coeficient
public:
    GA(
        int num,                                                            // number of expressions
        int chosen,                                                         // number of selected expressions
        int original_length,                                                // original number of nodes
        int chance,                                                         // chance to mutate selected node
        int mutate_times,                                                   // number of nodes to be mutated
        std::vector<void (*)(const float &, const float &, float &)> avops, // available operations
        std::vector<std::string> avops_symb,                                // symbols for available operations
        int ran_max,                                                        // max number produced by random generator for using as constants
        int ran_min,                                                        // min number produced by random generator for using as constants
        float k_a,                                                          // delta coeficient
        float k_b,                                                          // length coeficient
        std::vector<std::pair<float, float>> train_data);                   //train data (value, expected result)
    ~GA();                                                                  // clear memory
    void iterate();                                                         // generate next generation
    void evaluate();                                                        // calculate fitness
    void sort();                                                            // sort expressions
    std::string get_solution();                                             // get solution with the lowest error
    float get_error();                                                      // get error of the best solution
    std::vector<std::pair<Expression *, float>> get_results();              // get copy of expressions
    void print_results();                                                   // print info about expressions
    void print_error();                                                     // print error of the best solution
};

#endif // !GA_H
