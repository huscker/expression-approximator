#include "src/expr.h"
#include <vector>
#include <iostream>
#include <string>
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
    std::vector<void(*)(const float & ,const float & ,float & )> avops;
    std::vector<std::string> avops_symb = {"+","-","*","/"};
    avops.push_back(add);
    avops.push_back(sub);
    avops.push_back(mul);
    avops.push_back(div);
    Expression expr(avops,avops_symb,100,1);
    expr.generate_random(30);
    expr.print_tree();
    std::cout << expr.get_str() << std::endl << expr.get_length() << std::endl;
    std::cout << expr.calculate(30.3);
    return 0;
}