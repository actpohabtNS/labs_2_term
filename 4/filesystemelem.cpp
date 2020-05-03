#include "filesystemelem.h"

FileSystemElem::FileSystemElem()
    : _isFolder(false), _name(""), _size(0), _lastChanged(QTime(0,0)) {}

FileSystemElem::FileSystemElem(bool isFolder, QString name, int size, const QTime &lastEdited)
    : _isFolder(isFolder), _name(name), _size(size), _lastChanged(lastEdited) {}

FileSystemElem::~FileSystemElem() {}

bool FileSystemElem::isInTimeInterval(const QTime& min, const QTime& max) const
{
    if (min <= this->_lastChanged && this->_lastChanged <= max)
        return true;
    else
        return false;
}

bool FileSystemElem::isInSizeInterval(int min, int max) const
{
    if (min <= this->_size && this->_size <= max)
        return true;
    else
        return false;
}

bool FileSystemElem::isFolder() const
{
    return this->_isFolder;
}

QString FileSystemElem::name() const
{
    return  this->_name;
}

int FileSystemElem::size() const
{
    return this->_size;
}

QTime FileSystemElem::lastChanged() const
{
    return this->_lastChanged;
}

void FileSystemElem::setSize(int size)
{
    this->_size = size;
}

void FileSystemElem::setLastChanged(const QTime &lastChanged)
{
    this->_lastChanged = lastChanged;
}

bool containsStr(const FileSystemElem &elem, QString str)
{
    return elem.name().contains(str);
}

bool isInTimeInterval(const FileSystemElem &elem, QTime min,  QTime max)
{
    return elem.isInTimeInterval(min, max);
}

bool isInSizeInterval(const FileSystemElem &elem, int min, int max)
{
    return elem.isInSizeInterval(min, max);
}
