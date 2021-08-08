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
std::vector<Node **> get_othr_leaves(Node* current){
    std::vector<Node **> temp;
    if(current->left != NULL){
        if(current->left->left == NULL && current->left->right == NULL){
            temp.push_back(&current->left);
        }else{
            std::vector<Node **> t = get_othr_leaves(current->left);
            std::copy(t.begin(),t.end(),std::back_inserter(temp));
        }
    }
    if(current->right != NULL){
        if(current->right->left == NULL && current->right->right == NULL){
            temp.push_back(&current->right);
        }else{
            std::vector<Node **> t = get_othr_leaves(current->right);
            std::copy(t.begin(),t.end(),std::back_inserter(temp));
        }
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
int count(Node* p){
    int res = 1;
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
Node ** get_branch_at(Node **p, const int pos,int & counter){
    if(pos == counter){
        return p;
    }
    Node ** t = NULL;
    if((*p)->left != NULL){
        counter++;
        t = get_branch_at(&((*p)->left),pos,counter);
    }
    if(t != NULL){
        return t;
    }
    if((*p)->right != NULL){
        counter++;
        t = get_branch_at(&((*p)->right),pos,counter);
    }
    return t;
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
Node ** get_parent_of(Node* pos,Node* tree){
    Node ** t = NULL;
    if(tree->left != NULL){
        if(tree->left->left == pos || tree->left->right == pos){
            return &tree->left;
        }else{
            t = get_parent_of(pos,tree->left);
        }
    }
    if(t!=NULL){
        return t;
    }
    if(tree->right != NULL){
        if(tree->right->left == pos || tree->right->right == pos){
            return &tree->right;
        }else{
            t = get_parent_of(pos,tree->right);
        }
    }
    return t;
}
Node * copy_tree(Node* tree){
    Node * res = copy_node(tree);
    if(res->left != NULL){
        res->left = copy_tree(tree->left);
    }
    if(res->right != NULL){
        res->right = copy_tree(tree->right);
    }
    return res;
}
Node * copy_node(Node* node){
    Node * res = new Node;
    res->left = node->left;
    res->leftData = node->leftData;
    res->leftVar = node->leftVar;
    res->op = node->op;
    res->right = node->right;
    res->rightData = node->rightData;
    res->rightVar = node->rightVar;
    res->symb = node->symb;
    return res;
}

Expression::Expression(std::vector<void(*)(const float & ,const float & ,float & )> avops,std::vector<std::string> avops_symb,int ran_max,int ran_min){
    Expression::ran_max = ran_max;
    Expression::ran_min = ran_min;
    Expression::avops = avops;
    Expression::avops_symb = avops_symb;
    Expression::tree = NULL;

}
Expression::Expression(Node* tree,std::vector<void(*)(const float & ,const float & ,float & )> avops,std::vector<std::string> avops_symb,int ran_max,int ran_min){
    Expression::ran_max = ran_max;
    Expression::ran_min = ran_min;
    Expression::avops = avops;
    Expression::avops_symb = avops_symb;
    Expression::tree = copy_tree(tree);
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
Node * Expression::create_node(){
    int r = rand() % Expression::avops.size();
    Node * temp = new Node;
    temp->leftVar = false;
    temp->rightVar = false;
    temp->leftData = 0;
    temp->rightData = 0;
    temp->op = Expression::avops.at(r);
    temp->symb = Expression::avops_symb.at(r);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void Expression::generate_random(int n){
    if (n<1){
        printf("Invalid argument. Force quiting.");
        exit(EXIT_FAILURE);
    }
    delete_tree(Expression::tree);
    // generate nodes
    int r = rand() % avops.size();
    Node * temp = Expression::create_node();
    for(int i = 1;i<n;i++){
        std::vector<Node **> leaves = get_leaves(temp);
        r = rand() % avops.size();
        Node * t = create_node();
        *leaves.at(rand() % leaves.size()) = t;
    }
    // fill nodes 
    Expression::fill_tree(temp);
    Expression::tree = temp;
}
void Expression::mutate(int chance){ // chance <- percentage, mutate 1 time
    if (rand() % 100 < chance){
        //mutate leaves
        Node **p = NULL;
       	int choice = rand() % 3;
	if(choice==0){ //modify
            int c = 0;
            p = get_branch_at(&(Expression::tree),rand() % count(Expression::tree),c);
	    if(p == NULL){
                printf("Unknown error. Quitting.\n");
                exit(EXIT_FAILURE);
            }
            Node * temp = create_node();
            fill_tree(temp);
            temp->left = (*p)->left;
            temp->right = (*p)->right;
            delete (*p);
            (*p) = temp;
        }if(choice==1){ // append new
            std::vector<Node **> leaves = get_leaves(Expression::tree);
            p = leaves.at(rand()%leaves.size());
            Node * temp = create_node();
            fill_tree(temp);
            *p = temp;
        }if(choice==2){ // delete
            std::vector<Node **> leaves = get_othr_leaves(Expression::tree);
	    if (leaves.size() <= 1){return;}
	    p = leaves.at(rand()%leaves.size());
	    Node ** parent = get_parent_of((*p),Expression::tree);
	    if (parent == NULL){
		parent = &(Expression::tree);
	    }
	    if((*parent)->left == (*p)){
                delete (*parent)->left;
                (*parent)->left = NULL;
                if(rand() % 2 == 1){
                    (*parent)->leftVar = true;
                }
                else{
                    (*parent)->leftData = rand() % (Expression::ran_max-Expression::ran_min) + Expression::ran_min;
                }
            }
            if((*parent)->right == (*p)){
                delete (*parent)->right;
                (*parent)->right = NULL;
                if(rand() % 2 == 1){
                    (*parent)->rightVar = true;
                }
                else{
                    (*parent)->rightData = rand() % (Expression::ran_max-Expression::ran_min) + Expression::ran_min;
                }
            }
        }
    }

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
Expression* Expression::get_copy(){
    return new Expression(Expression::tree,Expression::avops,Expression::avops_symb,Expression::ran_max,Expression::ran_min);
}
