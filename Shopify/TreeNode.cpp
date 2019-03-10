#include "TreeNode.h"
#include <stdio.h>

//  This constructor creates a TreeNode object that points
//  to the entryPtr passed to the function.
//  left and right point to NULL
TreeNode::TreeNode(DBentry* _entryPtr) {
    entryPtr = _entryPtr;
    left = NULL;
    right = NULL;
}

//  The destructor deletes the entryPtr pointer since it is
//  created using the "new" operator. Afterwards, entryPtr,
//  left, and right pointers point to NULL.
TreeNode::~TreeNode() {
    delete entryPtr;
    entryPtr = NULL;
    left = NULL;
    right = NULL;
}

// Sets the pointer that points to the "left" node
void TreeNode::setLeft(TreeNode* newLeft) {
    left = newLeft;
}

// Sets the pointer that points to the "right" node
void TreeNode::setRight(TreeNode* newRight) {
    right = newRight;
}

// Returns the pointer that points to the "left" node
TreeNode* TreeNode::getLeft() const {
    return left;
}

// Returns the pointer that points to the "right" node
TreeNode* TreeNode::getRight() const {
    return right;
}

// Returns the entry that the node points to
DBentry* TreeNode::getEntry() const {
    return entryPtr;
}
