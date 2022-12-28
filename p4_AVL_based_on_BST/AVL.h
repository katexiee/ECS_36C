#ifndef AVL_H
#define AVL_H

#include <iostream>
// #include "json.hpp"

class AVLNode {
    public:
        // Constructor
        AVLNode(int k){
            key = k; Left_ = NULL; Right_ = NULL; height_ = 0; BF_ = 0;
        }
        
        //data
        AVLNode *Left_;
        AVLNode *Right_;
        int key;
        int height_;
        int BF_;
};

class AVLTree {
    public:
        // Constructor
        AVLTree() {root = NULL;size = 0;}
        //rotations:
        AVLNode* LL(AVLNode * Node);
        AVLNode* RR(AVLNode * Node);
        AVLNode* LR(AVLNode * Node);
        AVLNode* RL(AVLNode * Node);
        //rotation helper 
        void updateHeight_family(AVLNode * Node);
        void updateBF(AVLNode * Node);

        AVLNode* Insert(int key, AVLNode* Node);
        
        int AVLNodeBF(AVLNode * Node);
        int AVLNodeHeight(AVLNode * Node);
        bool empty(AVLNode* Node);
        AVLNode* getroot();
        void setroot(AVLNode*Node);
        int Size();
        
    private:
        AVLNode* root;
        int size;
};

#endif



