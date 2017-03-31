#ifndef BBTREE_BBTREE_H
#define BBTREE_BBTREE_H

class BBTree {

private:

    struct Node {
        const int key;
        Node *left = nullptr;
        Node *right = nullptr;
        int weight = 2; // Anzahl Blätter
        Node(const int k) : key(k) {}
        Node(const int k, Node *l, Node *r) : key(k), left(l), right(r) {}
        bool search(const int) const;
        Node *insert(const int, const double);
        Node *remove(const int, const double);
        void print(int, bool);

        virtual ~Node();
    };

    const double alpha;
    Node *root;

    bool isEmpty() const;

public:

    BBTree(const double a) : alpha(a) {}

    bool search(const int) const;
    void insert(const int);
    void remove(const int);
    void print();

    virtual ~BBTree();
};

#endif //BBTREE_BBTREE_H
