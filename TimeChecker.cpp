


#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <stack>
#include <chrono>

#include "Matrix.hpp"

#define SIZE_MESSAGE "size "
#define EIGEN_MULT_MESSAGE "eigen mult "
#define EIGEN_ADD_MESSAGE "eigen add "
#define MATLIB_ADD_MESSAGE "matlib add "
#define MATLIB_MULT_MESSAGE "matlib mult "


using Eigen::MatrixXd;
using std::cout;
using std::endl;


/**
 * stack to push times
 */
std::stack<std::chrono::time_point<std::chrono::system_clock>> tictoc_stack;

/**
 * insert current time into stack
 */
void tic()
{
    tictoc_stack.push(std::chrono::system_clock::now());
}

/**
 * get delta from last time
 * @return delta from last time
 */
double toc()
{

    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    tictoc_stack.pop();
    return elapsed_seconds.count();
}

/**
 * main function on file, calcs times to perform operations on matrices
 * @param n size of matrices
 * @return 0 if successes.
 */
int main(int n)
{


    cout << SIZE_MESSAGE << n << endl;

    MatrixXd m1 = MatrixXd::Random(n, n);
    MatrixXd m2 = MatrixXd::Random(n, n);

    MatrixXd m3;

    tic();
    m1 * m2;
    cout << EIGEN_MULT_MESSAGE << toc() << endl;

    tic();
    m1 + m2;
    cout << EIGEN_ADD_MESSAGE << toc() << endl;

    vector<int> onesVector((unsigned long) (n * n), 1);
    Matrix<int> onesMatrix(n, n, onesVector);


    tic();
    onesMatrix * onesMatrix;
    cout << MATLIB_MULT_MESSAGE << toc() << endl;

    tic();
    onesMatrix + onesMatrix;
    cout << MATLIB_ADD_MESSAGE << toc() << endl;

    return 0;
}
