#ifndef GRAPH_H
#define GRAPH_H

class Graph {
public:
    Graph() = default;
    virtual ~Graph() = default;

    virtual void addNode() = 0;
    virtual void addEdge(const int& fnode, const int& tnode) = 0;
    virtual void addEdge(const int& fnode, const int& tnode, const int& weight) = 0;
    virtual void eraseEdge(const int& fnode, const int& tnode) = 0;
    virtual void eraseEdges() = 0;
    virtual void print() const = 0;

    virtual int nodes() const = 0;
    virtual int edges() const = 0;
    virtual bool empty() const = 0;

};

#endif // GRAPH_H
