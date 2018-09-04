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
