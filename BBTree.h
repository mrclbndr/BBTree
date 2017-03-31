#ifndef BBTREE_BBTREE_H
#define BBTREE_BBTREE_H

/**
 * Interface for weight-balanced trees.
 */
class BBTree {

private:

    /**
     * Represents a node of a {@link BBTree}.
     */
    struct Node {
        const int key;
        Node *left = nullptr;
        Node *right = nullptr;
        int weight = 2; // Anzahl Blätter
        double balance = (double) 1 / weight;

        /**
         * Create a new instance of a {@link Node}.
         *
         * @param k the key
         */
        Node(const int k) : key(k) {}

        /**
         * Create a new instance of a {@link Node}.
         *
         * @param k the key
         * @param l the left child node or {@code nullptr} in case of a leave
         * @param r the right child node or {@code nullptr} in case of a leave
         */
        Node(const int k, Node *l, Node *r) : key(k), left(l), right(r) {}

        /**
         * Search for a key in the partial tree whose root is this {@link Node}.
         *
         * @param key the key to be searched for
         * @return {@code true} if the key does exist, {@code false} otherwise
         */
        bool search(const int) const;

        /**
         * Insert a key into the partial tree whose root is this {@link Node}.
         * <strong>Note:</strong> This method modifies the tree structure though the caller must store the new root of this partial tree.
         *
         * @param key the key to be inserted
         * @param alpha the alpha of the {@link BBTree}
         * @return the new root {@link Node} of this partial tree, must be stored by caller, never {@code nullptr}
         *
         */
        Node *insert(const int, const double);

        /**
         * Remove a key from the partial tree whose root is this {@link Node}.
         * <strong>Note:</strong> This method modifies the tree structure though the caller must store the new root of this partial tree.
         *
         * @param key the key to be removed
         * @param alpha the alpha of the {@link BBTree}
         * @return the new root {@link Node} of this partial tree, must be stored by caller or {@code nullptr} if this {@link Node} is about to be removed and the caller must {@code delete} this {@link Node}
         */
        Node *remove(const int, const double);

        /**
         * Rebalance the partial tree whose root is this {@link Node}.
         * <strong>Note:</strong> This method modifies the tree structure though the caller must store the new root of this partial tree.
         *
         * @param alpha the alpha of the {@link BBTree}
         * @return the new root {@link Node} of this partial tree, must be stored by caller, never {@code nullptr}
         */
        Node *rebalance(const double);

        /**
         * Recalculate the weight and weight balance of this {@link Node}.
         */
        void recalculate_weight_balance();

        /**
         * Perform a simple rotation anti-clockwise around this {@link Node}.
         * <strong>Note:</strong> This method modifies the tree structure though the caller must store the new root of this partial tree.
         *
         * @return the new root {@link Node} of this partial tree, must be stored by caller, never {@code nullptr}
         */
        Node *rotate_left();

        /**
         * Perform a simple rotation clockwise around this {@link Node}.
         * <strong>Note:</strong> This method modifies the tree structure though the caller must store the new root of this partial tree.
         *
         * @return the new root {@link Node} of this partial tree, must be stored by caller, never {@code nullptr}
         */
        Node *rotate_right();

        /**
         * Print this {@link Node} and its children recursively to standard output.
         *
         * @param depth the depth of this {@link Node} in the {@link BBTree}, used to indent the output
         */
        void print(int);

        /**
         * Destruct this {@link Node}.
         */
        virtual ~Node();
    };

    const double alpha;
    Node *root;

    /**
     * Check whether this {@link BBTree} contains no {@link Node}s.
     *
     * @return {@code true} if this {@link BBTree} contains no {@link Node}s, {@code false} otherwise
     */
    bool isEmpty() const;

public:
    /**
     * Create a new instance of a {@link BBTree}.
     *
     * @param a alpha
     */
    BBTree(const double a) : alpha(a) {}

    /**
     * Search this {@link BBTree} for presence of a certain key.
     *
     * @param key the key to be searched for
     * @return {@code true} if the key does exist, {@code false} otherwise
     */
    bool search(const int) const;

    /**
     * Insert a certain key into this {@link BBTree}.
     * If the key does already exist the tree remains unaffected.
     *
     * @param key the key to be inserted
     */
    void insert(const int);

    /**
     * Remove a certain key from this {@link BBTree}.
     * If the key does not exist the tree remains unaffected.
     *
     * @param key the key to be removed
     */
    void remove(const int);

    /**
     * Print the internal structure of this {@link BBTree} to standard output.
     * <strong>Note:</strong> The format of the output is not specified and might change over time!
     */
    void print();

    /**
     * Destruct this {@link BBTree}.
     */
    virtual ~BBTree();
};

#endif //BBTREE_BBTREE_H
