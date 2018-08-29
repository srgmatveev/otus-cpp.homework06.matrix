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
/*
    Matrix<int, -1, 1> matrix1;
    assert(matrix1.size() == 0); // все ячейки свободны
    auto a1 = matrix1[0];
    assert(a1 == -1);
    assert(matrix1.size() == 0);
    matrix1[100] = 314;
    assert(matrix1[100] == 314);
    assert(matrix1.size() == 1);
    // выведется одна строка
    // 100314
    for (auto c : matrix1)
    {
        int x;
        int v;
        std::tie(x, v) = c;
        std::cout << x << v << std::endl;
    }

    Matrix<int, -1> matrix2;     // бесконечная матрица int заполнена значениями -1
    assert(matrix2.size() == 0); // все ячейки свободны
    auto a = matrix2[0][0];
    assert(a == -1);
    assert(matrix2.size() == 0);
    matrix2[100][100] = 314;
    assert(matrix2[100][100] == 314);
    assert(matrix2.size() == 1);
    ((matrix2[100][100] = 314) = 0) = 217;

    // выведется одна строка
    // 100100314
    for (auto c : matrix2)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
*/
    return 0;
}
