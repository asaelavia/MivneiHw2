//
// Created by raz_a on 27/11/2019.
//

#ifndef DATACENTERMANAGER_AVLTREE_H
#define DATACENTERMANAGER_AVLTREE_H

template <typename T>
class AVLNode {
public:
    double key;
    int height;
    AVLNode<T>* parent;
    AVLNode<T>* left;
    AVLNode<T>* right;
    T data;
    ~AVLNode() = default;
};

template <typename T>
class AVLTree {
    AVLNode<T>* root;
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {
        if(this->root) postOrderDelete(this->root);
    }
    void postOrderDelete(AVLNode<T>* node);
    AVLNode<T>* newNode(double key, const T& data = T(), AVLNode<T>* parent = nullptr);
    AVLNode<T>* find(AVLNode<T>* node, double key);
    AVLNode<T>* findParent(AVLNode<T>* node, double key);
    void insertNode(double key, const T& data = T());
    void deleteNode(double key);
    void rotateLL(AVLNode<T>* node);
    void rotateLR(AVLNode<T>* node);
    void rotateRL(AVLNode<T>* node);
    void rotateRR(AVLNode<T>* node);
    int balanceFactor(AVLNode<T>* node);
    void updateHeight(AVLNode<T>* node);
    void rotateNodesInPath(AVLNode<T>* node, AVLNode<T>* node2, bool is_insert);
    AVLNode<T>* getRoot();

};

int maxFunc(int a, int b) {
    return (a > b) ? a : b;
}

template <typename T>
AVLNode<T>* AVLTree<T>::newNode(double key, const T& data, AVLNode<T>* parent) {
    auto* node = new AVLNode<T>();
    node->key = key;
    node->height = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->data = data;
    return node;
}

template <typename T>
void AVLTree<T>::insertNode(double key, const T& data) {
    if(this->root == nullptr){
        this->root = newNode(key, data);
        return;
    }

    AVLNode<T>* node = find(this->root, key);

    if(node != nullptr){
        return;
    }

    node = findParent(this->root, key);
    AVLNode<T>* node2;

    if(node->key > key){
        node->left = newNode(key, data ,node);
        node2 = node->left;
    }
    else{
        node->right = newNode(key, data, node);
        node2 = node->right;
    }

    rotateNodesInPath(node, node2, true);

}

template<typename T>
AVLNode<T>* AVLTree<T>::find(AVLNode<T>* node, double key) {
    if(node == nullptr){
        return nullptr;
    }
    double curr_key = node->key;
    if(curr_key == key){
        return node;
    }
    if(curr_key > key){
        return find(node->left, key);
    }
    else{
        return find(node->right, key);
    }
}

template<typename T>
AVLNode<T>* AVLTree<T>::findParent(AVLNode<T> *node, double key) {
    if(node == nullptr){
        return nullptr;
    }
    double curr_key = node->key;
    if(curr_key == key){
        return nullptr;
    }
    else if(curr_key > key){
        if(node->left != nullptr){
            if(node->left->key != key){
                return findParent(node->left, key);
            }
        }
    }
    else{
        if(node->right != nullptr){
            if(node->right->key != key){
                return findParent(node->right, key);
            }
        }
    }
    return node;
}

template<typename T>
void AVLTree<T>::rotateLL(AVLNode<T>* node) {
    AVLNode<T>* son = node->left;
    node->left = son->right;
    if(son->right != nullptr){
        son->right->parent = node;
    }
    son->right = node;
    son->parent = node->parent;
    node->parent = son;
    if(son->parent != nullptr){
        if(son->parent->left == node){
            son->parent->left = son;
        }
        if(son->parent->right == node){
            son->parent->right = son;
        }
    }
    if(this->root == node){
        this->root = son;
    }
    updateHeight(node);
    updateHeight(son);

}

template<typename T>
void AVLTree<T>::rotateLR(AVLNode<T>* node) {
    AVLNode<T>* son = node->left;
    AVLNode<T>* son2 = son->right;
    node->left = son2->right;
    if(son2->right != nullptr){
        son2->right->parent = node;
    }
    son->right = son2->left;
    if(son2->left != nullptr){
        son2->left->parent = son;
    }
    son2->left = son;
    son->parent = son2;
    son2->right = node;
    son2->parent = node->parent;
    node->parent = son2;
    if(son2->parent != nullptr){
        if(son2->parent->left == node){
            son2->parent->left = son2;
        }
        if(son2->parent->right == node){
            son2->parent->right = son2;
        }
    }
    if(this->root == node){
        this->root = son2;
    }
    updateHeight(node);
    updateHeight(son);
    updateHeight(son2);

}

template<typename T>
void AVLTree<T>::rotateRL(AVLNode<T>* node) {
    AVLNode<T>* son = node->right;
    AVLNode<T>* son2 = son->left;
    node->right = son2->left;
    if(son2->left != nullptr){
        son2->left->parent = node;
    }
    son->left = son2->right;
    if(son2->right != nullptr){
        son2->right->parent = son;
    }
    son2->right = son;
    son->parent = son2;
    son2->left = node;
    son2->parent = node->parent;
    node->parent = son2;
    if(son2->parent != nullptr){
        if(son2->parent->left == node){
            son2->parent->left = son2;
        }
        if(son2->parent->right == node){
            son2->parent->right = son2;
        }
    }
    if(this->root == node){
        this->root = son2;
    }
    updateHeight(node);
    updateHeight(son);
    updateHeight(son2);

}

template<typename T>
void AVLTree<T>::rotateRR(AVLNode<T>* node) {
    AVLNode<T>* son = node->right;
    node->right = son->left;
    if(son->left != nullptr){
        son->left->parent = node;
    }
    son->left = node;
    son->parent = node->parent;
    node->parent = son;
    if(son->parent != nullptr){
        if(son->parent->left == node){
            son->parent->left = son;
        }
        if(son->parent->right == node){
            son->parent->right = son;
        }
    }
    if(this->root == node){
        this->root = son;
    }
    updateHeight(node);
    updateHeight(son);

}

template<typename T>
int AVLTree<T>::balanceFactor(AVLNode<T> *node) {
    int left = -1, right = -1;
    if(node->left != nullptr){
        left = node->left->height;
    }
    if(node->right != nullptr){
        right = node->right->height;
    }
    return (left-right);
}

template<typename T>
void AVLTree<T>::updateHeight(AVLNode<T>* node) {
    int left = -1, right = -1;
    if(node != nullptr){
        if(node->left != nullptr){
            left = node->left->height;
        }
        if(node->right != nullptr){
            right = node->right->height;
        }
        node->height = 1 + maxFunc(left, right);
    }

}


template<typename T>
void AVLTree<T>::deleteNode(double key) {
    AVLNode<T>* node = find(this->root, key);

    if(node == nullptr){
        return;
    }

    AVLNode<T>* temp;
    AVLNode<T>* temp2;
    bool node_is_left_son = false;

    if(node->parent){
        if(node->parent->left == node){
            node_is_left_son = true;
        }

        if(!node->right && !node->left){
            if(node_is_left_son){
                node->parent->left = nullptr;
                temp = node->parent;
                if(temp->right){
                    temp2 = temp->right;
                    delete node;
                    rotateNodesInPath(temp, temp2, false);
                }
                else{
                    temp2 = temp->parent;
                    delete node;
                    rotateNodesInPath(temp2, temp, false);
                }
                return;

            }
            else{
                node->parent->right = nullptr;
                temp = node->parent;
                if(temp->left){
                    temp2 = temp->left;
                    delete node;
                    rotateNodesInPath(temp, temp2, false);
                }
                else{
                    temp2 = temp->parent;
                    delete node;
                    rotateNodesInPath(temp2, temp, false);
                }
                return;
            }

        }

        else if((!node->left && node->right) || (node->left && !node->right)) {
            if(node_is_left_son){
                if(node->left){
                    node->parent->left = node->left;
                    node->left->parent = node->parent;
                }
                else{
                    node->parent->left = node->right;
                    node->right->parent = node->parent;
                }
            }
            else{
                if(node->left){
                    node->parent->right = node->left;
                    node->left->parent = node->parent;
                }
                else{
                    node->parent->right = node->right;
                    node->right->parent = node->parent;
                }
            }

            temp2 = node->parent;
            temp = temp2->parent;
            delete node;
            rotateNodesInPath(temp, temp2, false);
            return;
        }

    }

    else if(node->left && !node->right){
        this->root = node->left;
        delete node;
        return;
    }

    else if(!node->left && node->right){
        this->root = node->right;
        delete node;
        return;
    }

    else if(!node->left && !node->right){
        this->root = nullptr;
        delete node;
        return;
    }

    AVLNode<T>* next_node = node->right; //Next node as inorder

    while(next_node->left){
        next_node = next_node->left;
    }

    node->key = next_node->key;
    node->data = next_node->data;

    if(next_node->parent->left == next_node){
        node_is_left_son = true;
    }

    if(!next_node->right){
        if(node_is_left_son){
            next_node->parent->left = nullptr;
            temp = next_node->parent;
            if(temp->right){
                temp2 = temp->right;
                delete next_node;
                rotateNodesInPath(temp, temp2, false);
            }
            else{
                temp2 = temp->parent;
                delete next_node;
                rotateNodesInPath(temp2, temp, false);
            }
            return;

        }
        else{
            next_node->parent->right = nullptr;
            temp = next_node->parent;
            if(temp->left){
                temp2 = temp->left;
                delete next_node;
                rotateNodesInPath(temp, temp2, false);
            }
            else{
                temp2 = temp->parent;
                delete next_node;
                rotateNodesInPath(temp2, temp, false);
            }
            return;
        }

    }

    else {
        next_node->parent->left = next_node->right;
        next_node->right->parent = next_node->parent;
    }

    temp = next_node->parent;
    if(temp->right){
        temp2 = temp->right;
        delete next_node;
        temp->left = nullptr;
        rotateNodesInPath(temp, temp2, false);
    }
    else{
        temp2 = temp->parent;
        delete next_node;
        temp->left = nullptr;
        rotateNodesInPath(temp2, temp, false);
    }

}

template<typename T>
void AVLTree<T>::postOrderDelete(AVLNode<T> *node) {
    if(node->left){
        postOrderDelete(node->left);
    }
    if(node->right){
        postOrderDelete(node->right);
    }
    delete node;
}

template<typename T>
AVLNode<T> *AVLTree<T>::getRoot() {
    return this->root;
}

template<typename T>
void AVLTree<T>::rotateNodesInPath(AVLNode<T> *node, AVLNode<T> *node2, bool is_insert) {
    int bf, bf2, bf3;
    while(node != nullptr){
        updateHeight(node);
        bf = balanceFactor(node);
        bf2 = balanceFactor(node2);
        if(node2 == node->left){
            if(bf == 2 && bf2 >= 0){
                rotateLL(node);
                if(is_insert) {return;}
            }
            else if(bf == 2 && bf2 == -1){
                rotateLR(node);
                if(is_insert) {return;}
            }
            if(node->right && !is_insert){
                bf3 = balanceFactor(node->right);
                if(bf == -2 && bf3 <= 0){
                    rotateRR(node);
                }
                else if(bf == -2 && bf3 == 1){
                    rotateRL(node);
                }
            }
        }
        else if(node2 == node->right){
            if(bf == -2 && bf2 <= 0){
                rotateRR(node);
                if(is_insert) {return;}
            }
            else if(bf == -2 && bf2 == 1){
                rotateRL(node);
                if(is_insert) {return;}
            }
            if(node->left && !is_insert){
                bf3 = balanceFactor(node->left);
                if(bf == 2 && bf3 >= 0){
                    rotateLL(node);
                }
                else if(bf == 2 && bf3 == -1){
                    rotateLR(node);
                }
            }
        }
        node2 = node;
        node = node->parent;
    }
}

#endif //DATACENTERMANAGER_AVLTREE_H
