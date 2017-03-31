#include <iostream>
#include "BBTree.h"

// BBTree
BBTree::~BBTree() {
    delete root;
}

bool BBTree::search(const int key) const {
    return !isEmpty() && root->search(key);
}

void BBTree::insert(const int key) {
    if (isEmpty()) {
        root = new Node(key);
    } else {
        root = root->insert(key, alpha);
    }
}

void BBTree::remove(const int key) {
    if (!isEmpty()) {
        root->remove(key, alpha);
    }
}

void BBTree::print() {
    if (!isEmpty()) {
        root->print(0, false);
    }
}

bool BBTree::isEmpty() const {
    return root == nullptr;
}

// Node
BBTree::Node::~Node() {
    delete left;
    delete right;
}

bool BBTree::Node::search(const int key) const {
    return this->key == key
           || (key < this->key
               ? left != nullptr && left->search(key)
               : right != nullptr && right->search(key));
}

BBTree::Node *BBTree::Node::insert(const int key, const double alpha) {
    Node *new_root = this;
    if (key < this->key) {
        left = left == nullptr
               ? new Node(key)
               : left->insert(key, alpha);
    } else if (this->key < key) {
        right = right == nullptr
                ? new Node(key)
                : right->insert(key, alpha);
    }
    if (key != this->key) {
        recalculate_weight_balance();
        if (balance < alpha) {
            // right partial tree heavier than left one
            double d = (1 - 2 * alpha) / (1 - alpha);
            if (balance <= d) {
                // left rotation
                new_root = rotate_left();
//            } else {
//                // right-left rotation
//                left = left->rotate_left();
//                new_root = rotate_right();
            }
        } else if (balance > 1 - alpha) {
            // left partial tree heavier than right one
            double d = alpha / (1 - alpha);
            if (balance > d) {
                // right rotation
                new_root = rotate_right();
//            } else {
//                // left-right rotation
//                right = right->rotate_right();
//                new_root = rotate_left();
            }
        }
    }
    return new_root;
}

BBTree::Node *BBTree::Node::remove(const int key, const double alpha) {
    return this;
}

void BBTree::Node::recalculate_weight_balance() {
    int weight_left = left == nullptr
                      ? 1
                      : left->weight;
    weight = weight_left;
    weight += right == nullptr
              ? 1
              : right->weight;
    balance = (double) weight_left / weight;
}

BBTree::Node *BBTree::Node::rotate_left() {
    Node *new_root = right;
    right = right->left;
    recalculate_weight_balance();
    new_root->left = this;
    new_root->recalculate_weight_balance();
    return new_root;
}

BBTree::Node *BBTree::Node::rotate_right() {
    Node *new_root = left;
    recalculate_weight_balance();
    left = left->right;
    new_root->right = this;
    new_root->recalculate_weight_balance();
    return new_root;
}

void BBTree::Node::print(int depth, bool left_child) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    std::cout << "+-" << key << "\n";
    if (left == nullptr) {
        for (int i = 0; i < depth + 1; i++) {
            std::cout << "  ";
        }
        std::cout << "+-\n";
    } else {
        left->print(depth + 1, true);
    }
    if (right == nullptr) {
        for (int i = 0; i < depth + 1; i++) {
            std::cout << "  ";
        }
        std::cout << "+-\n";
    } else {
        right->print(depth + 1, false);
    }
}