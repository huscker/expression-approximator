#include "expr.h"
#include <vector>
#include <algorithm>
#include <random>
#include <exception>
#include <iostream>
#include <iomanip>
struct Node{
    bool leftVar;
    bool rightVar;
    int leftData;
    int rightData;
    void(* op) (const float & ,const float & ,float & );
    std::string symb;
    struct Node * left;
    struct Node * right;
};

std::vector<Node **> get_leaves(Node * current){
    std::vector<Node **> temp;
    if (current->left == NULL){
        temp.push_back(&current->left);
    }
    else{
        std::vector<Node **> t = get_leaves(current->left);
        std::copy(t.begin(),t.end(),std::back_inserter(temp));
    }
    if (current->right == NULL){
        temp.push_back(&current->right);
    }
    else{
        std::vector<Node **> t = get_leaves(current->right);
        std::copy(t.begin(),t.end(),std::back_inserter(temp));
    }
    return temp;
}
void delete_tree(Node * tree){
    if(tree != NULL){
        if(tree->left != NULL){
            delete_tree(tree->left);
        }
        if(tree->right != NULL){
            delete_tree(tree->right);
        }
        delete tree;
    }
}
void postorder(Node* p,int indent=0){
    if(p != NULL) {
        if(p->right) {
            postorder(p->right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout<< p->symb << "\n ";
        if(p->left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            postorder(p->left, indent+4);
        }
    }
}
std::string infix(Node * p){
    std::string res = "(";
    if(p->left == NULL){
        if(p->leftVar){
            res+='x';
        }else{
            res+=std::to_string(p->leftData);
        }
    }else{
        res+=infix(p->left);
    }
    res+=p->symb;
    if(p->right == NULL){
        if(p->rightVar){
            res+='x';
        }else{
            res+=std::to_string(p->rightData);
        }
    }else{
        res+=infix(p->right);
    }
    res+=')';
    return res;
}
unsigned int count(Node* p){
    unsigned int res = 1;
    if (p->left != NULL)
    {
        res += count(p->left);
    }
    if (p->right != NULL)
    {
        res += count(p->right);
    }
    return res;
}
unsigned int get_branch_at(Node * p,const unsigned int pos,Node ** out){
    unsigned int res = 1;
    if (p->left != NULL)
    {
        res += get_branch_at(p->left,pos,out);
    }
    if (p->right != NULL)
    {
        res += get_branch_at(p->right,pos,out);
    }
    if(res == pos){
        out = &p;
    }
    return res;
}
float get_result(Node* p,float x){
    float t1,t2,res;
    if(p->left != NULL){
        t1 = get_result(p->left,x);
    }else if(p->leftVar){
        t1 = x;
    }else {
        t1 = p->leftData;
    }
    if(p->right != NULL){
        t2 = get_result(p->right,x);
    }else if(p->rightVar){
        t2 = x;
    }else {
        t2 = p->rightData;
    }
    p->op(t1,t2,res);
    return res;
}

Expression::Expression(std::vector<void(*)(const float & ,const float & ,float & )> avops,std::vector<std::string> avops_symb,int ran_max,int ran_min){
    Expression::ran_max = ran_max;
    Expression::ran_min = ran_min;
    Expression::avops = avops;
    Expression::avops_symb = avops_symb;
    Expression::tree = NULL;
    srand(time(0));

}
Expression::~Expression(){
    delete_tree(Expression::tree);
}

void Expression::fill_tree(Node * node){
    if(node->left==NULL){
        if(rand() % 2 == 1){
            node->leftVar = true;
        }
        else{
            node->leftData = rand() % (Expression::ran_max-Expression::ran_min) + Expression::ran_min;
        }
    }else{
        fill_tree(node->left);
    }
    if(node->right==NULL){
        if(rand() % 2 == 1){
            node->rightVar = true;
        }
        else{
            node->rightData = rand() % (Expression::ran_max-Expression::ran_min) + Expression::ran_min;
        }
    }else{
        fill_tree(node->right);
    }
}

void Expression::generate_random(unsigned int n){
    if (n<1){
        printf("Invalid argument. Force quiting.");
        exit(EXIT_FAILURE);
    }
    delete_tree(Expression::tree);
    // generate nodes
    unsigned int r = rand() % avops.size();
    Node * temp = new Node;
    temp->leftVar = false;
    temp->rightVar = false;
    temp->leftData = 0;
    temp->rightData = 0;
    temp->op = Expression::avops.at(r);
    temp->symb = Expression::avops_symb.at(r);
    temp->left = NULL;
    temp->right = NULL;
    for(int i = 1;i<n;i++){
        std::vector<Node **> leaves = get_leaves(temp);
        r = rand() % avops.size();
        Node * t = new Node;
        t->leftVar = false;
        t->rightVar = false;
        t->leftData = 0;
        t->rightData = 0;
        t->op = Expression::avops.at(r);
        t->symb = Expression::avops_symb.at(r);
        t->left = NULL;
        t->right = NULL;
        *leaves.at(rand() % leaves.size()) = t;
    }
    // fill nodes 
    Expression::fill_tree(temp);
    Expression::tree = temp;
}
void Expression::mutate(){
    
}
float Expression::calculate(float x){
    return get_result(Expression::tree,x);
}
std::string Expression::get_str(){
    return infix(Expression::tree);
}
void Expression::print_tree(){
    postorder(Expression::tree);
}
unsigned int Expression::get_length(){
    return count(Expression::tree);
}
Expression Expression::cross(Expression othr){

}