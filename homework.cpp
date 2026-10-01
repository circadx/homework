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

int main()
{
    int t[] = {5,5,5,5,6,6,7,7,7,7,7,8};
    size_t lns[] = {4,2,5,1};
    size_t n = 12;
    size_t rows = 4;

    int ** mtx = convert(t, n, lns, rows);
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < lns[i]; ++j)
        {
            std::cout << mtx[i][j] << ' ';
        }
        std::cout << '\n';
    }
    rmMtx(mtx,rows);
    return 0;
}