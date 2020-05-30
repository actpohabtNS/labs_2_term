#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

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

    virtual void directed(const bool& directed) = 0;
    virtual void weighted(const bool& weighted) = 0;

    virtual void dfs(const int& snode, bool* visited, bool byWeight = false) const = 0;

    virtual void bfs(const int& snode, bool* visited, bool byWeight = false) const = 0;

    virtual bool connected() const = 0;
    virtual bool cyclic() const = 0;

    [[nodiscard]] virtual std::vector<std::vector<int>> components() const = 0;
    [[nodiscard]] virtual std::vector<int> topologicalSort() const = 0;

    [[nodiscard]] virtual int dijkstra(int fnode, int tnode) const = 0;
    [[nodiscard]] virtual std::vector<int> dijkstra(int snode) const = 0;
    [[nodiscard]] virtual std::vector<std::vector<int>> floyd() const = 0;

    virtual int nodes() const = 0;
    virtual int edges() const = 0;
    virtual bool empty() const = 0;
    virtual bool directed() const = 0;
    virtual bool weighted() const = 0;
};

#endif // GRAPH_H
