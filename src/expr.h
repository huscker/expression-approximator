#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <string>

struct Node; // node containing one operation of expression

// util. functions:
std::vector<Node **> get_leaves(Node *current);              // get nodes with that has at least one null child
std::vector<Node **> get_othr_leaves(Node *current);         // get nodes with both children being null
void postorder(Node *p, int indent);                         // print node tree
std::string infix(Node *p);                                  // get infix form of a node tree
void delete_tree(Node *tree);                                // delete node tree
int count(Node *p);                                          // count nodes in a node tree
float get_result(Node *p, float x);                          // calculate result
Node **get_branch_at(Node **p, const int pos, int &counter); // get node at specific position
Node **get_parent_of(Node *pos, Node *tree);                 // get parent node (if it is not root)
Node *copy_tree(Node *tree);                                 // get copy of a node tree
Node *copy_node(Node *node);                                 // get copy of a node

class Expression
{
private:
    Node *tree;                                                         // node tree as expression
    std::vector<void (*)(const float &, const float &, float &)> avops; // available operations
    std::vector<std::string> avops_symb;                                // symbols for available operations
    int ran_max;                                                        // max number produced by random generator for using as constants
    int ran_min;                                                        // min number produced by random generator for using as constants

    void fill_tree(Node *node);   // fill pre-generated node tree with random constants
    Node *create_node();          // create new node

public:
    Expression(std::vector<void (*)(const float &, const float &, float &)> avops,
               std::vector<std::string> avops_symb,
               int ran_max,
               int ran_min);
    Expression(Node *tree,
               std::vector<void (*)(const float &, const float &, float &)> avops,
               std::vector<std::string> avops_symb,
               int ran_max,
               int ran_min);
    ~Expression();                       // clear memory
    void generate_random(int n);         // generate structure of Expression::tree and fill it
    void mutate(int chance);             // modify, add, remove nodes in Expression::tree
    void mutate_keep_length(int chance); // modify nodes in Expression::tree
    void print_tree();                   // call postorder
    float calculate(float x);            // get result of expression
    int get_length();                    // count nodes in Expression::tree
    std::string get_str();               // get infix form of expression
    Expression *get_copy();              // get copy of expression
};

#endif // !EXPR_H
