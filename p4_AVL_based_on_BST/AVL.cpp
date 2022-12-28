#include <iostream>
#include <math.h>
#include <memory>
#include <string>
#include <fstream>
#include <string.h>
#include "AVL.h"
using namespace std;

AVLNode* AVLTree::LL(AVLNode* Node){
    AVLNode *p,*tp; //create two temps 
    p = Node;//c
    tp = p->Right_;//b
    p->Right_ = tp->Left_;//b- to right child of c
    tp->Left_ = p;//c become right child of b
    updateHeight_family(tp); //update height 
    updateBF(tp);
    return tp; 
}

AVLNode* AVLTree::RR(AVLNode* Node){
    AVLNode *p,*tp; //create two temps            
    p = Node;//c           
    tp = p-> Left_; //b             
    p->Left_ = tp->Right_; //b+ to left child of c 
    tp->Right_ = p;//c become right child of b
    updateHeight_family(tp); //update height 
    updateBF(tp);
    return tp; 
}


AVLNode* AVLTree::LR(AVLNode* Node){
    AVLNode *p,*tp, *tp2;//create three temps for c, b ,a 
    p = Node;//c
    tp = p->Right_;//b
    tp2 =p->Right_->Left_;//a
    p->Right_ = tp2->Left_;//a- 
    p->height_ = AVLNodeHeight(p); //update height 
    tp->Left_ = tp2->Right_;//a+
    tp->height_ = AVLNodeHeight(tp);//update height 
    tp2->Left_ = p; //a left become c
    tp2->Right_ = tp; //a right is b
    tp2->height_ = AVLNodeHeight(tp2);//update height 
    updateBF(tp2); 
    return tp2; 
}

AVLNode* AVLTree::RL(AVLNode* Node){
    AVLNode *p,*tp, *tp2;//create three temps for c,b,a 
    p = Node;//c
    tp = p->Left_;//b
    tp2 =p->Left_->Right_; //a
    tp->Right_ = tp2->Left_; //a-
    tp->height_ = AVLNodeHeight(tp); //update height 
    p->Left_ = tp2->Right_;//a+
    p->height_ = AVLNodeHeight(p); //update height 
    tp2->Right_ = p;//a left become c
    tp2->Left_ = tp; //a right is b
    tp2->height_ = AVLNodeHeight(tp2); //update height 
    
    updateBF(tp2);
    return tp2; 
}

void AVLTree::updateHeight_family(AVLNode* Node) {
    Node->height_ = AVLNodeHeight(Node); 
    Node->Left_->height_ = AVLNodeHeight(Node->Left_);
    Node->Right_->height_ = AVLNodeHeight(Node->Right_);
}

void AVLTree::updateBF(AVLNode* Node){
    Node->BF_ = AVLNodeBF(Node); 
    Node->Left_->BF_ = AVLNodeBF(Node->Left_);
    Node->Right_->BF_ = AVLNodeBF(Node->Right_);
}

//insert + rotation 
AVLNode* AVLTree::Insert(int key, AVLNode* Node) {
    if(empty(Node)){ //when the tree is empty, then it's the root 
        AVLNode *newAVLNode = new AVLNode(key);
        Node = newAVLNode;
        size++;
        return(Node);
    }
    else if (key > Node->key) { //if it's larger then root, go right 
        Node->Right_ = Insert(key, Node->Right_);
    }
    else if( key < Node->key) {//if it's smaller, go left 
        Node->Left_ = Insert(key, Node->Left_);
    }
    else return Node;//already exist 
  
    Node->height_ = AVLNodeHeight(Node);//update the height 
    Node->BF_ =  AVLNodeBF(Node);//update the bf 

    //choose which rotation for t;
    if(Node->BF_ > 1 && Node->Right_->BF_ > 0)
        return LL(Node);
    if(Node->BF_ < -1 && Node->Left_->BF_ < 0)
        return RR(Node);
    if(Node->BF_ > 1 && Node->Right_->BF_ < 0)
        return LR(Node);
    if(Node->BF_ < -1 && Node->Left_->BF_ > 0)
        return RL(Node);
    return Node;
}

//find balance factor
int AVLTree::AVLNodeBF(AVLNode* Node) {
    int num_null = -1;
    if(Node->Left_ && Node->Right_) {//have 2 children
        return (Node->Right_->height_ - Node->Left_->height_);
    }
    else if(empty(Node->Left_) && Node->Right_ ){ //only right child
        return (Node->Right_->height_ - (num_null));//left is -1
    }
    else if(Node->Left_ && empty(Node->Right_)){//only left child
        return ((num_null) - Node-> Left_ -> height_);//right is -1
    }
    else
        return 0;
}

// find AVLNode height_ 
int AVLTree::AVLNodeHeight(AVLNode* Node){
    int height = 0;
    if(empty(Node->Left_) && empty(Node->Right_)) { //the leaf
        Node->BF_ = height;//if both empty, bf is the height 
        return height;
    }
    if(empty(Node->Left_)){ //only right child
        height = Node->Right_->height_ + 1;
        return height;
    }
    else if(empty(Node->Right_)) { //onlye left child 
        height =Node->Left_->height_ + 1;
        return height;
    }
    //find the taller height
    return max(Node->Left_->height_, Node->Right_->height_) + 1;
}

bool AVLTree::empty(AVLNode* Node){
    return Node ==NULL;
}

int AVLTree::Size(){
    return size;
}

AVLNode* AVLTree::getroot(){
    return root;
}

void AVLTree::setroot(AVLNode* c){
    root = c;
}

