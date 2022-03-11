#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H
#include "TreeNode.h"


template <typename T>
class RedBlackTree
{
public:
    RedBlackTree();
    RedBlackTree(T val);
    ~RedBlackTree(){}
    void insert(T val);
    TreeNode<T> *find(T val);
    void DeleteValue(const T& val);
private:
    void leftRoate(TreeNode<T> *currNode);
    void rightRoate(TreeNode<T> *currNode);
    void fixTree(TreeNode<T> *currNode);
    TreeNode<T> *findPreNode(TreeNode<T> *currNode);
    void DeleteReblance(TreeNode<T> *currNode);
private:
    TreeNode<T> *root;
};
// #include "RedBlackTree.cpp"
#endif