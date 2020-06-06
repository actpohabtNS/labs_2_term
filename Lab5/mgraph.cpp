#include <stack>
#include <queue>
#include <map>
#include <functional>

#include "mgraph.h"
#include "lgraph.h"

void MGraph::_addEdge(const int &fnode, const int &tnode, const int &weight, const bool& increment)
{
    assert(fnode < this->_nodes && tnode < this->_nodes);

    if (fnode == tnode) //loops are not implemented
        return;

    if (increment)
        this->_edges++;

    this->_matrix[fnode][tnode] = new int(weight);

    if (!this->_directed)
        this->_matrix[tnode][fnode] = new int(weight);
}

void MGraph::_removeOneWays()
{
    for (int fnode = 0; fnode < this->_nodes; fnode++)
        for (int tnode = fnode+1; tnode < this->_nodes; tnode++)
        {
            if (this->_matrix[fnode][tnode] != this->_matrix[tnode][fnode])
            {
                this->_matrix[fnode][tnode] = nullptr;
                this->_matrix[tnode][fnode] = nullptr;
            }

            this->_edges--;
        }
}

void MGraph::_equateWeights()
{
    for (auto& row : this->_matrix)
        for (int* weight : row)
            weight = new int(1);
}

void MGraph::_fill()
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

        if (!this->_matrix[fnode][tnode])
        {
            if (!this->_directed && this->_matrix[tnode][fnode])
                continue;

            this->_addEdge(fnode, tnode, this->_weighed ? getRandomInt(1, 100) : 1, false);
            edges++;
        }
    }
}

int MGraph::_firstNeighbour(int row, int max) const
{
    for (int idx = 0; idx < this->_nodes; idx++)
    {
        if (this->_matrix[row][idx] == nullptr)
            continue;

        if (max == -1 || *this->_matrix[row][idx] < max)
            return idx;
    }

    return -1;
}

int MGraph::_furthestNeighbour(int row, int max) const
{
    int furthNeigh = this->_firstNeighbour(row, max);

    if (furthNeigh == -1)
        return -1;

    for (int idx = 0; idx < this->_nodes; idx++)
    {
        if (this->_matrix[row][idx] == nullptr)
            continue;

        if (*this->_matrix[row][idx] > *this->_matrix[row][furthNeigh])
        {
            if (max == -1)
            {
                furthNeigh = idx;
            } else
            {
                if (*this->_matrix[row][idx] < max)
                    furthNeigh = idx;
            }
        }
    }

    return furthNeigh;
}

std::vector<int> MGraph::_neighboursWithWeight(int row, int weight) const
{
    std::vector<int> nodes;

    for (int idx = 0; idx < this->_nodes; idx++)
        if (this->_matrix[row][idx] != nullptr
                && *this->_matrix[row][idx] == weight)
            nodes.emplace_back(idx);

    return nodes;
}

std::vector<int> MGraph::_descendingNeighbours(int row) const
{
    std::vector<int> nodes;

    int maxWTo = this->_furthestNeighbour(row);

    while (maxWTo != -1)
    {
        auto nWW = this->_neighboursWithWeight(row, *this->_matrix[row][maxWTo]);

        nodes.insert(nodes.end(), nWW.begin(), nWW.end());

        maxWTo = this->_furthestNeighbour(row, *this->_matrix[row][maxWTo]);
    }

    return nodes;
}

void MGraph::_dfs(const int &snode, bool *visited, bool byWeight, std::vector<int> *trav) const
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
            for (int idx = this->_nodes - 1; idx >= 0; idx--)
                if (this->_matrix[current][idx] != nullptr)
                    if (!visited[idx])
                    {
                        nodes.push(idx);
                        visited[idx] = true;
                    }
        } else
        {
            auto descNeigh = this->_descendingNeighbours(current);

            for (int idx : descNeigh)
            {
                if (!visited[idx])
                {
                    nodes.push(idx);
                    visited[idx] = true;
                }
            }
        }
    }
}

void MGraph::_transpose() const
{
    for (int row = 0; row < this->_nodes; row++)
        for (int idx = row + 1; idx < this->_nodes; idx++)
            std::swap(this->_matrix[row][idx], this->_matrix[idx][row]);
}

std::vector<int> MGraph::_dijkstra(int snode) const
{
    std::vector<int> distance(this->_nodes, -1);
    std::priority_queue<std::pair<int, int>> pqueue;

    distance[snode] = 0;
    pqueue.emplace(0, snode);

    while (!pqueue.empty())
    {
        snode = pqueue.top().second;
        pqueue.pop();

        for (int node = 0; node < this->_nodes; node++)
        {
            if (this->_matrix[snode][node] && (distance[node] == -1 || distance[node] > distance[snode] + *this->_matrix[snode][node]))
            {
                distance[node] = distance[snode] + *this->_matrix[snode][node];
                pqueue.emplace(-distance[node], node);
            }
        }
    }

    return distance;
}

MGraph::MGraph()
    : _nodes(0), _edges(0), _directed(false), _weighed(false) {}

MGraph::MGraph(int nodes, int edges, bool directed, bool weighted)
    : _directed(directed), _weighed(weighted)
{
    this->_nodes = nodes >= 0 ? nodes : 0;
    edges = edges >= 0 ? edges : 0;

    int directedDivider = this->_directed ? 1 : 2;
    this->_edges = edges > nodes*(nodes-1)/directedDivider ? nodes*(nodes-1)/directedDivider : edges;

    this->_matrix.resize(this->_nodes);

    for (auto& row : this->_matrix)
         row.resize(this->_nodes, nullptr);

    if (edges != 0)
        this->_fill();
}

MGraph::MGraph(const LGraph &lGraph)
    : _nodes(lGraph._nodes), _edges(lGraph._edges), _directed(lGraph._directed), _weighed(lGraph._weighed) {

    this->_matrix.resize(this->_nodes);

    for (auto& row : this->_matrix)
        row.resize(this->_nodes, nullptr);

    for (int node = 0; node < this->_nodes; node++)
        for (const auto& edge : lGraph._list[node])
            this->_matrix[node][edge.toNode] = new int(edge.weight);
}

MGraph::~MGraph()
{
    for (auto& row : this->_matrix)
            for (int* elem : row)
                delete elem;
}

void MGraph::build(const LGraph &lGraph)
{
    this->_nodes = lGraph._nodes;
    this->_edges = lGraph._edges;
    this->_directed = lGraph._directed;
    this->_weighed = lGraph._weighed;

    this->_matrix.resize(this->_nodes);

    for (auto& row : this->_matrix)
        row.resize(5, nullptr);

    for (int i = 0; i < this->_nodes; i++)
        for (const auto& edge : lGraph._list[i])
            this->_matrix[i][edge.toNode] = new int(edge.weight);
}

void MGraph::addNode()
{
    for (auto& row : this->_matrix)
        row.emplace_back(nullptr);

    this->_nodes++;

    this->_matrix.emplace_back(std::vector<int*>(this->_nodes, nullptr));
}

void MGraph::addEdge(const int &fnode, const int &tnode)
{
    this->_addEdge(fnode, tnode, 1);
}

void MGraph::addEdge(const int &fnode, const int &tnode, const int &weight)
{
    this->_addEdge(fnode, tnode, weight);
}

void MGraph::eraseEdge(const int &fnode, const int &tnode)
{
    assert(fnode < this->_nodes && tnode < this->_nodes);

    if (this->_matrix[fnode][tnode] == nullptr)
        return;

    this->_edges--;

    delete this->_matrix[fnode][tnode];
    this->_matrix[fnode][tnode] = nullptr;

    if (!this->_directed)
    {
        delete this->_matrix[tnode][fnode];
        this->_matrix[tnode][fnode] = nullptr;
    }
}

void MGraph::eraseEdges()
{
    this->_edges = 0;

    for (int i = 0; i < this->_nodes; i++)
        for (int j = 0; j < this->_nodes; j++)
            delete this->_matrix[i][j], this->_matrix[i][j] = nullptr;
}

QString MGraph::QStr() const
{
    QString QStr;

    QString oArr = " ----- ", cArr = " ----> ";

    if (!this->_directed)
        oArr = " <---- ";

    for (int row = 0; row < this->_nodes; row++)
        for (int elem = (this->_directed ? 0 : row); elem < this->_nodes; elem++)
        {
            if (this->_matrix[row][elem] != nullptr)
            {
                QStr += "( " + QString::number(row) + " )" + oArr + *this->_matrix[row][elem] + cArr + "( " + QString::number(elem) + " )";
                QStr += "\n";
            }
        }

    return QStr;
}

void MGraph::print() const
{
    qDebug().noquote() << this->QStr();
}

void MGraph::directed(const bool &directed)
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

void MGraph::weighed(const bool &weighted)
{
    if (this->_weighed && !weighted)
        this->_equateWeights();

    this->_weighed = weighted;
}

void MGraph::dfs(const int &snode, bool *visited, bool byWeight) const
{
    this->_dfs(snode, visited, byWeight);
}

std::vector<int> MGraph::dfs(const int &snode) const
{
    std::vector<int> trav;

    bool* visited = new bool[this->_nodes];
    this->_dfs(snode, visited, false, &trav);

    delete [] visited;

    return trav;
}

void MGraph::bfs(const int &snode, bool *visited, bool byWeight) const
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
            for (int idx = 0; idx < this->_nodes; idx++)
                if (this->_matrix[current][idx] != nullptr)
                    if (!visited[idx])
                    {
                        nodes.push(idx);
                        visited[idx] = true;
                    }
        } else
        {
            auto descNeigh = this->_descendingNeighbours(current);

            for (int idx = descNeigh.size() - 1; idx >= 0; idx--)
            {
                if (!visited[descNeigh[idx]])
                {
                    nodes.push(descNeigh[idx]);
                    visited[descNeigh[idx]] = true;
                }
            }
        }
    }
}

bool MGraph::connected() const
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

bool MGraph::cyclic() const
{
    std::vector<int> visited(this->_nodes, 0);

    std::function<bool(int, int)> _dfs = [&](int snode, int parent) //white, grey, black (coloring) algorithm
    {
        visited[snode] = 1;

        for (int node = 0; node < this->_nodes; node++)
        {
           if (!this->_matrix[snode][node])
               continue;

           if (visited[node] == 0)
           {
                if (_dfs(node, snode))
                    return true;

           } else if (visited[node] == 1)
           {
               if (!this->_directed && node == parent)
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

std::vector<std::vector<int> > MGraph::components() const
{
    std::vector<std::vector<int>> components;

    std::vector<int> component;

    bool* visited = new bool[this->_nodes]();

    if (!this->_directed)
    {
        for (int idx = 0; idx < this->_nodes; idx++)
        {
            if (!visited[idx])
            {
                component.clear();
                this->_dfs(idx, visited, false, &component);
                components.emplace_back(component);
            }
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

std::vector<int> MGraph::topologicalSort() const
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

            for (int idx = 0; idx < this->_nodes; idx++)
            {
                if (this->_matrix[current][idx] != nullptr)
                    if (!visited[idx])
                    {
                        nodes.push(idx);
                        visited[idx] = true;
                        isDeadEnd = false;
                    }
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

int MGraph::dijkstra(int fnode, int tnode) const
{
    int f_t = this->_dijkstra(fnode)[tnode];
    int t_f = this->_dijkstra(tnode)[fnode];

    return std::min(f_t, t_f);
}

std::vector<int> MGraph::dijkstra(int snode) const
{
    return this->_dijkstra(snode);
}

std::vector<std::vector<int>> MGraph::floyd() const
{
    static const int inf = INT_MAX;

    std::vector<std::vector<int>> dist(this->_nodes, std::vector<int>(this->_nodes, 0));

    for (int i = 0; i < this->_nodes; i++)
            for (int j = 0; j < this->_nodes; j++)
                dist[i][j] = (i == j) ? 0 : this->_matrix[i][j] ? *this->_matrix[i][j] : inf;

    for (int k = 0; k < this->_nodes; k++)
        for (int i = 0; i < this->_nodes; i++)
            for (int j = 0; j < this->_nodes; j++)
                if (dist[i][k] != inf && dist[k][j] != inf)
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);

    return dist;
}

SpanningTree *MGraph::SpanningTreeDFS(int snode, bool byWeight) const
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
            for (int idx = 0; idx < this->_nodes; idx++)
            {
                if (!this->_matrix[snode][idx])
                    continue;

                if (!visited[idx])
                {
                    if (treeNodes.find(idx) == treeNodes.end())
                        treeNodes[idx] = new SpanningTree::Node(idx);

                    tree->link(treeNodes[snode], treeNodes[idx], *this->_matrix[snode][idx]);
                    _dfs(idx);
                }
            }
        } else
        {
            auto descNeigh = this->_descendingNeighbours(snode);

            for (int idx = descNeigh.size()-1; idx >= 0; idx--)
            {
                if (!visited[descNeigh[idx]])
                {
                    if (treeNodes.find(descNeigh[idx]) == treeNodes.end())
                        treeNodes[descNeigh[idx]] = new SpanningTree::Node(descNeigh[idx]);

                    tree->link(treeNodes[snode], treeNodes[descNeigh[idx]], *this->_matrix[snode][descNeigh[idx]]);
                    _dfs(descNeigh[idx]);
                }
            }
        }
    };

    _dfs(snode);

    return tree;
}

std::vector<SpanningTree *> MGraph::SpanningForestDFS(bool byWeight) const
{
    std::vector<SpanningTree*> STrees;

    for (auto comp : this->components())
        STrees.emplace_back(this->SpanningTreeDFS(comp[0], byWeight));

    return STrees;
}

SpanningTree *MGraph::SpanningTreeBFS(int snode, bool byWeight) const
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
                for (int idx = 0; idx < this->_nodes; idx++)
                {
                    if (this->_matrix[current][idx] == nullptr)
                        continue;

                    if (!visited[idx])
                    {
                        nodes.push(idx);
                        visited[idx] = true;

                        if (treeNodes.find(idx) == treeNodes.end())
                            treeNodes[idx] = new SpanningTree::Node(idx);

                        tree->link(treeNodes[current], treeNodes[idx], *this->_matrix[current][idx]);
                    }
                }
            } else
            {
                auto descNeigh = this->_descendingNeighbours(current);

                for (int idx = descNeigh.size() - 1; idx >= 0; idx--)
                {
                    if (!visited[descNeigh[idx]])
                    {
                        nodes.push(descNeigh[idx]);
                        visited[descNeigh[idx]] = true;

                        if (treeNodes.find(descNeigh[idx]) == treeNodes.end())
                            treeNodes[descNeigh[idx]] = new SpanningTree::Node(descNeigh[idx]);

                        tree->link(treeNodes[current], treeNodes[descNeigh[idx]], *this->_matrix[current][descNeigh[idx]]);
                    }
                }
            }
        }
    };

    _bfs(snode);

    return tree;
}

std::vector<SpanningTree *> MGraph::SpanningForestBFS(bool byWeight) const
{
    std::vector<SpanningTree*> STrees;

    for (auto comp : this->components())
        STrees.emplace_back(this->SpanningTreeBFS(comp[0], byWeight));

    return STrees;
}

SpanningTree *MGraph::kruskal() const
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
        for (int tnode = (this->_directed ? 0 : fnode); tnode < this->_nodes; tnode++)
        {
            if (!this->_matrix[fnode][tnode])
                continue;

            edges.emplace_back(fnode, tnode, *this->_matrix[fnode][tnode]);
        }

    std::sort(edges.begin(), edges.end(), [](const Edge& edge1, const Edge& edge2)
    {
         return edge1.weight > edge2.weight;    //sort as descending
    });

    MGraph tempG(this->_nodes);

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

int MGraph::nodes() const
{
    return this->_nodes;
}

int MGraph::edges() const
{
    return this->_edges;
}

bool MGraph::directed() const
{
    return this->_directed;
}

bool MGraph::weighed() const
{
    return this->_weighed;
}

bool MGraph::empty() const
{
    return this->_nodes == 0;
}
