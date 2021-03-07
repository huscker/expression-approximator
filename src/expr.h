#ifndef EXPR_H
#define EXPR_H
#include <vector>
#include <string>

struct Node;

std::vector<Node **> get_leaves(Node * current);
std::vector<Node **> get_othr_leaves(Node* current);
void postorder(Node * p,int indent);
std::string infix(Node * p);
void delete_tree(Node * tree);
unsigned int count(Node* p);
float get_result(Node* p,float x);
void get_branch_at(Node *p,const unsigned int pos,Node ** out,unsigned int & counter);
Node ** get_parent_of(Node* pos,Node* tree);
Node * copy_tree(Node* tree);
Node * copy_node(Node* node);

class Expression{
    private:
        Node * tree;
        std::vector<void(*)(const float & ,const float & ,float & )> avops;
        std::vector<std::string> avops_symb;
        int ran_max,ran_min;

    public:
        Expression(std::vector<void(*)(const float & ,const float & ,float & )> avops,std::vector<std::string> avops_symb,int ran_max,int ran_min);
        Expression(Node* tree,std::vector<void(*)(const float & ,const float & ,float & )> avops,std::vector<std::string> avops_symb,int ran_max,int ran_min);
        ~Expression();
        void fill_tree(Node * node);
        void generate_random(unsigned int n);
        void mutate(int chance);
        float calculate(float x);
        std::string get_str();
        unsigned int get_length();
        void print_tree();
        Node * create_node();
        Expression get_copy();
        Expression cross(Expression othr);
};

#endif // !EXPR_H