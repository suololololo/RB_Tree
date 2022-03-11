#include "RedBlackTree.cpp"
#include <iostream>

int main()
{
    RedBlackTree<int> *tree = new RedBlackTree<int>();
    tree->insert(5);
    tree->insert(7);
    tree->insert(9);
    tree->insert(3);
    TreeNode<int> *node = tree->find(7);
    std::cout << node->isRed << std::endl;
    tree->DeleteValue(5);
    node = tree->find(3);
    std::cout << node->isRed << std::endl;
    return 0;
}