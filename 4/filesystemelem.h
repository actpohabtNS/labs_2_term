#ifndef FILESYSTEMELEM_H
#define FILESYSTEMELEM_H

#include <QString>
#include <QTime>

class FileSystemElem
{
private:
    bool _isFolder;
    QString _name;
    int _size;
    QTime _lastEdited;

public:
    explicit FileSystemElem(bool isFolder, QString name, int size, const QTime& lastEdited);
    virtual ~FileSystemElem();


    bool operator= (const QTime& time) const;
    bool operator< (const QTime& time) const;
    bool operator<= (const QTime& time) const;
    bool operator> (const QTime& time) const;
    bool operator>= (const QTime& time) const;

    bool operator= (int size) const;
    bool operator< (int size) const;
    bool operator<= (int size) const;
    bool operator> (int size) const;
    bool operator>= (int size) const;

    bool contains(QString str) const;

    bool isInTimeInterval( QTime min,  QTime max) const;
    bool isInSizeInterval(int min, int max) const;

    bool isFolder() const;
    QString name() const;
    int size() const;
    QTime lastEdited() const;

    void setSize(int size);
};

bool containsStr(const FileSystemElem& elem, QString str);
bool isInTimeInterval(const FileSystemElem& elem,  QTime min,  QTime max);
bool isInSizeInterval(const FileSystemElem& elem, int min, int max);

#endif // FILESYSTEMELEM_H
