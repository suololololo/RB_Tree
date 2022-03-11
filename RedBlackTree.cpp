#include "RedBlackTree.h"
#include <iostream>
template <typename T>
RedBlackTree<T>::RedBlackTree() : root(nullptr)
{
}

template <typename T>
RedBlackTree<T>::RedBlackTree(T val) : root(nullptr)
{
    root = new TreeNode<T>(val, false);
}

template <typename T>
void RedBlackTree<T>::insert(T val)
{
    if (root == nullptr)
    {
        root = new TreeNode<T>(val, false);
        return;
    }
    TreeNode<T> *curr = root;
    while (curr != nullptr)
    {
        if (val > curr->val)
        {
            if (curr->right == nullptr)
            {
                curr->right = new TreeNode<T>(val, true);
                curr->right->father = curr;
                if (curr->isRed)
                {
                    fixTree(curr->right);
                }
                break;
            }
            else
            {
                curr = curr->right;
            }
        }
        else
        {
            if (curr->left == nullptr)
            {
                curr->left = new TreeNode<T>(val, true);
                curr->left->father = curr;
                if (curr->isRed)
                {
                    fixTree(curr->left);
                }
                break;
            }
            else
            {
                curr = curr->left;
            }
        }
    }
}

template <typename T>
void RedBlackTree<T>::fixTree(TreeNode<T> *currNode)
{
    TreeNode<T> *tempCurrNode = currNode;
    TreeNode<T> *uncle;
    while (true)
    {
        if (tempCurrNode->father == nullptr)
        {
            break;
        }
        if (!tempCurrNode->father->isRed)
        {
            break;
        }
        TreeNode<T> *father = tempCurrNode->father;
        TreeNode<T> *grandfather = father->father;
        if (grandfather)
        {
            if (father == grandfather->left)
            {
                uncle = grandfather->right;
                // 如果存在叔叔节点
                if (uncle)
                {
                    // 父亲和叔叔都是红色
                    if (uncle->isRed)
                    {
                        uncle->isRed = false;
                        father->isRed = false;
                        grandfather->isRed = true;
                        // 递归向上调整颜色
                        tempCurrNode = grandfather;
                    }
                    //父亲为红 叔叔为黑 且当前节点为父亲的右孩子 左旋
                    else if (tempCurrNode == father->right)
                    {
                        tempCurrNode = father;
                        leftRoate(tempCurrNode);
                    }
                    // 父亲为红 叔叔为黑 且当前节点为父亲的左孩子
                    else
                    {
                        father->isRed = false;
                        grandfather->isRed = true;
                        rightRoate(grandfather);
                    }
                }
                //没有叔叔节点
                else
                {
                    if (tempCurrNode == father->right)
                    {
                        tempCurrNode = tempCurrNode->father;
                        leftRoate(tempCurrNode);
                    }
                    else
                    {
                        father->isRed = false;
                        grandfather->isRed = true;
                        rightRoate(grandfather);
                    }
                }
            }
            // father = grandfather->right
            else
            {
                uncle = grandfather->left;
                if (uncle)
                {
                    if (uncle->isRed)
                    {
                        uncle->isRed = false;
                        father->isRed = false;
                        grandfather->isRed = true;
                        tempCurrNode = grandfather;
                    }
                    else if (tempCurrNode == father->left)
                    {
                        tempCurrNode = tempCurrNode->father;
                        rightRoate(tempCurrNode);
                    }
                    else
                    {
                        father->isRed = false;
                        grandfather->isRed = true;
                        leftRoate(grandfather);
                    }
                }
                else
                {
                    if (tempCurrNode == father->left)
                    {
                        tempCurrNode = tempCurrNode->father;
                        rightRoate(tempCurrNode);
                    }
                    else
                    {
                        father->isRed = false;
                        grandfather->isRed = true;
                        leftRoate(grandfather);
                    }
                }
            }
        }
    }
    root->isRed = false;
}

template <typename T>
TreeNode<T> *RedBlackTree<T>::find(T val)
{
    TreeNode<T> *curr = root;
    while (curr)
    {
        if (curr->val > val)
        {
            curr = curr->left;
        }
        else if (curr->val < val)
        {
            curr = curr->right;
        }
        else
        {
            return curr;
        }
    }
    return nullptr;
}

template <typename T>
void RedBlackTree<T>::leftRoate(TreeNode<T> *currNode)
{
    TreeNode<T> *right = currNode->right;
    TreeNode<T> *father = currNode->father;
    currNode->right = right->left;
    right->left = currNode;
    if (father == nullptr)
    {
        root = right;
    }
    else if (currNode == father->left)
    {
        father->left = right;
    }
    else
    {
        father->right = right;
    }
    right->father = father;
    currNode->father = right;
}

template <typename T>
void RedBlackTree<T>::rightRoate(TreeNode<T> *currNode)
{
    TreeNode<T> *left = currNode->left;
    TreeNode<T> *father = currNode->father;
    currNode->left = left->right;
    left->right = currNode;
    if (father == nullptr)
    {
        root = left;
    }
    else if (currNode == father->left)
    {
        father->left = left;
    }
    else
    {
        father->right = left;
    }

    left->father = father;
    currNode->father = left;
}

template <typename T>
TreeNode<T> *RedBlackTree<T>::findPreNode(TreeNode<T> *currNode)
{
    TreeNode<T> *temp = currNode->right;
    while (temp->left != nullptr)
    {
        temp = temp->left;
    }

    return temp;
}

template <typename T>
void RedBlackTree<T>::DeleteValue(const T &v1)
{
    TreeNode<T> *p = NULL;
    TreeNode<T> *nextNode = NULL;
    p = find(v1);
    if (p == NULL)
    {
        std::cout << "删除的值不存在" << std::endl;
        return;
    }
    if (p->left && p->right)
    {
        TreeNode<T> *tempNode = p->right;
        while (tempNode)
        { //中序序列的后继节点
            nextNode = tempNode;
            tempNode = tempNode->left;
        }
        p->val = nextNode->val;
        p = nextNode;
    }
    if (p->left)
    {
        //直接用后继节点的值替换
        TreeNode<T> *temp = p->left;
        p->val = temp->val;
        p->left = NULL;
        delete temp;
    }
    else if (p->right)
    {
        //直接用后继节点的值替换
        TreeNode<T> *temp = p->right;
        p->val = temp->val;
        p->right = NULL;
        delete temp;
    }
    else
    {
        //左右子树都不存在，需要进入删除调整算法
        DeleteReblance(p);
        if (p == root)
        {
            root = NULL;
        }
        else if (p == p->father->left)
        { //父节点的指针域需要修改
            p->father->left = NULL;
        }
        else if (p == p->father->right)
        { //父节点的指针域需要修改
            p->father->right = NULL;
        }
        delete p;
    }
}

//删除节点后的调整
template <typename T>
void RedBlackTree<T>::DeleteReblance(TreeNode<T> *node)
{
    TreeNode<T> *parent = NULL;
    TreeNode<T> *other = NULL;
    while (!node->isRed && node->father)
    {
        parent = node->father;
        if (node == parent->left)
        {
            other = parent->right;
            if (other->isRed)
            { //情形1兄弟节点为红
                parent->isRed = true;
                other->isRed = false;
                leftRoate(parent);
                other = parent->right;
            }
            if ((other->left == NULL || !other->left->isRed) && (other->right == NULL || !other->left->isRed))
            { //情形2兄弟为黑，且兄弟的两个孩子也为黑
                other->isRed = true;
                node = parent;
                continue;
            }
            if (other->right == NULL || !other->right->isRed)
            {                               //情形3兄弟节点的右孩子为黑，左为红
                other->left->isRed = false; //此时左孩子一定存在且颜色为红，如果不满足就不会进入这个条件
                other->isRed = true;
                rightRoate(other);
                other = parent->right;
            }
            //情形4兄弟节点的右孩子为红
            other->right->isRed = false;
            other->isRed = parent->isRed;
            parent->isRed = false;
            leftRoate(parent);
            break;
        }
        else
        {
            other = parent->left;
            if (other->isRed)
            { //情形1兄弟节点为红
                parent->isRed = true;
                other->isRed = false;
                rightRoate(parent);
                other = parent->left;
            }
            if ((other->left == NULL || !other->left->isRed) && (other->right == NULL || !other->left->isRed))
            { //情形2兄弟为黑，且兄弟的两个孩子也为黑
                other->isRed = true;
                node = parent;
                continue;
            }
            if (other->left == NULL || !other->left->isRed)
            {                                //情形3兄弟节点的右孩子为黑，左为红
                other->right->isRed = false; //此时左孩子一定存在且颜色为红，如果不满足就不会进入这个条件
                other->isRed = true;
                leftRoate(other);
                other = parent->left;
            }
            //情形4兄弟节点的右孩子为红
            other->left->isRed = false;
            other->isRed = parent->isRed;
            parent->isRed = false;
            rightRoate(parent);
            break;
        }
    }
    node->isRed = false;
}