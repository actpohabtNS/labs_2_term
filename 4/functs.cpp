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
