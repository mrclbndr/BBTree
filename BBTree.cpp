#include <iostream>
#include "BBTree.h"

// BBTree
BBTree::~BBTree() {
    delete root;
}

bool BBTree::search(const int key) const {
    return root == nullptr
           ? false
           : root->search(key);
}

void BBTree::insert(const int key) {
    if (root == nullptr) {
        root = new Node(key);
    } else {
        root->insert(key, alpha);
    }
}

void BBTree::remove(const int key) {
    if (root != nullptr) {
        root->remove(key, alpha);
    }
}

void BBTree::print() {
    if (root != nullptr) {
        root->print(0, false);
    }
}

// Node
BBTree::Node::~Node() {
    delete left;
    delete right;
}

bool BBTree::Node::search(const int key) const {
    return this->key == key
           || (key < this->key
               ? left->search(key)
               : right->search(key));
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
        int weight_left = left == nullptr
                          ? 1
                          : left->weight;
        weight = weight_left;
        weight += right == nullptr
                           ? 1
                           : right->weight;

        double root_balance = weight_left / weight;
        if (root_balance < alpha) {
            // right partial tree heavier than left one
            double d = (1 - 2 * alpha) / (1 - alpha); // S. 35f.
            if (root_balance <= d) {
                // left rotation

            } else {
                // right-left rotation

            }
        } else if (root_balance > 1 - alpha) {
            // left partial tree heavier than right one
            double d = alpha / (1-alpha); // S. 35f.
            if (root_balance > d) {
                // right rotation

            } else {
                // left-right rotation

            }
        }
    }
    return new_root;
}

BBTree::Node *BBTree::Node::remove(const int key, const double alpha) {
    return this;
}

void BBTree::Node::print(int depth, bool left_child) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    std::cout << "+-" << key << "\t\t\tW(p)=" << weight << "\n";
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