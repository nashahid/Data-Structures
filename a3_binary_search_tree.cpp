#include "a3_binary_search_tree.hpp"
#include <iostream> 
using namespace std; 

// Nabeel Shahid 20460189
// Jonathan Chan 20521786


//helper functions
unsigned int h_depth(BinarySearchTree::Node* node);
BinarySearchTree::Node* getParent(BinarySearchTree::DataType val, BinarySearchTree::Node* root);
BinarySearchTree::Node* getNode(BinarySearchTree::DataType val, BinarySearchTree::Node* root);
bool left_child(BinarySearchTree::DataType val, BinarySearchTree::Node* parent);
BinarySearchTree::Node* mini(BinarySearchTree::Node* node);
void printer(BinarySearchTree::Node *index);


// strcut constrcutor 
BinarySearchTree::Node::Node(DataType newval){
    
    val = newval;
    right = NULL;
    left = NULL;
}

BinarySearchTree::BinarySearchTree() {
    
    root_ = NULL ;
    size_ = 0;
    
}

BinarySearchTree::~BinarySearchTree(){
    
    while(size_ >0){
        remove(root_->val);
    }
}

unsigned int BinarySearchTree::size() const{
    
    return size_; 
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    
    Node* temp;
    temp = root_;
    
    while(temp->right !=NULL) {
        
        temp = temp->right; 
    }

    return temp->val;  
}

BinarySearchTree::DataType BinarySearchTree::min() const{
    
    Node* temp;
    temp = root_;
    
    while(temp->left !=NULL) {
        
        temp = temp->left;
    }
    
    return temp->val;
}

unsigned int BinarySearchTree::depth() const {
    
    unsigned int depth = (h_depth(root_)); 
    return depth; 
    
}


void BinarySearchTree::print() const{
    
    //recurses through the nodes in the binary tree
    printer(root_);
    
}

bool BinarySearchTree::exists(DataType val) const {

    if (root_ == NULL){
        
        return false; 
    }
    
    Node* temp; 
    temp = root_ ;
    
    while (temp != NULL) {
    
        if (temp->val == val){
            return true;
        }
    
        else if (val < temp->val) {
            
            temp = temp->left;
        }
            
        else{
            
            temp = temp->right;
        }
    
    }
    
    return false; 
    
}

bool BinarySearchTree::insert(DataType val){
    
    //condition 1 - the value already exists 
    if (exists(val)){
        
        return false; 
    }
   
    Node* insert = new Node(val);
    
    // condition 2 - the list is empty - insetertd node is root node 
    if (size_== 0) {
        
      root_ = insert;
      size_++;
      return true;
        
    }
    
    //condition 3 - regular insert
    
    bool filled = false;
    Node* temp;
    temp = root_; 

    while(filled == false) {
        
        if (val > temp->val){
            
            if(temp->right == NULL){
                temp->right = insert;
                filled = true;
            }
            
            else{
               temp = temp->right;
            }
        }
        else if (val < temp->val) {
            
            if(temp->left == NULL){
                temp->left = insert;
                filled = true;
            }
            
            else{
                temp = temp->left;
            }

        }
    }
     
    size_++;
    return true; 

}


bool BinarySearchTree::remove(DataType val){
    
    if (size_==0){
        
        return false; 
    }
    
    if (!exists(val)){
        
        return false; 
    }
    
    
    Node* node = getNode(val, root_);
    Node* parent = NULL; 
    
    if (node != root_) {
   
        parent = getParent(val, root_);
    }
    
    // case 1: is leaf node 
    if (node->right == NULL && node->left == NULL){
        
        if (node!=root_) {
            
            if (left_child(val, parent)){
            
            parent->left = NULL;
            }
        
            else{
                parent->right = NULL;
            }
            
        }
        
        else {
            root_ = NULL;
        }
    }
    
    // case 2: Has 1 child
    
    else if (node->left == NULL && node->right != NULL){
        
        if(node != root_){
        
            if (left_child(val, parent)){
            
            parent->left = node-> right;
            }
        
            else{
                parent->right = node->right;
            }

        }
        
        else {
            root_ = root_->right;   
            }
    }
    
    
    else if (node->left != NULL && node->right == NULL) {
        
        if(node != root_){

            if (left_child(val, parent)){
            
                parent->left = node->left;
            }
        
            else{
                parent->right = node->left;
            }
        }
        
        else{
            root_ = root_->left;
        }
    }
    
    //case 3: Has 2 children
    else if (node->left != NULL && node->right != NULL){
        
        Node* temp;
        temp = mini(node->right);
        
        node->val = temp->val;
        
        
        parent = getParent(temp->val, node);

        if (parent != NULL){
            parent->left = NULL ;
        }
        else{
            root_->right = NULL;
        }
        
        size_-- ;
        delete temp; 
        return true;
        
    }

    
    size_-- ;
    delete node;
    return true;

}




// helper function which returns the depth of a BST given a root node as its argument

unsigned int h_depth(BinarySearchTree::Node* node){
    
    if (node == NULL){
        
        return 0; 
    }
    
    if ((node->left != NULL) && (node->right!= NULL)){
        
        if (h_depth(node->left) > h_depth(node->right)){
            
            return (1 + h_depth(node->left)) ; 
        }
        
        else {
            
            return (1 + h_depth(node->right)) ;
        }
    }
    
            
    else {
        
        if (node->left == NULL) {
            
            return (1 + h_depth(node->right));
        }
        
        if (node->right == NULL){
            
            return (1 + h_depth(node->left));
        }
    }

    return 0;
}

// helper function (for the remove function) returns the parent to the node with a given value, asumptions: BST is NOT EMPTY and that the value does in fact EXIST in the BST, and is NOT ROOT NODE

BinarySearchTree::Node* getParent(BinarySearchTree::DataType val, BinarySearchTree::Node* root){
    
    
    if  (root!=NULL){
        
        if (root->val == val) {
            
            return NULL; 
        }
    }

    
    BinarySearchTree::Node* temp;
    temp = root; 
    bool found = false;
    
    while(found == false){
        
        if (temp->right != NULL){
            
            if (temp->right->val == val){
                found = true;
            }
        
            else if(val > temp->val){
                temp = temp->right;
            }
        }
        
        if (temp->left != NULL){
            
            if (temp->left->val == val){
                found = true;
            }
            
            else if(val < temp->val){
                temp = temp->left;
            }

        }
    }
    
     return temp;
        
}
 


// helper func for remove
BinarySearchTree::Node* getNode(BinarySearchTree::DataType val, BinarySearchTree::Node* root){
    
    BinarySearchTree::Node* parent = getParent(val, root);
    
    if (parent != NULL){
        
        if (left_child(val, parent)){
        
            return parent->left;
        }
        
        return parent->right;
    }
    
    else{
    
        return root;
    }
}

// helper: returns wheather the node with the value is the left child of the parent, (if not then is right)  
bool left_child(BinarySearchTree::DataType val, BinarySearchTree::Node* parent){
    
    
    BinarySearchTree::Node* temp = parent;
    
    if (temp->left != NULL){
        
        if (val < temp->val)
            
            return true;
    }
    
    return false;
}


// helper min function for remove - return min node
BinarySearchTree::Node* mini(BinarySearchTree::Node* node){
    
    BinarySearchTree::Node* temp;
    temp = node;
    
    while(temp->left !=NULL) {
        
        temp = temp->left;
    }
    
    return temp;
}

//recurses through the nodes in the binary tree
void printer(BinarySearchTree::Node *index){
 
    if (index==NULL)
        return;
    else
    {
        cout<<index->val<<endl;
        printer(index->left);
        printer(index->right);
    }
}
