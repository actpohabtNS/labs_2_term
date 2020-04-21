#ifndef GENERALTREE_H
#define GENERALTREE_H
#include <vector>
#include <stack>
#include <queue>
#include <utility>
#include <functs.h>
#include <iostream>
#include <QDebug>

QString pathToQStr(std::vector<int> path, std::vector<int> maxMap);

template <typename T>
class Node {
private:
    T data;
    std::vector<Node<T>*> children;

public:
    Node()
    {
        this->data = NULL;
    }

    Node(T data)
    {
        this->data = data;
    }

    Node(T data, std::vector<Node<T>*> children)
    {
        this->data = data;
        this->children = children;
    }

    ~Node()
    {
        delete &data;
        delete &children;
    }

    bool contains(T searchData)
    {
        std::stack<Node*> nodes;

        nodes.push(this);

        while (!nodes.empty())
        {
            Node* current = nodes.top();
            nodes.pop();

            if (current->data == searchData)
                return true;

            if (current->children.size() != 0)
            {
                for(int idx = current->children.size() - 1; idx >= 0; idx--)
                {
                    nodes.push(current->children[idx]);
                }
            }
        }

        return false;
    }

    T get(std::vector<int> path)
    {
        Node* node = this;

        for (int idx : path)
        {
            node = node->children[idx];
        }

        return node->data;
    }

    void set(std::vector<int> path, T newData)
    {
        Node* node = this;

        for (int idx : path)
        {
            node = node->children[idx];
        }

        node->data = newData;
    }

    Node* remove(std::vector<int> path)
    {
        Node* node = this;

        for (uint elem = 0; elem < path.size(); elem++)
        {
            if (elem == path.size()-1)
            {
                Node* temp = node->children[path[elem]];

                node->children.erase(node->children.begin() + path[elem]);
                node = temp;
                break;
            }

            node = node->children[path[elem]];

        }

        Node* temp = new Node(node->getData(), node->getChildren());
        delete node;
        return temp;
    }

    void remove(T removingData)
    {
        std::vector<int> removingPath;

        while (this->contains(removingData))
        {
            removingPath = this->getPath(removingData);
            this->remove(removingPath);
        }
    }


    void insert(std::vector<int> path, T data)
    {
        Node* parent = this;

        for (int idx : path)
        {
            parent = parent->children[idx];
        }

        parent->children.push_back(new Node(data));
    }

    std::vector<int> getPath(T searchData)
    {
        std::stack<Node*> nodes;
        nodes.push(this);

        std::stack<std::vector<int>> intPaths;
        intPaths.push({});

        while (!nodes.empty())
        {
            Node* current = nodes.top();
            nodes.pop();

            if (current->data == searchData)
            {
                return intPaths.top();
            }

            std::vector<int> parentPath = intPaths.top();
            intPaths.pop();

            if (current->children.size() != 0)
            {
                for (int idx = current->children.size() - 1; idx >= 0; idx--)
                {
                    std::vector<int> extendedPath(parentPath);
                    extendedPath.push_back(idx);

                    nodes.push(current->children[idx]);
                    intPaths.push(extendedPath);
                }
            }
        }

        return {-1};
    }

    QString getSubtreeQStr(std::vector<int> maxChildrenMap)
    {
        std::stack<Node*> nodes;
        nodes.push(this);

        std::stack<std::vector<int>> intPaths;
        intPaths.push({});

        QString subtreeQStr;

        while (!nodes.empty())
        {
            Node<T>* current = nodes.top();
            nodes.pop();

            std::vector<int> parentPath = intPaths.top();
            intPaths.pop();

            //subtreeQStr += QVariant(*current).toString();
            QTextStream(&subtreeQStr) << *current;
            subtreeQStr += pathToQStr(parentPath, maxChildrenMap);
            subtreeQStr += "\n";

            if (current->children.size() != 0)
            {
                for (int idx = current->children.size() - 1; idx >= 0; idx--)
                {
                    std::vector<int> extendedPath(parentPath);
                    extendedPath.push_back(idx);

                    nodes.push(current->children[idx]);
                    intPaths.push(extendedPath);
                }
            }

        }

        return subtreeQStr;
    }

    std::vector<int> getMaxChildrenMap()
    {
        std::queue<Node*> nodes;
        nodes.push(this);

        std::vector<int> maxChildrenMap;

        int thisLevelNodes = 1;
        int nextLevelNodes = 0;
        int levelMaxDigits = getDigitsNum(this->getChildrenSize()-1);

        while (!nodes.empty())
        {
            Node* current = nodes.front();
            nodes.pop();

            if (thisLevelNodes == 0)
            {
                thisLevelNodes = nextLevelNodes;
                nextLevelNodes = 0;
                maxChildrenMap.push_back(levelMaxDigits);
                levelMaxDigits = getDigitsNum(current->getChildrenSize()-1);
            }

            int levelDigits = getDigitsNum(current->getChildrenSize()-1);

            if (levelMaxDigits < levelDigits)
            {
                levelMaxDigits = levelDigits;
            }

            if (current->getChildrenSize() != 0)
            {
                for (int idx = 0; idx < current->getChildrenSize(); idx++)
                {
                    nodes.push(current->children[idx]);
                }
            }
            nextLevelNodes += current->getChildrenSize();
            thisLevelNodes--;

        }

        return maxChildrenMap;
    }

    void print()
    {
        std::stack<Node*> nodes;

        nodes.push(this);

        while (!nodes.empty())
        {
            Node* current = nodes.top();
            nodes.pop();

            qDebug() << current->data;

            if (current->children.size() != 0)
            {
                for (int idx = current->getChildrenSize() - 1; idx >= 0; idx--)
                {
                    nodes.push(current->children[idx]);
                }
            }
        }
    }

    T getData()
    {
        return data;
    }

    std::vector<Node<T>*> getChildren()
    {
        return children;
    }

    int getChildrenSize()
    {
        return children.size();
    }

    friend std::ostream& operator<<(std::ostream& ostream, const Node<T>& node)
    {
        return ostream << node.data;
    }

    friend QTextStream& operator<<(QTextStream &ostream, const Node<T>& node)
    {
        return ostream << node.data;
    }

};

QString pathToQStr(std::vector<int> path, std::vector<int> maxMap)
{
    QString resQStr = "—> ";

    for (uint pathIdx = 0; pathIdx < path.size(); pathIdx++)
    {
        for (int nullDigits = maxMap[pathIdx] - getDigitsNum(path[pathIdx]); nullDigits > 0; nullDigits--)
        {
            resQStr += " ";
        }

        resQStr += QString::number(path[pathIdx]);

        if (pathIdx != path.size()-1)
            resQStr += ",";
    }

    resQStr += " <—";
    return resQStr;
}

#endif // GENERALTREE_H
