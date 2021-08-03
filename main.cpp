//#include "src/expr.h"
#include "src/ga.h"
#include <vector>
#include <iostream>
#include <string>
#include <random>
void add(const float & a,const float & b,float & c){
    c= a+b;
}
void sub(const float & a,const float & b,float & c){
    c= a-b;
}
void mul(const float & a,const float & b,float & c){
    c= a*b;
}
void div(const float & a,const float & b,float & c){
    c= a/b;
}

int main(){
    srand(time(NULL));
    std::vector<void(*)(const float & ,const float & ,float & )> avops;
    std::vector<std::string> avops_symb = {"+","-","*","/"};
    avops.push_back(add);
    avops.push_back(sub);
    avops.push_back(mul);
    avops.push_back(div); 
    std::vector<std::pair<float,float>> train_data = {
        std::pair<float,float>(1.0,1.0),
        std::pair<float,float>(2.0,4.0),
        std::pair<float,float>(3.0,9.0),
        std::pair<float,float>(4.0,16.0),
        std::pair<float,float>(5.0,25.0)
    };
    //A ga = GA(10,15,10,avops,avops_symb,100,0,1.0,0.0,train_data);
    //ga.iterate();
    
    
    Expression expr(avops,avops_symb,100,1);
    expr.generate_random(3);
    expr.print_tree();
    std::cout << std::endl;
    std::cout << expr.get_str() << std::endl << expr.get_length() << std::endl;
    std::cout << expr.calculate(30.3) << std::endl;
    expr.mutate(1);
    /*
    Expression expr2 = expr.get_copy();
    expr2.mutate(1000);
    std::cout << expr2.get_str() << std::endl << expr2.get_length() << std::endl;
    std::cout << expr2.calculate(30.3) << std::endl;*/

    return 0;
}