#include <iostream>
#include "BBTree.h"

int main(int argc, char **argv) {
    if (argc < 1) {
        std::cout << "[ERROR] alpha must be specified\n";
    }
    double alpha = atof(argv[0]);

    BBTree *tree = new BBTree(alpha);
    tree->insert(2);
    tree->insert(5);
    tree->insert(4);
    tree->insert(3);
    tree->insert(1);
    tree->print();

    std::cout << tree->search(10) << "\n";
    std::cout << tree->search(2) << "\n";
    return 0;
}