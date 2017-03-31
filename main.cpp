#include <iostream>
#include "BBTree.h"

int main(int argc, char **argv) {
    if (argc < 1) {
        std::cout << "[ERROR] alpha must be specified\n";
    }
    double alpha = atof(argv[1]);

    BBTree *tree = new BBTree(alpha);
    tree->insert(1);
    tree->insert(2);
    tree->insert(3);
    tree->insert(4);
    tree->insert(5);
    tree->insert(6);
    tree->insert(7);
    tree->insert(8);
    tree->insert(9);
    tree->insert(10);
    tree->print();

    return 0;
}