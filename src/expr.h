#ifndef EXPR_H
#define EXPR_H
#include <vector>
#include <string>

struct Node;

std::vector<Node **> get_leaves(Node * current);
void postorder(Node * p,int indent);
void delete_tree(Node * tree);

class Expression{
    private:
        Node * tree;
        std::vector<void(*)(const float & ,const float & ,float & )> avops;
        std::vector<std::string> avops_symb;
        int ran_max,ran_min;

    public:
        Expression(std::vector<void(*)(const float & ,const float & ,float & )> avops,std::vector<std::string> avops_symb,int ran_max,int ran_min);
        ~Expression();
        void fill_tree(Node * node);
        void generate_random(int n);
        void mutate();
        float calculate();
        int get_str(char * out);
        void print_tree();
        Expression cross(Expression othr);
};

#endif // !EXPR_H