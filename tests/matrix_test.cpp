#include "gmock/gmock.h"
#include "matrix.h"
using namespace testing;

TEST(Matrix_Test_case, Matrix_Test)
{

    Matrix<int, -1, 1> matrix1;
    ASSERT_THAT(matrix1.size(), 0); // все ячейки свободны
    auto a1 = matrix1[0];
    ASSERT_THAT(a1, -1);
    ASSERT_THAT(matrix1.size(), 0);
    matrix1[100] = 314;
    ASSERT_THAT(matrix1[100], 314);
    ASSERT_THAT(matrix1.size(), 1);
    std::string output{};
    // выведется одна строка
    // 100314
    for (auto c : matrix1)
    {
        int x;
        int v;
        std::tie(x, v) = c;
        internal::CaptureStdout();
        std::cout << x << v << std::endl;
        output = internal::GetCapturedStdout();
        ASSERT_THAT(output, "100314\n");
    }

    Matrix<int, -1> matrix2;            // бесконечная матрица int заполнена значениями -1
    ASSERT_THAT(matrix2.size(), Eq(0)); // все ячейки свободны
    auto a = matrix2[0][0];
    ASSERT_THAT(a, -1);
    ASSERT_THAT(matrix2.size(), 0);
    matrix2[100][100] = 314;
    ASSERT_THAT(matrix2[100][100], 314);
    ASSERT_THAT(matrix2.size(), 1);
    ((matrix2[100][100] = 314) = 0) = 217;
    ASSERT_THAT(matrix2[100][100], 217);
    // выведется одна строка
    // 100100217
    for (auto c : matrix2)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        internal::CaptureStdout();
        std::cout << x << y << v << std::endl;
        output = internal::GetCapturedStdout();
        ASSERT_THAT(output, "100100217\n");
    }
}

TEST(Matrix_Test_case, Copy_Matrix_Test)
{
    Matrix<int, 0> matrix;
    Matrix<int, 0> matrix1;
    std::string output{};
    std::string result{};
    ASSERT_THAT(matrix.size(), 0);
    ASSERT_THAT(matrix1.size(), 0);
    for (auto i{0}; i < 10; ++i)
    {
        matrix[i][i] = i;
        matrix[i][9 - i] = 9 - i;
    }
    testing::internal::CaptureStdout();
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
    output = testing::internal::GetCapturedStdout();
    result = {
        "1 0 0 0 0 0 0 8\n"
        "0 2 0 0 0 0 7 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 2 0 0 0 0 7 0\n"
        "1 0 0 0 0 0 0 8\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix.size(), 18);
    matrix1 = matrix;

    testing::internal::CaptureStdout();
    for (auto i{1}; i < 9; ++i)
    {
        for (auto j{1}; j < 9; ++j)
        {
            if (j != 1)
                std::cout << ' ';
            std::cout << matrix1[i][j];
        }
        std::cout << std::endl;
    }
    output = testing::internal::GetCapturedStdout();
    result = {
        "1 0 0 0 0 0 0 8\n"
        "0 2 0 0 0 0 7 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 2 0 0 0 0 7 0\n"
        "1 0 0 0 0 0 0 8\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix1.size(), 18);
    for (auto i{0}; i < 10; ++i)
    {
        matrix[i][i] = 2 * i;
        matrix[i][9 - i] = 2 * (9 - i);
    }
    testing::internal::CaptureStdout();
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
    output = testing::internal::GetCapturedStdout();
    result = {
        "2 0 0 0 0 0 0 16\n"
        "0 4 0 0 0 0 14 0\n"
        "0 0 6 0 0 12 0 0\n"
        "0 0 0 8 10 0 0 0\n"
        "0 0 0 8 10 0 0 0\n"
        "0 0 6 0 0 12 0 0\n"
        "0 4 0 0 0 0 14 0\n"
        "2 0 0 0 0 0 0 16\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix.size(), 18);
    testing::internal::CaptureStdout();
    for (auto i{1}; i < 9; ++i)
    {
        for (auto j{1}; j < 9; ++j)
        {
            if (j != 1)
                std::cout << ' ';
            std::cout << matrix1[i][j];
        }
        std::cout << std::endl;
    }
    output = testing::internal::GetCapturedStdout();
    result = {
        "1 0 0 0 0 0 0 8\n"
        "0 2 0 0 0 0 7 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 2 0 0 0 0 7 0\n"
        "1 0 0 0 0 0 0 8\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix1.size(), 18);
}

TEST(Matrix_Test_case, Copy_Constructor_Matrix_Test)
{
    Matrix<int, 0> matrix;
    std::string output{};
    std::string result{};
    ASSERT_THAT(matrix.size(), 0);
    for (auto i{0}; i < 10; ++i)
    {
        matrix[i][i] = i;
        matrix[i][9 - i] = 9 - i;
    }
    testing::internal::CaptureStdout();
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
    output = testing::internal::GetCapturedStdout();
    result = {
        "1 0 0 0 0 0 0 8\n"
        "0 2 0 0 0 0 7 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 2 0 0 0 0 7 0\n"
        "1 0 0 0 0 0 0 8\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix.size(), 18);
    auto matrix1 = matrix;
    testing::internal::CaptureStdout();
    for (auto i{1}; i < 9; ++i)
    {
        for (auto j{1}; j < 9; ++j)
        {
            if (j != 1)
                std::cout << ' ';
            std::cout << matrix1[i][j];
        }
        std::cout << std::endl;
    }
    output = testing::internal::GetCapturedStdout();
    result = {
        "1 0 0 0 0 0 0 8\n"
        "0 2 0 0 0 0 7 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 2 0 0 0 0 7 0\n"
        "1 0 0 0 0 0 0 8\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix1.size(), 18);
    for (auto i{0}; i < 10; ++i)
    {
        matrix[i][i] = 2 * i;
        matrix[i][9 - i] = 2 * (9 - i);
    }
    testing::internal::CaptureStdout();
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
    output = testing::internal::GetCapturedStdout();
    result = {
        "2 0 0 0 0 0 0 16\n"
        "0 4 0 0 0 0 14 0\n"
        "0 0 6 0 0 12 0 0\n"
        "0 0 0 8 10 0 0 0\n"
        "0 0 0 8 10 0 0 0\n"
        "0 0 6 0 0 12 0 0\n"
        "0 4 0 0 0 0 14 0\n"
        "2 0 0 0 0 0 0 16\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix.size(), 18);
    testing::internal::CaptureStdout();
    for (auto i{1}; i < 9; ++i)
    {
        for (auto j{1}; j < 9; ++j)
        {
            if (j != 1)
                std::cout << ' ';
            std::cout << matrix1[i][j];
        }
        std::cout << std::endl;
    }
    output = testing::internal::GetCapturedStdout();
    result = {
        "1 0 0 0 0 0 0 8\n"
        "0 2 0 0 0 0 7 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 2 0 0 0 0 7 0\n"
        "1 0 0 0 0 0 0 8\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix1.size(), 18);
}

TEST(Matrix_Test_case, Move_Constructor_Matrix_Test)
{
    Matrix<int, 0> matrix;
    std::string output{};
    std::string result{};
    ASSERT_THAT(matrix.size(), 0);
    for (auto i{0}; i < 10; ++i)
    {
        matrix[i][i] = i;
        matrix[i][9 - i] = 9 - i;
    }
    testing::internal::CaptureStdout();
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
    output = testing::internal::GetCapturedStdout();
    result = {
        "1 0 0 0 0 0 0 8\n"
        "0 2 0 0 0 0 7 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 2 0 0 0 0 7 0\n"
        "1 0 0 0 0 0 0 8\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix.size(), 18);
    auto matrix1(std::move(matrix));
    testing::internal::CaptureStdout();
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
    output = testing::internal::GetCapturedStdout();
    result = {
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix.size(), 0);
    testing::internal::CaptureStdout();
    for (auto i{1}; i < 9; ++i)
    {
        for (auto j{1}; j < 9; ++j)
        {
            if (j != 1)
                std::cout << ' ';
            std::cout << matrix1[i][j];
        }
        std::cout << std::endl;
    }
    output = testing::internal::GetCapturedStdout();
    result = {
        "1 0 0 0 0 0 0 8\n"
        "0 2 0 0 0 0 7 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 2 0 0 0 0 7 0\n"
        "1 0 0 0 0 0 0 8\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix1.size(), 18);
}

TEST(Matrix_Test_case, Move_Operator_Matrix_Test)
{
    Matrix<int, 0> matrix;
    std::string output{};
    std::string result{};
    ASSERT_THAT(matrix.size(), 0);
    for (auto i{0}; i < 10; ++i)
    {
        matrix[i][i] = i;
        matrix[i][9 - i] = 9 - i;
    }
    testing::internal::CaptureStdout();
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
    output = testing::internal::GetCapturedStdout();
    result = {
        "1 0 0 0 0 0 0 8\n"
        "0 2 0 0 0 0 7 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 2 0 0 0 0 7 0\n"
        "1 0 0 0 0 0 0 8\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix.size(), 18);
    Matrix<int, 0> matrix1;
    ASSERT_THAT(matrix1.size(), 0);
    for (auto i{0}; i < 10; ++i)
    {
        matrix1[i][i] = 2 * i;
        matrix1[i][9 - i] = 2 * (9 - i);
    }
    testing::internal::CaptureStdout();
    for (auto i{1}; i < 9; ++i)
    {
        for (auto j{1}; j < 9; ++j)
        {
            if (j != 1)
                std::cout << ' ';
            std::cout << matrix1[i][j];
        }
        std::cout << std::endl;
    }
    output = testing::internal::GetCapturedStdout();
    result = {
        "2 0 0 0 0 0 0 16\n"
        "0 4 0 0 0 0 14 0\n"
        "0 0 6 0 0 12 0 0\n"
        "0 0 0 8 10 0 0 0\n"
        "0 0 0 8 10 0 0 0\n"
        "0 0 6 0 0 12 0 0\n"
        "0 4 0 0 0 0 14 0\n"
        "2 0 0 0 0 0 0 16\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix1.size(), 18);
    matrix1 = std::move(matrix);
    testing::internal::CaptureStdout();
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
    output = testing::internal::GetCapturedStdout();
    result = {
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix.size(), 0);
    testing::internal::CaptureStdout();
    for (auto i{1}; i < 9; ++i)
    {
        for (auto j{1}; j < 9; ++j)
        {
            if (j != 1)
                std::cout << ' ';
            std::cout << matrix1[i][j];
        }
        std::cout << std::endl;
    }
    output = testing::internal::GetCapturedStdout();
    result = {
        "1 0 0 0 0 0 0 8\n"
        "0 2 0 0 0 0 7 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 0 4 5 0 0 0\n"
        "0 0 3 0 0 6 0 0\n"
        "0 2 0 0 0 0 7 0\n"
        "1 0 0 0 0 0 0 8\n"};
    ASSERT_THAT(output, result);
    ASSERT_THAT(matrix1.size(), 18);
}