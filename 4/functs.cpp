#include "functs.h"

int getDigitsNum(int num)
{
    int digitsNum = 0;
    if (num < 0) digitsNum = 1;
    do
    {
        num /= 10;
        digitsNum++;
    } while (num);

    return digitsNum;
}


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
