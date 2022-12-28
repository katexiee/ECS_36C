#include <iostream>
#include <fstream>
#include <string.h>
#include "AVL.h"
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

void printjson(json& outputObj, AVLNode* n, int root);

int main(int argc, char** argv) {
    if(argc != 2) {
        cerr << "Usage: not enough files in the argument" <<  endl;
        return 1;
    }
    ifstream fn;
    fn.open(argv[1]);
    json jsonobj;
    fn >> jsonobj;
    AVLTree Tree = AVLTree();
    for(auto i = jsonobj.begin(); i != jsonobj.end(); ++i){
        if(i.key() == "metadata")
            break;
        AVLNode* root_ = Tree.getroot();
        Tree.setroot(Tree.Insert(i.value()["key"],root_));
    }

    json outputObj;
    printjson(outputObj, Tree.getroot(), Tree.getroot()->key); //store the result into outputObj
    outputObj["size"] = Tree.Size();
    // Print final result
     cout << outputObj.dump(2);
}


void printjson(json& outputObj, AVLNode* Node, int root) {
    if(Node == NULL) {
        return; 
    }
    string num = to_string(Node->key);
    outputObj[num]["balance factor"] = Node->BF_;
    outputObj[num]["height"] = Node->height_;
    // add left and right child
    if(Node->Left_ != NULL) 
        outputObj[num]["left"] = Node->Left_->key;
    if(Node->Right_ != NULL)
        outputObj[num]["right"] = Node->Right_->key;
    if(Node->key != root)
        outputObj[num]["parent"] = root;
    else{
        outputObj[num]["root"] = true;
        outputObj["height"] = Node->height_;
        outputObj["root"] = Node->key;
    }
    printjson(outputObj, Node->Left_, Node->key);
    printjson(outputObj, Node->Right_, Node->key);
}
