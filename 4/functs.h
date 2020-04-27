#ifndef FUNCTS_H
#define FUNCTS_H

#include <vector>
#include <QString>

int getDigitsNum(int num);

QString pathToQStr(const std::vector<int>& path);

QString pathToQStr(const std::vector<int>& path, const std::vector<int>& maxMap);

#endif // FUNCTS_H
