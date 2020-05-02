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

FileSystemElem FileSystem::_timeEdited(const std::vector<int> &path, bool first) const
{
    std::vector<FileSystemElem> elems = this->_fileTree->preorderTravData(path);

    FileSystemElem timeElem = elems[0];

    for (FileSystemElem elem : elems)
    {
        if ( first ? timeElem.lastChanged() > elem.lastChanged() : timeElem.lastChanged() < elem.lastChanged() )
            timeElem = elem;
    }

    return timeElem;
}

void FileSystem::_changeSize(const std::vector<int> &path, int shift)
{
    FileSystemElem elem = this->_fileTree->get(path);
    elem.setSize(elem.size() + shift);

    this->_fileTree->set(path, elem);
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

void FileSystem::_changeLastChanged(const std::vector<int> &path, const QTime &newTime)
{
    FileSystemElem elem = this->_fileTree->get(path);
    elem.setLastChanged(newTime);

    this->_fileTree->set(path, elem);
}

void FileSystem::_changeBranchLastChanged(const std::vector<int> &path, const QTime &newTime)
{
    std::vector<int> parentPath = path;

    while (!parentPath.empty())
    {
        if (this->_fileTree->get(path).lastChanged() >= newTime)
            return;

        this->_changeLastChanged(parentPath, newTime);
        parentPath.pop_back();
    }

    if (this->_fileTree->get(parentPath).lastChanged() >= newTime)
        return;
    this->_changeLastChanged(parentPath, newTime);
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
    this->_changeBranchLastChanged(path, elem.lastChanged());
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

FileSystemElem FileSystem::firstEdited(const std::vector<int> &path) const
{
    return this->_timeEdited(path, true);
}

FileSystemElem FileSystem::lastEdited(const std::vector<int> &path) const
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

void FileSystem::filterByLastEdited(const QTime& min, const QTime& max)
{
    this->_filterByFunc(isInTimeInterval, min, max);
}

GeneralTree<FileSystemElem> *FileSystem::fileTree() const
{
    return this->_fileTree;
}
