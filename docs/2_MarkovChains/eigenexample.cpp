#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;
int main()
{
   //
   // Creating matrices
   //
   // A matrix of variable size with double entries.
   MatrixXd M1(4,4);
   M1.setZero();
   MatrixXd M2 = MatrixXd::Zero(2,2);
   MatrixXd M3 = MatrixXd::Random(2,3);
   MatrixXd M4 = MatrixXd::Constant(3,3,1.2);

   //
   // We put some entries in the matrices
   //
   M2 << 1,2,3,4;
   M1 << M2, M2*M2, 10*M2, 2*M2;
   M2.row(1) << 0, 0;
   M2.col(0) << 10, 10;
   M1.topLeftCorner(2,2).setZero();
   M1.bottomRightCorner(2,2).setIdentity();
   M3(1,1) = 10.0;
   M3(3) = 11.0;
   M1.block<2,2>(1,1) << 1,2,3,4;
   M1.block(1,1,2,2) << 1,2,3,4;
   M1.topRows(1) << 1,2,3,4;  //indicate 1st row
   M1.leftCols(2) << 1,2,3,4,5,6,7,8; //2 leftmost columns





  //
  // Matrix operations
  //
  M1 = MatrixXd::Random(2,2);
  M2 = MatrixXd::Random(2,3);
  M3 = MatrixXd::Random(2,2);
  cout << M1 * M2 << endl << endl << M1+M3 << endl << endl << M1*2+2*M3 << endl << endl;
  //cout << M2 * M1; FAILS!!

  // transpose()
  // inverse()
  cout << M1.inverse() << endl << endl;


  //
  // Solving a linear algebra problem
  //
  Matrix2f A;
  Vector2f b;
  A << 2, -1, -1, 3;
  b << 1, 2;
  Vector2f x = A.colPivHouseholderQr().solve(b);
  cout << "The solution is:\n" << x << endl;


 int i;
  std::cin >> i;




}
