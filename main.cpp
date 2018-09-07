#include <cassert>
#include <iostream>
#include <exception>
#include "matrix.h"
#include "my_traits.h"

int main(int argc, char const *argv[])
{
    try
    {
        Matrix<int, 0> matrix;
       
        for (auto i{0}; i < 10; ++i)
        {
            matrix[i][i] = i;
            matrix[i][9 - i] = 9 - i;
        }

        for (auto i{1}; i < 9; ++i)
        {
            for (auto j{1}; j < 9; ++j)
            {
                if (j != 1)
                    std::cout << ' ';
                std::cout << matrix[i][j];
            }
            std::cout << std::endl;
        }

        std::cout << matrix.size() << std::endl;

        for (auto &item : matrix)
        {
            std::size_t x;
            std::size_t y;
            int v;
            std::tie(x, y, v) = item;
            std::cout << x << y << v << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
