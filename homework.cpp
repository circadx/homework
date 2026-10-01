#include <iostream>

int ** convert(const int * t, size_t n, const size_t * lns, size_t rows)
{
    int ** res = new int * [rows];
    size_t pos = 0;
    for (size_t i = 0; i< rows; ++i)
    {
        res[i] = new int[lns[i]];

        for (size_t j = 0; j < lns[i]; ++j)
        {
            res[i][j] = t[pos];
            ++pos;
        }
    }
    return res;
}

void rmMtx(int ** mtx, size_t rows)
{
    for (size_t i = 0; i< rows; ++i)
    {
        delete[] mtx[i];
    }
    delete[] mtx;
}