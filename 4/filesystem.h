#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QString>

#include "generalTree.h"
#include "filesystemelem.h"

class FileSystem : public GeneralTree<FileSystemElem> {

private:
    GeneralTree<FileSystemElem>* _fileTree;

    int _elemsCount(const std::vector<int>& path, bool countingFolders) const;
    FileSystemElem _timeEdited(const std::vector<int>& path, bool first) const;

    void _changeSize(const std::vector<int>& path, int shift);
    void _changeBranchSize(const std::vector<int>& path, int shift);
    void _changeLastChanged(const std::vector<int>& path, const QTime& newTime);
    void _changeBranchLastChanged(const std::vector<int>& path, const QTime& newTime);

    template <typename ...Types>
    void _filterByFunc(bool includesByFilter(const FileSystemElem&, Types ...Args), Types ...Args);

    template <typename ...Types>
    void _filterByFunc(bool includesByFilter(const FileSystemElem&, const Types& ...Args), const Types& ...Args);


public:
    explicit FileSystem(const FileSystemElem& root);
    virtual ~FileSystem();

    void insert(const std::vector<int>& path, const FileSystemElem& elem);
    void remove(const std::vector<int>& path);

    int size(const std::vector<int>& path) const;
    int filesCount(const std::vector<int>& path) const;
    int foldersCount(const std::vector<int>& path) const;
    FileSystemElem firstEdited(const std::vector<int>& path) const;
    FileSystemElem lastEdited(const std::vector<int>& path) const;

    void filterByName(QString name);
    void filterBySize(int min, int max);
    void filterByLastEdited(const QTime& min, const QTime& max);

    GeneralTree<FileSystemElem>* fileTree() const;
};

template <typename ...Types>
void FileSystem::_filterByFunc(bool includesByFilter(const FileSystemElem&, Types ...Args), Types ...Args)
{
    std::stack<Node*> nodes;
    nodes.push(this->_root);

    std::stack<std::vector<int>> paths;
    paths.push({});

    Node* current;
    std::vector<int> currentPath;

    while (!nodes.empty())
    {
        current = nodes.top();
        nodes.pop();

        currentPath = paths.top();
        paths.pop();

        for (uint child = 0; child < current->children().size(); child++)
        {
            std::vector<int> childPath(paths.top());
            childPath.push_back(child);

            if (!includesByFilter(current->children()[child]->data(), Args...))
            {
                this->_fileTree->removeSubtree(childPath);
                child--;
            }
            else
            {
                nodes.push(current->children()[child]);
                paths.push(childPath);
            }
        }
    }
}

template<typename ...Types>
void FileSystem::_filterByFunc(bool includesByFilter(const FileSystemElem &, const Types& ... Args), const Types&... Args)
{
    this->_filterByFunc(includesByFilter, Args...);
}
#endif // FILESYSTEM_H
