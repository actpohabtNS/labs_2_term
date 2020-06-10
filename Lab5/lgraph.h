#ifndef LGRAPH_H
#define LGRAPH_H

#include <vector>

#include "Graph.h"

class MGraph;

class LGraph : public Graph
{
private:
    friend MGraph;

    struct Edge
    {
        int toNode;
        int weight;

        Edge() = default;
        explicit Edge(int toNode, int weight = 1);
    };

    mutable std::vector<std::vector<Edge>> _list;
    int _nodes;
    int _edges;
    bool _directed;
    bool _weighed;

    int _edgeIdx(const int& fnode, const int& tnode) const;
    void _addEdge(const int& fnode, const int& tnode, const int& weight, const bool& increment = true);
    void _removeOneWays();
    void _equateWeights();
    void _fill();
    int _firstNeighbour(int node, int max = -1) const;
    int _furthestNeighbour(int node, int max = -1) const;
    [[nodiscard]] std::vector<int> _neighboursWithWeight(int node, int weight) const;
    [[nodiscard]] std::vector<int> _descendingNeighbours(int node) const;

    void _dfs(const int& snode, bool* visited, bool byWeight, std::vector<int>* trav = nullptr) const;

    void _transpose() const;

    [[nodiscard]] std::vector<int> _dijkstra(int snode) const;

public:
    LGraph();
    explicit LGraph(int nodes, int edges = 0, bool directed = false, bool weighed = false);
    explicit LGraph(const MGraph& mGraph);

    ~LGraph() override = default;

    void build(const MGraph& mGraph);
    void addNode() override;
    void addEdge(const int& fnode, const int& tnode) override;
    void addEdge(const int& fnode, const int& tnode, const int& weight) override;
    void eraseEdge(const int& fnode, const int& tnode) override;
    void eraseEdges() override;

    QString QStr() const override;
    void print() const override;

    QString type() const override;

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

#endif // LGRAPH_H
