#include <stack>
#include <queue>

#include "mgraph.h"

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

        qDebug() << "Visiting: " << current;

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

    this->_fill();
}

MGraph::~MGraph()
{
    for (auto& row : this->_matrix)
            for (int* elem : row)
                delete elem;
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

void MGraph::print() const
{
    QString oArr = "-----", cArr = "---->";

    if (!this->_directed)
        oArr = "<----";

    for (int row = 0; row < this->_nodes; row++)
        for (int elem = (this->_directed ? 0 : row); elem < this->_nodes; elem++)
        {
            if (this->_matrix[row][elem] != nullptr)
                qDebug().noquote() << "(" << row << ")" << oArr << *this->_matrix[row][elem] << cArr << "(" << elem << ")";
        }
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

void MGraph::weighted(const bool &weighted)
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

        qDebug() << "Visiting: " << current;

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

    auto* visited = new bool[this->_nodes];

    std::fill_n(visited, this->_nodes, false);

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

    bool* visited = new bool[this->_nodes];
    std::fill_n(visited, this->_nodes, false);

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

    bool* visited = new bool[this->_nodes];
    std::fill_n(visited, this->_nodes, false);

    std::function<void(int)> _dfs = [&](int snode)
    {
        std::stack<int> nodes;
        nodes.push(snode);
        visited[snode] = true;

        while (!nodes.empty())
        {
            int current = nodes.top();

            bool isDeadEnd = true;

            for (int idx = this->_nodes - 1; idx >= 0; idx--)
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

    return toporder;
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

bool MGraph::weighted() const
{
    return this->_weighed;
}

bool MGraph::empty() const
{
    return this->_nodes == 0;
}
