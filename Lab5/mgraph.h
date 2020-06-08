#ifndef MGRAPH_H
#define MGRAPH_H

#include <cassert>
#include <QDebug>

#include "Graph.h"
#include "random.h"

class LGraph;

class MGraph : Graph
{
    friend LGraph;

private:
    mutable std::vector<std::vector<int*>> _matrix;
    int _nodes;
    int _edges;
    bool _directed;
    bool _weighed;

    void _addEdge(const int& fnode, const int& tnode, const int& weight, const bool& increment = true);
    void _removeOneWays();
    void _equateWeights();
    void _fill();
    int _firstNeighbour(int row, int max = -1) const;
    int _furthestNeighbour(int row, int max = -1) const;
    [[nodiscard]] std::vector<int> _neighboursWithWeight(int row, int weight) const;
    [[nodiscard]] std::vector<int> _descendingNeighbours(int row) const;

    void _dfs(const int& snode, bool* visited, bool byWeight, std::vector<int>* trav = nullptr) const;

    void _transpose() const;

    [[nodiscard]] std::vector<int> _dijkstra(int snode) const;

public:
    MGraph();
    explicit MGraph(int nodes, int edges = 0, bool directed = false, bool weighed = false);
    explicit MGraph(const LGraph& lGraph);
    ~MGraph();

    void build(const LGraph& lGraph);
    void addNode() override;
    void addEdge(const int& fnode, const int& tnode) override;
    void addEdge(const int& fnode, const int& tnode, const int& weight) override;
    void eraseEdge(const int& fnode, const int& tnode) override;
    void eraseEdges() override;

    QString QStr() const;
    void print() const override;

    void directed(const bool& directed) override;
    void weighed(const bool &weighed) override;

    void dfs(const int& snode, bool* visited, bool byWeight = false) const override;
    [[nodiscard]] std::vector<int> dfs(const int& snode) const;

    void bfs(const int& snode, bool* visited, bool byWeight = false) const override;

    bool connected() const override;
    bool cyclic() const override;

    [[nodiscard]] std::vector<std::vector<int>> components() const override;
    [[nodiscard]] std::vector<int> topologicalSort() const override;

    [[nodiscard]] int dijkstra(int fnode, int tnode) const override;
    [[nodiscard]] std::vector<int> dijkstra(int snode) const override;
    [[nodiscard]] std::vector<std::vector<int>> floyd() const override;

    [[nodiscard]] SpanningTree * SpanningTreeDFS(int snode, bool byWeight = false) const override;
    [[nodiscard]] std::vector<SpanningTree *> SpanningForestDFS(bool byWeight = false) const override;
    [[nodiscard]] SpanningTree * SpanningTreeBFS(int snode, bool byWeight = false) const override;
    [[nodiscard]] std::vector<SpanningTree *> SpanningForestBFS(bool byWeight = false) const override;

    [[nodiscard]] SpanningTree * kruskal() const override;

    int nodes() const override;
    int edges() const override;
    bool directed() const override;
    bool weighed() const override;
    bool empty() const override;

};

#endif // MGRAPH_H
