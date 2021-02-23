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
    void * op;
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

void Expression::generate_random(int n){
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
    temp->op = &Expression::avops.at(r);
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
        t->op = &Expression::avops.at(r);
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
float Expression::calculate(){

}
int Expression::get_str(char * out){

}
void Expression::print_tree(){
    postorder(Expression::tree);
}
Expression Expression::cross(Expression othr){

}