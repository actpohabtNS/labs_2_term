#include <QDebug>
#include <stack>
#include <queue>
#include <map>

#include "lgraph.h"
#include "mgraph.h"
#include "random.h"

// ---------------------------------------- Edge ----------------------------------------

LGraph::Edge::Edge(int toNode, int weight)
    : toNode(toNode), weight(weight) {}



// ---------------------------------------- LGraph ----------------------------------------

int LGraph::_edgeIdx(const int &fnode, const int &tnode) const
{
    if (fnode >= this->_nodes || tnode >= this->_nodes)
        return -1;

    int edgeIdx = -1;

    for (uint edge = 0; edge < this->_list[fnode].size(); edge++)
        if (this->_list[fnode][edge].toNode == tnode)
        {
            edgeIdx = edge;
            break;
        }

    return edgeIdx;
}

void LGraph::_addEdge(const int &fnode, const int &tnode, const int &weight, const bool &increment)
{
    assert(fnode < this->_nodes && tnode < this->_nodes);

    if (fnode == tnode) //self-loops are not implemented
        return;

    if (increment)
            this->_edges++;

    this->_list[fnode].emplace_back(tnode, weight);

    if (!this->_directed && fnode != tnode)
        this->_list[tnode].emplace_back(fnode, weight);
}

void LGraph::_removeOneWays()
{
    for (int node = 0; node < this->_nodes; node++)
        for (uint edge = 0; edge < this->_list[node].size(); edge++)
        {
            int toNode = this->_list[node][edge].toNode;

            bool isDirectedEdge = true;

            for (uint toNodeEdge = 0; toNodeEdge < this->_list[toNode].size(); toNodeEdge++)
                if (this->_list[toNode][toNodeEdge].toNode == node)
                {
                    isDirectedEdge = false;
                    break;
                }

            if (isDirectedEdge)
            {
                this->_edges--;

                this->_list[node].erase(this->_list[node].begin() + edge);

                edge--;
            }
        }
}

void LGraph::_equateWeights()
{
    for (auto &node : this->_list)
        for (LGraph::Edge &edge : node)
            edge.weight = 1;
}

void LGraph::_fill()
{
    int fnode;
    int tnode;
    int edges = 0;

    while (edges != this->_edges)
    {
        fnode = getRandomInt(0, this->_nodes - 1);
        tnode = getRandomInt(0, this->_nodes - 1);

        if (fnode == tnode) //loops are not implemented
            continue;

        if (this->_edgeIdx(fnode, tnode) == -1)
        {
            if (!this->_directed && this->_edgeIdx(tnode, fnode) != -1)
                continue;

            this->_addEdge(fnode, tnode, this->_weighed ? getRandomInt(1, 100) : 1, false);
            edges++;
        }
    }
}

int LGraph::_firstNeighbour(int node, int max) const
{
    for (uint idx = 0; idx < this->_list[node].size(); idx++)
    {
        if (max == -1 || this->_list[node][idx].weight < max)
            return idx;
    }

    return -1;
}

int LGraph::_furthestNeighbour(int node, int max) const
{
    if (this->_list[node].size() == 0)
        return -1;

    int furthNeigh = this->_firstNeighbour(node, max);

    for (uint idx = 0; idx < this->_list[node].size(); idx++)
    {
        if (this->_list[node][idx].weight > this->_list[node][furthNeigh].weight)
        {
            if (max == -1)
            {
                furthNeigh = idx;
            } else
            {
                if (this->_list[node][idx].weight < max)
                    furthNeigh = idx;
            }
        }
    }

    return furthNeigh;
}

std::vector<int> LGraph::_neighboursWithWeight(int node, int weight) const
{
    std::vector<int> nodes;

    for (int idx = 0; idx < this->_nodes; idx++)
        if (this->_list[node][idx].weight == weight)
            nodes.emplace_back(idx);

    return nodes;
}

std::vector<int> LGraph::_descendingNeighbours(int node) const
{
    std::vector<std::pair<int, int>> nodesWeights;

    for (uint edge = 0; edge < this->_list[node].size(); edge++)
        nodesWeights.emplace_back(this->_list[node][edge].weight, edge);

    std::sort(nodesWeights.begin(), nodesWeights.end(),
              [](const std::pair<int, int> &p1, const std::pair<int, int> &p2)
    {
        return p1.first > p2.first;
    });

    std::vector<int> nodes;

    for (auto nodeWeight : nodesWeights)
        nodes.emplace_back(nodeWeight.second);

    return nodes;
}

void LGraph::_dfs(const int &snode, bool *visited, bool byWeight, std::vector<int> *trav) const
{
    if (visited[snode])
        return;

    std::stack<int> nodes;
    nodes.push(snode);
    visited[snode] = true;

    while (!nodes.empty())
    {
        int current = nodes.top();
        nodes.pop();

        if (trav)
            trav->emplace_back(current);

        if (!byWeight)
        {
            for (int edge = this->_list[current].size() - 1; edge >= 0; edge--)
                if (!visited[this->_list[current][edge].toNode])
                {
                    nodes.push(this->_list[current][edge].toNode);
                    visited[this->_list[current][edge].toNode] = true;
                }
        } else
        {
            auto descNeigh = this->_descendingNeighbours(current);

            for (int edge : descNeigh)
            {
                if (!visited[this->_list[current][edge].toNode])
                {
                    nodes.push(this->_list[current][edge].toNode);
                    visited[this->_list[current][edge].toNode] = true;
                }
            }
        }
    }
}

void LGraph::_transpose() const
{
    std::vector<std::vector<LGraph::Edge>> newList(this->_nodes);

    for (int node = 0; node < this->_nodes; node++)
        for (const auto& edge : this->_list[node])
            newList[edge.toNode].emplace_back(node, edge.weight);

    this->_list = newList;
}

std::vector<int> LGraph::_dijkstra(int snode) const
{
    std::vector<int> distance(this->_nodes, -1);
    std::priority_queue<std::pair<int, int>> pqueue;

    distance[snode] = 0;
    pqueue.emplace(0, snode);

    while (!pqueue.empty())
    {
        snode = pqueue.top().second;
        pqueue.pop();

        for (const auto& edge : this->_list[snode])
        {
            if (distance[edge.toNode] == -1 || distance[edge.toNode] > distance[snode] + edge.weight)
            {
                distance[edge.toNode] = distance[snode] + edge.weight;
                pqueue.emplace(-distance[edge.toNode], edge.toNode);
            }
        }
    }

    return distance;
}

LGraph::LGraph(int nodes, int edges, bool directed, bool weighted)
    : _directed(directed), _weighed(weighted)
{
    this->_nodes = nodes >= 0 ? nodes : 0;
    edges = edges >= 0 ? edges : 0;

    int directedDivider = this->_directed ? 1 : 2;
    this->_edges = edges > nodes*(nodes-1)/directedDivider ? nodes*(nodes-1)/directedDivider : edges;

    this->_list.resize(this->_nodes);

    if (edges != 0)
        this->_fill();
}

LGraph::LGraph(const MGraph &mGraph)
    : _nodes(mGraph._nodes), _edges(mGraph._edges), _directed(mGraph._directed), _weighed(mGraph._weighed) {

    this->_list.resize(this->_nodes);

    for (int row = 0; row < this->_nodes; row++)
        for (int idx = 0; idx < this->_nodes; idx++)
            if (mGraph._matrix[row][idx])
                this->_list[row].emplace_back(idx, *mGraph._matrix[row][idx]);
}

void LGraph::build(const MGraph &mGraph)
{
    this->_nodes = mGraph._nodes;
    this->_edges = mGraph._edges;
    this->_directed = mGraph._directed;
    this->_weighed = mGraph._weighed;

    this->_list.resize(this->_nodes);

    for (int row = 0; row < this->_nodes; row++)
        for (int idx = 0; idx < this->_nodes; idx++)
            if (mGraph._matrix[row][idx])
                this->_list[row].emplace_back(idx, *mGraph._matrix[row][idx]);
}

void LGraph::addNode()
{
    this->_nodes++;

    this->_list.emplace_back(std::vector<Edge>(0));
}

void LGraph::addEdge(const int &fnode, const int &tnode)
{
    this->_addEdge(fnode, tnode, 1);
}

void LGraph::addEdge(const int &fnode, const int &tnode, const int &weight)
{
    if (!this->_weighed)
        this->_weighed = true;

    this->_addEdge(fnode, tnode, weight);
}

void LGraph::eraseEdge(const int &fnode, const int &tnode)
{
    int edgeIdx = this->_edgeIdx(fnode, tnode);

    if (edgeIdx == -1)
        return;

    this->_list[fnode].erase(this->_list[fnode].begin() + edgeIdx);

    if (!this->_directed)
        this->_list[tnode].erase(this->_list[tnode].begin() + this->_edgeIdx(tnode, fnode));
}

void LGraph::eraseEdges()
{
    this->_edges = 0;

    for (int i = 0; i < this->_nodes; i++)
        this->_list[i].clear();
}

QString LGraph::QStr() const
{
    QString QStr;

    QString oArr = " ----- ", cArr = " ----> ";

    for (int node = 0; node < this->_nodes; node++)
        for (const auto& edge : this->_list[node])
        {
            QStr += "( " + QString::number(node) + " )" + oArr + QString::number(edge.weight) + cArr + "( " + QString::number(edge.toNode) + " )";
            QStr += "\n";
        }

    return QStr;
}

void LGraph::print() const
{
    qDebug().noquote() << this->QStr();
}

void LGraph::directed(const bool &directed)
{
    if (!this->_directed && directed)
        this->_edges *= 2;

    if (this->_directed && !directed)
    {
        this->_removeOneWays();
        this->_edges /= 2;
    }

    this->_directed = directed;
}

void LGraph::weighed(const bool &weighted)
{
    if (this->_weighed && !weighted)
        this->_equateWeights();

    this->_weighed = weighted;
}

void LGraph::dfs(const int &snode, bool *visited, bool byWeight) const
{
    this->_dfs(snode, visited, byWeight);
}

std::vector<int> LGraph::dfs(const int &snode) const
{
    std::vector<int> trav;

    bool* visited = new bool[this->_nodes];
    this->_dfs(snode, visited, false, &trav);

    delete [] visited;

    return trav;
}

void LGraph::bfs(const int &snode, bool *visited, bool byWeight) const
{
    std::fill_n(visited, this->_nodes, false);

    std::queue<int> nodes;
    nodes.push(snode);
    visited[snode] = true;

    while (!nodes.empty())
    {
        int current = nodes.front();
        nodes.pop();

        if (!byWeight)
        {
            for (const auto& edge : this->_list[current])
                if (!visited[edge.toNode])
                {
                    nodes.push(edge.toNode);
                    visited[edge.toNode] = true;
                }
        } else
        {
            auto descNeigh = this->_descendingNeighbours(current);

            for (int edge = descNeigh.size() - 1; edge >= 0; edge--)
            {
                if (!visited[this->_list[current][descNeigh[edge]].toNode])
                {
                    nodes.push(this->_list[current][descNeigh[edge]].toNode);
                    visited[this->_list[current][descNeigh[edge]].toNode] = true;
                }
            }
        }
    }
}

bool LGraph::connected() const
{
    bool connected = true;

    auto* visited = new bool[this->_nodes]();

    this->dfs(0, visited);

    for (int idx = 0; idx < this->_nodes; idx++)
        if (!visited[idx])
        {
            connected = false;
            break;
        }

    if (connected)
    {
        std::fill_n(visited, this->_nodes, false);

        this->_transpose();

        this->dfs(0, visited);

        for (int idx = 0; idx < this->_nodes; idx++)
            if (!visited[idx])
            {
                connected = false;
                break;
            }

        this->_transpose();
    }

    delete [] visited;

    return connected;
}

bool LGraph::cyclic() const
{
    std::vector<int> visited(this->_nodes, 0);

    std::function<bool(int, int)> _dfs = [&](uint snode, int parent) //white, grey, black (coloring) algorithm
    {
        visited[snode] = 1;

        for (const auto& edge : this->_list[snode])
        {
           if (visited[edge.toNode] == 0)
           {
                if (_dfs(edge.toNode, snode))
                    return true;

           } else if (visited[edge.toNode] == 1)
           {
               if (!this->_directed && edge.toNode == parent)
                   continue;

                return true;
            }
        }

        visited[snode] = 2;
        return false;
    };

    for (int node = 0; node < this->_nodes; node++)
    {
        if (visited[node])
            continue;

        if (_dfs(node, -1))
            return true;
    }

    return false;
}

std::vector<std::vector<int> > LGraph::components() const
{
    std::vector<std::vector<int>> components;

    std::vector<int> component;

    bool* visited = new bool[this->_nodes]();

    if (!this->_directed)
    {
        for (int idx = 0; idx < this->_nodes; idx++)
        {
            if (visited[idx])
                continue;

            component.clear();
            this->_dfs(idx, visited, false, &component);
            components.emplace_back(component);
        }
    } else                          // Kosaraju's algorithm
    {
        std::vector<int> trav;

        for (int idx = 0; idx < this->_nodes; idx++)
            this->_dfs(idx, visited, false, &trav);

        std::reverse(trav.begin(), trav.end());

        this->_transpose();

        std::fill_n(visited, this->_nodes, false);

        while (!trav.empty())
        {
            int current = trav.back();
            trav.pop_back();

            component.clear();

            if (visited[current])
                continue;

            this->_dfs(current, visited, false, &component);

            components.emplace_back(component);
        }

        this->_transpose();
    }

    delete [] visited;

    return components;
}

std::vector<int> LGraph::topologicalSort() const
{
    if (!this->_directed || this->cyclic())
        return {};

    std::vector<int> toporder;

    bool* visited = new bool[this->_nodes]();

    std::function<void(int)> _dfs = [&](int snode)
    {
        std::stack<int> nodes;
        nodes.push(snode);
        visited[snode] = true;

        while (!nodes.empty())
        {
            int current = nodes.top();

            bool isDeadEnd = true;

            for (const auto& edge : this->_list[current])
                if (!visited[edge.toNode])
                {
                    nodes.push(edge.toNode);
                    visited[edge.toNode] = true;
                    isDeadEnd = false;
                }

            if (isDeadEnd)
            {
                toporder.emplace_back(current);
                nodes.pop();
            }
        }

    };

    for (int currIdx = 0; currIdx < this->_nodes; currIdx++)
    {
        if (visited[currIdx])
            continue;

        _dfs(currIdx);
    }

    delete [] visited;

    std::reverse(toporder.begin(), toporder.end());

    return toporder;
}

int LGraph::dijkstra(int fnode, int tnode) const
{
    int f_t = this->_dijkstra(fnode)[tnode];
    int t_f = this->_dijkstra(tnode)[fnode];

    return std::min(f_t, t_f);
}

std::vector<int> LGraph::dijkstra(int snode) const
{
    return this->_dijkstra(snode);
}

std::vector<std::vector<int>> LGraph::floyd() const
{
    MGraph mgraph(*this);

    return mgraph.floyd();
}

SpanningTree *LGraph::SpanningTreeDFS(int snode, bool byWeight) const
{
    if (!this->_nodes)
        return nullptr;

    std::map<int, SpanningTree::Node*> treeNodes = { { snode, new SpanningTree::Node(snode) } };
    auto* tree = new SpanningTree(treeNodes[snode]);
    bool* visited = new bool[this->_nodes]();

    std::function<void(int)> _dfs = [&](int snode)
    {
        visited[snode] = true;

        if (!byWeight)
        {
            for (const auto& edge : this->_list[snode])
            {
                if (!visited[edge.toNode])
                {
                    if (treeNodes.find(edge.toNode) == treeNodes.end())
                        treeNodes[edge.toNode] = new SpanningTree::Node(edge.toNode);

                    tree->link(treeNodes[snode], treeNodes[edge.toNode], edge.weight);
                    _dfs(edge.toNode);
                }
            }
        } else
        {
            auto descNeigh = this->_descendingNeighbours(snode);

            for (int edge = descNeigh.size()-1; edge >= 0; edge--)
            {
                if (!visited[this->_list[snode][edge].toNode])
                {
                    if (treeNodes.find(this->_list[snode][edge].toNode) == treeNodes.end())
                        treeNodes[this->_list[snode][edge].toNode] = new SpanningTree::Node(this->_list[snode][edge].toNode);

                    tree->link(treeNodes[snode], treeNodes[this->_list[snode][edge].toNode], this->_list[snode][edge].weight);
                    _dfs(this->_list[snode][edge].toNode);
                }
            }
        }
    };

    _dfs(snode);

    return tree;
}

std::vector<SpanningTree *> LGraph::SpanningForestDFS(bool byWeight) const
{
    std::vector<SpanningTree*> STrees;

    for (auto comp : this->components())
        STrees.emplace_back(this->SpanningTreeDFS(comp[0], byWeight));

    return STrees;
}

SpanningTree *LGraph::SpanningTreeBFS(int snode, bool byWeight) const
{
    if (!this->_nodes)
        return nullptr;

    std::map<int, SpanningTree::Node*> treeNodes = { { snode, new SpanningTree::Node(snode) } };
    auto* tree = new SpanningTree(treeNodes[snode]);
    bool* visited = new bool[this->_nodes]();

    std::function<void(int)> _bfs = [&](int snode)
    {
        std::queue<int> nodes;
        nodes.push(snode);
        visited[snode] = true;

        while (!nodes.empty())
        {
            int current = nodes.front();
            nodes.pop();

            if (!byWeight)
            {
                for (const auto& edge : this->_list[current])
                {
                    if (!visited[edge.toNode])
                    {
                        nodes.push(edge.toNode);
                        visited[edge.toNode] = true;

                        if (treeNodes.find(edge.toNode) == treeNodes.end())
                            treeNodes[edge.toNode] = new SpanningTree::Node(edge.toNode);

                        tree->link(treeNodes[current], treeNodes[edge.toNode], edge.weight);
                    }
                }
            } else
            {
                auto descNeigh = this->_descendingNeighbours(current);

                for (int edge = descNeigh.size()-1; edge >= 0; edge--)
                {
                    if (!visited[this->_list[current][edge].toNode])
                    {
                        nodes.push(this->_list[current][edge].toNode);
                        visited[this->_list[current][edge].toNode] = true;

                        if (treeNodes.find(this->_list[current][edge].toNode) == treeNodes.end())
                            treeNodes[this->_list[current][edge].toNode] = new SpanningTree::Node(this->_list[current][edge].toNode);

                        tree->link(treeNodes[current], treeNodes[this->_list[current][edge].toNode], this->_list[current][edge].weight);
                    }
                }
            }
        }
    };

    _bfs(snode);

    return tree;
}

std::vector<SpanningTree *> LGraph::SpanningForestBFS(bool byWeight) const
{
    std::vector<SpanningTree*> STrees;

    for (auto comp : this->components())
        STrees.emplace_back(this->SpanningTreeBFS(comp[0], byWeight));

    return STrees;
}

SpanningTree *LGraph::kruskal() const
{
    if (!this->connected() || !this->_weighed)
        return nullptr;

    struct Edge
    {
        int fnode;
        int tnode;
        int weight;

        Edge() = default;
        Edge(int fnode, int tnode, int weight) : fnode(fnode), tnode(tnode), weight(weight) {}
    };

    std::vector<Edge> edges;

    for (int fnode = 0; fnode < this->_nodes; fnode++)
        for (const auto& edge : this->_list[fnode])
        {
            edges.emplace_back(fnode, edge.toNode, edge.weight);
        }

    std::sort(edges.begin(), edges.end(), [](const Edge& edge1, const Edge& edge2)
    {
         return edge1.weight > edge2.weight;    //sort as descending
    });

    LGraph tempG(this->_nodes);

    while (!edges.empty())
    {
        Edge currEdge = edges.back();
        edges.pop_back();

        tempG.addEdge(currEdge.fnode, currEdge.tnode, currEdge.weight);

        if (tempG.cyclic())
            tempG.eraseEdge(currEdge.fnode, currEdge.tnode);
    }

    SpanningTree* sTree = tempG.SpanningTreeDFS(0);

    return sTree;
}

int LGraph::nodes() const
{
    return this->_nodes;
}

int LGraph::edges() const
{
    return this->_edges;
}

bool LGraph::directed() const
{
    return this->_directed;
}

bool LGraph::weighed() const
{
    return this->_weighed;
}

bool LGraph::empty() const
{
    return this->_nodes == 0;
}
