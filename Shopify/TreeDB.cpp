#include "TreeDB.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

//  Creates a new TreeDB object
//  Root initially points to NULL and probesCount is 0
TreeDB::TreeDB() {
    root = NULL;
    probesCount = 0;
}

// Calls the "clear" function that is defined later
TreeDB::~TreeDB() {
    clear();
}

// Checks whether there is a root. If there isn't a root,
// then it creates a TreeNode entry there. Otherwise, it calls
// the helper function.
bool TreeDB::insert(DBentry* newEntry) {
    if(root == NULL) {
        root = new TreeNode(newEntry);
        return true;
    }
    
    return insertHelper(root, newEntry);
}

//  Inserts a new node by comparing the "title" string of the current node
//  and the newEntry. Recursively traverses the tree.
bool TreeDB::insertHelper(TreeNode* root, DBentry* newEntry) {
    int stringCompare;

    stringCompare = (root -> getEntry() -> getTitle()).compare(newEntry -> getTitle());
    
    if(stringCompare == 0) {
        return false;
    }
    
    if(stringCompare < 0) {
        if(root -> getRight() == NULL) {
            root -> setRight(new TreeNode(newEntry));
        } else {
            return insertHelper(root -> getRight(), newEntry);
        }
    } else if(stringCompare > 0) {
        if(root -> getLeft() == NULL) {
            root -> setLeft(new TreeNode(newEntry));
        } else {
            return insertHelper(root -> getLeft(), newEntry);
        }
    }
    return true;
}

// Calls the helper function.
DBentry* TreeDB::find(string name) {
    probesCount = 0;
    return findHelper(root, name);
}

// Recursively traverses through the tree by comparing the "name" string of the current
// node to the "name" string specified by the user.
DBentry* TreeDB::findHelper(TreeNode* root, string name) {
    probesCount++;
    int stringCompare;
    if(root == NULL) return NULL;
    stringCompare = (root -> getEntry() -> getTitle()).compare(name);

    if(stringCompare < 0) {
        return findHelper(root -> getRight(), name);
    } else if(stringCompare > 0){
        return findHelper(root -> getLeft(), name);
    }
    
    return root -> getEntry();
}

// Calls the helper function.
bool TreeDB::remove(string name) {
    return removeHelper(NULL, root, name);
}

// Recursively traverses the tree
bool TreeDB::removeHelper(TreeNode* prev, TreeNode* root, string name) {
    int stringCompare;
    if(root == NULL) return false;
    stringCompare = (root -> getEntry() -> getTitle()).compare(name);
    
    if(stringCompare < 0) {
        return removeHelper(root, root -> getRight(), name);
    } else if(stringCompare > 0) {
        return removeHelper(root, root -> getLeft(), name);
    } else if(stringCompare == 0) {
        // Checks if the node is a leaf node. If it is, then it sets the previous
        // node to NULL (depending on the direction). If previous is NULL, it also
        // sets the "root" pointer of the TreeDB object to NULL.
        if(root -> getRight() == NULL && root -> getLeft() == NULL) {
            // Leaf node
            if(prev != NULL) {
                if(prev -> getRight() != NULL && prev -> getRight() == root) prev -> setRight(NULL);
                else prev -> setLeft(NULL);
            } else if(prev == NULL && root -> getLeft() == NULL && root -> getRight() == NULL) {
                this -> root = NULL;
            }
            
            delete root;
            root = NULL;
            return true;
            
        // If there are two subtrees attached to the node, it deletes the node and replaces
        // it based on the instructions in the lab handout. If prev is NULL, then it replaces
        // the root node with "replaceNode"
        } else if(root -> getRight() != NULL && root -> getLeft() != NULL) {
            TreeNode* replaceNode = root -> getLeft();
            
            while(replaceNode -> getRight() != NULL) {
                replaceNode = replaceNode -> getRight();
            }
            
            if(prev == NULL) {
                replaceNode -> setRight(root -> getRight());
                this -> root = replaceNode;
            } else {
                root -> getLeft() -> setRight(replaceNode -> getLeft());
                if(prev -> getRight() != NULL && prev -> getRight() == root) {
                    prev -> setRight(replaceNode);
                } else {
                    prev -> setLeft(replaceNode);
                }
                if(root -> getLeft() != replaceNode) replaceNode -> setLeft(root -> getLeft());
                replaceNode -> setRight(root -> getRight());
            }
            
            delete root;
            root = NULL;
            return true;
            
        // If there is only one subtree, it attaches the subtree to the tree before deleting
        // the specified node. If prev is NULL, then the "attach" node becomes the root.
        } else if(root -> getRight() != NULL || root -> getLeft() != NULL) {
            TreeNode* attach;
            if(root -> getRight() != NULL) attach = root -> getRight();
            else attach = root -> getLeft();
            if(prev != NULL) {
                if(prev -> getRight() != NULL && prev -> getRight() == root) prev -> setRight(attach);
                else prev -> setLeft(attach);
            } else {
                this -> root = attach;
            }
            
            delete root;
            root = NULL;
            return true;
        }
    }
    return false;
}

// Calls the helper function.
void TreeDB::clear() {
    clearHelper(root);
}

// Traverses the tree and deletes the nodes that are the
// farthest from the root first.
void TreeDB::clearHelper(TreeNode* root) {
    if(root == NULL) return;
    clearHelper(root -> getRight());
    clearHelper(root -> getLeft());
    delete root;
}


// Calls the helper function and prints that value.
void TreeDB::countInventory() const {
    cout << countInventoryHelper(root) << endl;
}

// Traverses through the tree. Utilizes the "count" int variable
// to keep track of the inventory.
int TreeDB::countInventoryHelper(TreeNode* root) const {
    int count = 0;
    if(root == NULL) return 0;
    count += root ->getEntry() -> getInventory();
    if(root -> getRight() != NULL) {
        count += countInventoryHelper(root -> getRight());
    }
    if(root -> getLeft() != NULL) {
        count += countInventoryHelper(root -> getLeft());
    }
    return count;
}

// Calls the helper function.
ostream& operator<< (ostream& out, const TreeDB& rhs) {
    rhs.printAllHelper(rhs.root, out);
    return out;
}

// Prints all the nodes starting from the smallest one to the largest
// Utilizes the LNR traversal method to print.
void TreeDB::printAllHelper(TreeNode* root, ostream& out)  const {
    if(root != NULL) {
        printAllHelper(root -> getLeft(), out);
        out << *(root -> getEntry());
        printAllHelper(root -> getRight(), out);
    }
}

