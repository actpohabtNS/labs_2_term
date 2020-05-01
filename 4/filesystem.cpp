#include "filesystem.h"

int FileSystem::_elemsCount(const std::vector<int> &path, bool countingFolders) const
{
    int elems = 0;

    std::vector<FileSystemElem> elemsVec = this->_fileTree->preorderTravData(path);

    for (FileSystemElem elem : elemsVec)
    {
        if ( countingFolders ? elem.isFolder() : !elem.isFolder() )
            elems++;
    }

    return elems;
}

QTime FileSystem::_timeEdited(const std::vector<int> &path, bool first) const
{
    std::vector<FileSystemElem> elems = this->_fileTree->preorderTravData(path);

    QTime time = elems[0].lastEdited();

    for (FileSystemElem elem : elems)
    {
        if ( first ? time > elem.lastEdited() : time < elem.lastEdited() )
            time = elem.lastEdited();
    }

    return time;
}

void FileSystem::_changeSize(const std::vector<int> &path, int shift)
{
    _get(path).setSize(_get(path).size() + shift);
}

void FileSystem::_changeBranchSize(const std::vector<int> &path, int shift)
{
    std::vector<int> parentPath = path;
    while (!parentPath.empty())
    {
        this->_changeSize(parentPath, shift);
        parentPath.pop_back();
    }

    this->_changeSize(parentPath, shift);
}

FileSystem::FileSystem(const FileSystemElem &root) {
    this->_fileTree = new GeneralTree<FileSystemElem>(root);
}

FileSystem::~FileSystem() {}

void FileSystem::insert(const std::vector<int> &path, const FileSystemElem &elem)
{
    if (!this->_fileTree->get(path).isFolder())
        return;

    this->_fileTree->insert(path, elem);
    this->_changeBranchSize(path, elem.size());
}

void FileSystem::remove(const std::vector<int> &path)
{
    int size = this->_fileTree->get(path).size();

    this->_fileTree->removeSubtree(path);

    std::vector<int> brenchPath(path);
    brenchPath.pop_back();
    this->_changeBranchSize(brenchPath, size);
}

int FileSystem::size(const std::vector<int> &path) const
{
    return this->_fileTree->get(path).size();
}

int FileSystem::filesCount(const std::vector<int> &path) const
{
    return this->_elemsCount(path, false);
}

int FileSystem::foldersCount(const std::vector<int> &path) const
{
    return this->_elemsCount(path, true);
}

QTime FileSystem::firstEdited(const std::vector<int> &path) const
{
    return this->_timeEdited(path, true);
}

QTime FileSystem::lastEdited(const std::vector<int> &path) const
{
    return this->_timeEdited(path, false);
}

void FileSystem::filterByName(QString name)
{
    this->_filterByFunc(containsStr, name);
}

void FileSystem::filterBySize(int min, int max)
{
    this->_filterByFunc(isInSizeInterval, min, max);
}

void FileSystem::filterByLastEdited( QTime min,  QTime max)
{
    this->_filterByFunc(isInTimeInterval, min, max);
}
