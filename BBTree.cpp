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
    root = isEmpty()
           ? new Node(key)
           : root->insert(key, alpha);
}

void BBTree::remove(const int key) {
    if (!isEmpty()) {
        root = root->remove(key, alpha);
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
    if (key < this->key) {
        left = left == nullptr
               ? new Node(key)
               : left->insert(key, alpha);
    } else if (this->key < key) {
        right = right == nullptr
                ? new Node(key)
                : right->insert(key, alpha);
    }
    return key == this->key
           ? this
           : rebalance(alpha);
}

BBTree::Node *BBTree::Node::remove(const int key, const double alpha) {
    Node *new_root = this;
    if (this->key == key) {
        if (left != nullptr && right != nullptr) {
            int greatest_left_key = left->key;
            for (Node *greatest_left = left;
                 greatest_left->right != nullptr;
                 greatest_left = greatest_left->right, greatest_left_key = greatest_left->key);
            new_root = new Node(greatest_left_key, left, right);
            new_root->left = new_root->left->remove(greatest_left_key, alpha);
        } else if (left != nullptr && right == nullptr) {
            new_root = left;
        } else if (left == nullptr && right != nullptr) {
            new_root = right;
        } else {
            new_root = nullptr;
        }
    } else if (key < this->key && left != nullptr) {
        Node *new_left = left->remove(key, alpha);
        if (new_left == nullptr) {
            delete left;
        }
        left = new_left;
    } else if (this->key < key && right != nullptr) {
        Node *new_right = right->remove(key, alpha);
        if (new_right == nullptr) {
            delete right;
        }
        right = new_right;
    }
    return new_root == nullptr
           ? new_root
           : new_root->rebalance(alpha);
}

BBTree::Node *BBTree::Node::rebalance(const double alpha) {
    Node *new_root = this;
    recalculate_weight_balance();
    if (balance < alpha) {
        // right partial tree heavier than left one
        double d = (1 - 2 * alpha) / (1 - alpha);
        if (balance <= d) {
            // left rotation
            new_root = this->rotate_left();
        } else {
            // right-left rotation
            left = left->rotate_left();
            new_root = this->rotate_right();
        }
    } else if (balance > 1 - alpha) {
        // left partial tree heavier than right one
        double d = alpha / (1 - alpha);
        if (balance > d) {
            // right rotation
            new_root = this->rotate_right();
        } else {
            // left-right rotation
            right = right->rotate_right();
            new_root = this->rotate_left();
        }
    }
    return new_root;
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