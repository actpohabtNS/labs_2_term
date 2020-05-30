#ifndef SPANNINGTREE_H
#define SPANNINGTREE_H

#include <vector>

class SpanningTree
{    
public:

    class Node
    {
        friend SpanningTree;

    private:
        int _index;
        int _weight;
        Node* _parent;
        std::vector<Node*> _children;

    public:
        explicit Node(int index, int weight = 0);
        virtual ~Node();

        [[nodiscard]] int index() const;
        [[nodiscard]] int weight() const;
        [[nodiscard]] std::vector<Node*> children() const;
    };

    explicit SpanningTree(Node* root = nullptr);
    virtual ~SpanningTree();

    void link(Node* from, Node* to, const int& weight);

    [[nodiscard]] const Node* root() const;
    [[nodiscard]] int weight() const;


private:
    Node* _root;

    int _weight(Node* node) const;

};

#endif // SPANNINGTREE_H
