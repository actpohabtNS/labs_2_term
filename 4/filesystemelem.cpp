#include "filesystemelem.h"

FileSystemElem::FileSystemElem(bool isFolder, QString name, int size, const QTime &lastEdited)
    : _isFolder(isFolder), _name(name), _size(size), _lastEdited(lastEdited) {}

FileSystemElem::~FileSystemElem() {}

bool FileSystemElem::operator=(const QTime &time) const
{
    return this->_lastEdited == time;
}

bool FileSystemElem::operator<(const QTime &time) const
{
    return this->_lastEdited < time;
}

bool FileSystemElem::operator<=(const QTime &time) const
{
    return this->_lastEdited <= time;
}

bool FileSystemElem::operator>(const QTime &time) const
{
    return this->_lastEdited > time;
}

bool FileSystemElem::operator>=(const QTime &time) const
{
    return this->_lastEdited >= time;
}

bool FileSystemElem::operator=(int size) const
{
    return this->_size == size;
}

bool FileSystemElem::operator<(int size) const
{
    return this->_size < size;
}

bool FileSystemElem::operator<=(int size) const
{
    return this->_size <= size;
}

bool FileSystemElem::operator>(int size) const
{
    return this->_size > size;
}

bool FileSystemElem::operator>=(int size) const
{
    return this->_size >= size;
}

bool FileSystemElem::contains(QString str) const
{
    return this->_name.contains(str);
}

bool FileSystemElem::isInTimeInterval( QTime min,  QTime max) const
{
    if (min <= this->_lastEdited && this->_lastEdited <= max)
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

QTime FileSystemElem::lastEdited() const
{
    return this->_lastEdited;
}

void FileSystemElem::setSize(int size)
{
    this->_size = size;
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
