#include <iostream>
#include <cstddef>
#include <stdexcept>

class Mtx
{
private:
    std::size_t rows;
    std::size_t cols;
    int *data;

public:
    Mtx()
    {
        rows = 0;
        cols = 0;
        data = nullptr;
    }


    Mtx(std::size_t r, std::size_t c)
    {
        rows = r;
        cols = c;

        data = nullptr;

        if (rows * cols > 0)
        {
            data = new int[rows * cols];

            for (std::size_t i = 0; i < rows * cols; i++)
            {
                data[i] = 0;
            }
        }
    }


    Mtx(const Mtx &other)
    {
        rows = other.rows;
        cols = other.cols;

        data = nullptr;

        if (rows * cols > 0)
        {
            data = new int[rows * cols];

            for (std::size_t i = 0; i < rows * cols; i++)
            {
                data[i] = other.data[i];
            }
        }
    }


    Mtx(Mtx &&other)
    {
        rows = other.rows;
        cols = other.cols;
        data = other.data;

        other.rows = 0;
        other.cols = 0;
        other.data = nullptr;
    }


    Mtx &operator=(const Mtx &other)
    {
        if (this == &other)
        {
            return *this;
        }

        int *new_data = nullptr;

        if (other.rows * other.cols > 0)
        {
            new_data = new int[other.rows * other.cols];

            for (std::size_t i = 0; i < other.rows * other.cols; i++)
            {
                new_data[i] = other.data[i];
            }
        }

        delete[] data;

        rows = other.rows;
        cols = other.cols;
        data = new_data;

        return *this;
    }


    Mtx &operator=(Mtx &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] data;

        rows = other.rows;
        cols = other.cols;
        data = other.data;

        other.rows = 0;
        other.cols = 0;
        other.data = nullptr;

        return *this;
    }


    ~Mtx()
    {
        delete[] data;
    }


    int &get(std::size_t r, std::size_t c)
    {
        if (r >= rows || c >= cols)
        {
            throw std::out_of_range("Matrix index out of range");
        }

        return data[r * cols + c];
    }

    const int &get(std::size_t r, std::size_t c) const
    {
        if (r >= rows || c >= cols)
        {
            throw std::out_of_range("Matrix index out of range");
        }

        return data[r * cols + c];
    }


    std::size_t get_rows() const
    {
        return rows;
    }

    std::size_t get_cols() const
    {
        return cols;
    }


    bool empty() const
    {
        return rows == 0 || cols == 0;
    }


    Mtx operator+(const Mtx &other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            throw std::invalid_argument("Different matrix sizes");
        }

        Mtx result(rows, cols);

        for (std::size_t i = 0; i < rows * cols; i++)
        {
            result.data[i] = data[i] + other.data[i];
        }

        return result;
    }

    void print() const
    {
        for (std::size_t i = 0; i < rows; i++)
        {
            for (std::size_t j = 0; j < cols; j++)
            {
                std::cout << data[i * cols + j] << " ";
            }

            std::cout << "\n";
        }
    }
};


class Mtxs
{
private:
    std::size_t k;
    Mtx *mtxs;

public:
    Mtxs()
    {
        k = 0;
        mtxs = nullptr;
    }


    Mtxs(std::size_t n)
    {
        k = n;

        if (k > 0)
        {
            mtxs = new Mtx[k];
        }
        else
        {
            mtxs = nullptr;
        }
    }


    Mtxs(const Mtxs &other)
    {
        k = other.k;
        mtxs = nullptr;

        if (k > 0)
        {
            mtxs = new Mtx[k];

            for (std::size_t i = 0; i < k; i++)
            {
                mtxs[i] = other.mtxs[i];
            }
        }
    }


    Mtxs(Mtxs &&other)
    {
        k = other.k;
        mtxs = other.mtxs;

        other.k = 0;
        other.mtxs = nullptr;
    }


    Mtxs &operator=(const Mtxs &other)
    {
        if (this == &other)
        {
            return *this;
        }

        Mtx *new_mtxs = nullptr;

        if (other.k > 0)
        {
            new_mtxs = new Mtx[other.k];

            for (std::size_t i = 0; i < other.k; i++)
            {
                new_mtxs[i] = other.mtxs[i];
            }
        }

        delete[] mtxs;

        k = other.k;
        mtxs = new_mtxs;

        return *this;
    }


    Mtxs &operator=(Mtxs &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] mtxs;

        k = other.k;
        mtxs = other.mtxs;

        other.k = 0;
        other.mtxs = nullptr;

        return *this;
    }


    ~Mtxs()
    {
        delete[] mtxs;
    }


    void insert(const Mtx &m)
    {
        insert(k, m);
    }


    void insert(std::size_t index, const Mtx &m)
    {
        if (index > k)
        {
            throw std::out_of_range("Insert index out of range");
        }

        Mtx *new_mtxs = new Mtx[k + 1];

        for (std::size_t i = 0; i < index; i++)
        {
            new_mtxs[i] = mtxs[i];
        }

        new_mtxs[index] = m;

        for (std::size_t i = index; i < k; i++)
        {
            new_mtxs[i + 1] = mtxs[i];
        }

        delete[] mtxs;

        mtxs = new_mtxs;
        k++;
    }


    void insert(std::size_t index, const Mtxs &other)
    {
        if (index > k)
        {
            throw std::out_of_range("Insert index out of range");
        }


        Mtxs temp(other);

        Mtx *new_mtxs = new Mtx[k + temp.k];

        for (std::size_t i = 0; i < index; i++)
        {
            new_mtxs[i] = mtxs[i];
        }

        for (std::size_t i = 0; i < temp.k; i++)
        {
            new_mtxs[index + i] = temp.mtxs[i];
        }

        for (std::size_t i = index; i < k; i++)
        {
            new_mtxs[i + temp.k] = mtxs[i];
        }

        delete[] mtxs;

        mtxs = new_mtxs;
        k += temp.k;
    }


    void erase()
    {
        delete[] mtxs;

        mtxs = nullptr;
        k = 0;
    }


    void erase(std::size_t index)
    {
        if (index >= k)
        {
            throw std::out_of_range("Erase index out of range");
        }

        erase(index, index + 1);
    }


    void erase(std::size_t first, std::size_t last)
    {
        if (first > last || last > k)
        {
            throw std::out_of_range("Erase range out of range");
        }

        std::size_t new_size = k - (last - first);

        Mtx *new_mtxs = nullptr;

        if (new_size > 0)
        {
            new_mtxs = new Mtx[new_size];

            for (std::size_t i = 0; i < first; i++)
            {
                new_mtxs[i] = mtxs[i];
            }

            for (std::size_t i = last; i < k; i++)
            {
                new_mtxs[first + i - last] = mtxs[i];
            }
        }

        delete[] mtxs;

        mtxs = new_mtxs;
        k = new_size;
    }


    Mtx &operator[](std::size_t index)
    {
        if (index >= k)
        {
            throw std::out_of_range("Index out of range");
        }

        return mtxs[index];
    }

    const Mtx &operator[](std::size_t index) const
    {
        if (index >= k)
        {
            throw std::out_of_range("Index out of range");
        }

        return mtxs[index];
    }


    Mtxs operator+(const Mtxs &other) const
    {
        Mtxs result;

        for (std::size_t i = 0; i < k; i++)
        {
            result.insert(mtxs[i]);
        }

        for (std::size_t i = 0; i < other.k; i++)
        {
            result.insert(other.mtxs[i]);
        }

        return result;
    }

    std::size_t size() const
    {
        return k;
    }

    bool empty() const
    {
        return k == 0;
    }

    Mtx conv(Mtx accumulator, Mtx (*t)(Mtx, Mtx)) const
    {
        for (std::size_t i = 0; i < k; i++)
        {
            accumulator = t(accumulator, mtxs[i]);
        }

        return accumulator;
    }

    void print() const
    {
        for (std::size_t i = 0; i < k; i++)
        {
            std::cout << "Matrix " << i << ":\n";
            mtxs[i].print();
            std::cout << "\n";
        }
    }
};


Mtx addMatrices(Mtx a, Mtx b)
{
    return a + b;
}


int main()
{
    Mtx a(2, 2);
    Mtx b(2, 2);

    a.get(0, 0) = 1;
    a.get(0, 1) = 2;
    a.get(1, 0) = 3;
    a.get(1, 1) = 4;

    b.get(0, 0) = 5;
    b.get(0, 1) = 6;
    b.get(1, 0) = 7;
    b.get(1, 1) = 8;


    Mtxs arr;

    arr.insert(a);
    arr.insert(b);

    std::cout << "Initial array:\n";
    arr.print();


    std::cout << "First matrix:\n";
    arr[0].print();


    Mtxs arr2;

    arr2.insert(a);


    Mtxs arr3 = arr + arr2;

    std::cout << "Sum of arrays:\n";
    arr3.print();


    Mtx result = arr.conv(a, addMatrices);

    std::cout << "Conv result:\n";
    result.print();


    arr3.erase(1);

    std::cout << "After erase:\n";
    arr3.print();

    std::cout << "Size: " << arr3.size() << "\n";
    std::cout << "Empty: " << arr3.empty() << "\n";

    return 0;
}
