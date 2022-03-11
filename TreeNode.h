#ifndef TREE_NODE_H
#define TREE_NODE_H

template <typename T>
class TreeNode
{
public:
    TreeNode(int _val) : val(_val), left(nullptr), right(nullptr), isRed(true),father(nullptr)
    {
    }
    TreeNode(int _val, TreeNode *_left, TreeNode *_right) : val(_val), left(_left), right(_right), isRed(true),father(nullptr)
    {
    }
    TreeNode(int _val, bool _isRed) : val(_val), isRed(_isRed),left(nullptr),right(nullptr),father(nullptr)
    {
    }
    ~TreeNode()
    {
    }

public:
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T> *father;
    T val;
    bool isRed;
};

#endif