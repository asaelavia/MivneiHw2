//
// Created by raz_a on 08/12/2019.
//

#include "AVLTree.h"
#include <iostream>

using namespace std;

template<typename T>
void printBT(const std::string& prefix, AVLNode<T>* node, bool isLeft) {
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "'--" );

        // print the value of the node
        std::cout << "(" << node->key << "," << node->data << ")" << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "|   " : "    "), node->right, true);
        printBT( prefix + (isLeft ? "|   " : "    "), node->left, false);
    }
}

template<typename T>
void printBT(AVLTree<T>* tree) {
    printBT("", tree->getRoot(), false);
}

int main() {
    AVLTree<int> tree;
    tree.insertNode(5);
    tree.insertNode(2);
    tree.insertNode(8);
    tree.insertNode(1);
    tree.insertNode(4);
    tree.insertNode(6);
    tree.insertNode(10);
    tree.insertNode(3);
    tree.insertNode(7);
    tree.insertNode(9);
    tree.insertNode(12);
    tree.insertNode(11);
    printBT(&tree);

    tree.deleteNode(8);
    printBT(&tree);

    return 0;
}
