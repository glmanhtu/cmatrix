/***************************************************************
*  Copyright (C) 2013 Quan Wang <wangq10@rpi.edu>
*  Signal Analysis and Machine Perception Laboratory
*  Department of Electrical, Computer, and Systems Engineering
*  Rensselaer Polytechnic Institute, Troy, NY 12180, USA
*
*  Related publication:
*  Quan Wang, Kim L. Boyer.
*  Feature Learning by Multidimensional Scaling and its Applications in Object Recognition.
*  2013 26th SIBGRAPI Conference on Graphics, Patterns and Images (Sibgrapi). IEEE, 2013.
***************************************************************/

#ifndef SIMPLE_MATRIX_H
#define SIMPLE_MATRIX_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>

#define MAX_LINE_LENGTH 100000
#define EPSILON 0.0000001
namespace smat
{

/**********************************************
  * Declaration part
  **********************************************/

template <class T>
class Matrix
{
public:
  Matrix(int rows, int columns);                   // initialization without assigning values
  Matrix(int rows, int columns, T value);          // initialization with all same values
  Matrix(int rows, int columns, std::string type); // special matrix such as I
  Matrix(const char *filename);                    // load matrix from txt file
  ~Matrix();                                       // destruction

  void set(int r, int c, T value); // row, column, value
  T get(int r, int c);             // row, column
  int rows();                      // number of rows
  int columns();                   // number of columns

  void print();   // print the matrix
  Matrix *copy(); // copy itself to a new matrix

  void saveTxt(const char *filename); // save matrix to txt file

  // B=M'
  Matrix *transpose();
  // B=M(r1:r2,c1:c2)
  Matrix *sub(int r1, int r2, int c1, int c2); // submatrix
  // B=|M|
  Matrix *abs(); // absolute values

  // numbers of matrix
  T trace();               // trace
  double fnorm();          // Frobenius norm
  double pnorm(double p);  // p-norm
  T maxEl(int &r, int &c); // max element
  T minEl(int &r, int &c); // min element
  double mean();           // mean of elements
  T sum();                 // sum of elements
  double std();            // standard deviation of elements

  // M=M+a
  void addNumberSelf(T value); // add a number to itself in space
  // M=M*a
  void multiplyNumberSelf(T value); // add a number to itself in space

  // M=M+A
  void addMatrixSelf(Matrix *A); // add a matrix to itself in space
  // M=M.*A
  void dotMultiplyMatrixSelf(Matrix *A); // dot multiply a matrix to itself in space

  // B=M+A
  Matrix *addMatrixNew(Matrix *A); // add a matrix to itself with new matrix
  // B=M.*A
  Matrix *dotMultiplyMatrixNew(Matrix *A); // dot multiply a matrix to itself with new matrix
  // B=M*A
  Matrix *multiplyMatrixNew(Matrix *A); // multiply a matrix to itself with new matrix

private:
  int rows_;
  int columns_;
  T **v;
};

/**********************************************
  * Utilities part
  **********************************************/

template <class T>
T min(T v1, T v2)
{
  if (v1 < v2)
    return v1;
  else
    return v2;
}

template <class T>
T max(T v1, T v2)
{
  if (v1 > v2)
    return v1;
  else
    return v2;
}

template <class T>
void swap(T &v1, T &v2)
{
  T v3 = v1;
  v1 = v2;
  v2 = v3;
}

template <class T>
double sign(T v)
{
  if (v > 0)
    return 1.0;
  else if (v < 0)
    return -1.0;
  else
    return 0.0;
}


} // namespace smat

void EuclideanDistanceMatrix(smat::Matrix<double> *X, smat::Matrix<double> *D);
void ElementCopy(smat::Matrix<double> *X, smat::Matrix<double> *Y);
smat::Matrix<double> *MDS_SMACOF(smat::Matrix<double> *D, smat::Matrix<double> *X0, int dim, int iter);
#endif
