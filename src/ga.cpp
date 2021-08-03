#include "ga.h"
#include "expr.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <iostream>

// TODO: check if inf or nan

GA::GA(unsigned int num,unsigned int original_lentgh,int chance,std::vector<void(*)(const float & ,const float & ,float & )> avops,std::vector<std::string> avops_symb,int ran_max,int ran_min,float k_a,float k_b,std::vector<std::pair<float,float>> train_data){
    GA::avops = avops;
    GA::num = num; 
    GA::chance = chance;
    GA::avops_symb = avops_symb;
    GA::ran_max = ran_max;
    GA::ran_min = ran_min;
    GA::k_a = k_a;
    GA::k_b = k_b;
    GA::train_data = train_data;
    GA::original_lentgh = original_lentgh;
    Expression temp = Expression(avops,avops_symb,ran_max,ran_min);
    temp.generate_random(original_lentgh);
    for(unsigned int i =0;i<num;i++){
        GA::expressions.push_back(std::pair<Expression *,float>(temp.get_copy(),0.));
    }
}
GA::~GA(){
    for(auto i = GA::expressions.begin();i!=GA::expressions.end();i++){
        delete i->first;
        i->first = NULL;
    }
}
void GA::iterate(){
    //mutate and calculate fitness
    for(auto i = GA::expressions.begin();i!=GA::expressions.end();i++){
        i->first->mutate(GA::chance);
        // average 
        i->second = 0.0;
        for(auto it = GA::train_data.begin(); it != GA::train_data.end();it++){
            i->second += GA::evaluate_error(i->first,it->first,it->second);
        }
        i->second /= GA::train_data.size();
    }
    //selection
    std::sort(GA::expressions.begin(),GA::expressions.end(),[](std::pair<Expression *,float> a,std::pair<Expression *,float>  b) {
        return a.second < b.second;
    });
    for(auto i = GA::expressions.begin();i!=GA::expressions.end();i++){
        std::cout << i->first->get_str() << " " << i->second << std::endl;
    }
    // get child
    Expression * t = GA::expressions.at(0).first->get_copy();
    for(unsigned int i = 0;i<num;i++){ 
        delete GA::expressions.at(i).first;
        GA::expressions.at(i).first = t->get_copy();
    }
    delete t;
}
std::string GA::get_solution(){
    std::sort(GA::expressions.begin(),GA::expressions.end(),[](std::pair<Expression *,float> a,std::pair<Expression *,float>  b) {
        return a.second < b.second;
    });
    return GA::expressions.at(0).first->get_str();
}
std::vector<std::pair<Expression *,float>> GA::get_results(){
    std::sort(GA::expressions.begin(),GA::expressions.end(),[](std::pair<Expression *,float> a,std::pair<Expression *,float>  b) {
        return a.second < b.second;
    });
    return GA::expressions;
}
float GA::evaluate_error(Expression * index,float x, float y){
    // mean error
    return std::abs((index->calculate(x) - y))*GA::k_a + index->get_length()*GA::k_b;
}