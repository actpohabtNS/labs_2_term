#ifndef FILESYSTEMELEM_H
#define FILESYSTEMELEM_H

#include <QString>
#include <QTime>
#include <QTextStream>

class FileSystemElem
{
private:
    bool _isFolder;
    QString _name;
    int _size;
    QTime _lastChanged;

public:
    FileSystemElem(bool isFolder, QString name, int size, const QTime& lastChanged);
    virtual ~FileSystemElem();

    bool isInTimeInterval(const QTime& min, const QTime& max) const;
    bool isInSizeInterval(int min, int max) const;

    bool isFolder() const;
    QString name() const;
    int size() const;
    QTime lastChanged() const;

    void setSize(int size);
    void setLastChanged(const QTime& lastChanged);

    friend QTextStream& operator<<(QTextStream &ostream, const FileSystemElem& fsElem)
    {
        return ostream << fsElem._name << "\t\t" << fsElem._size << " kB\t\t" << fsElem._lastChanged.toString();
    }
};

bool containsStr(const FileSystemElem& elem, QString str);
bool isInTimeInterval(const FileSystemElem& elem,  QTime min,  QTime max);
bool isInSizeInterval(const FileSystemElem& elem, int min, int max);

#endif // FILESYSTEMELEM_H
