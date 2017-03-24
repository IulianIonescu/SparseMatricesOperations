#ifndef MAKEFILES_FUNCTIONS_H
#define MAKEFILES_FUNCTIONS_H
#include<stdio.h>
#include<time.h>/* for using function time (get current time) and macro constant NULL.*/
///\file functions.h
///\brief C library for sparse matrices operations and sparse matrices generation

typedef struct Sparse
{


      int *Line, *Column, *Value; ///< 3 pointers used to store the nenull elements and their positions on matrix


      int nrElements, nrLines, nrColumns; ///<3 variables used to store the number of nenull elements,the number of lines and columns from the normal matrix

} *SparseMatrix;///<The alias used to declare variable of Sparse type
int main();
void freeEverything(SparseMatrix rare);
SparseMatrix SparseMatrix_Conversion(int **mat, int m, int n);
SparseMatrix SparseMatrix_Addition(SparseMatrix *M1,SparseMatrix *M2);
SparseMatrix SparseMatrix_Product(SparseMatrix *M1, SparseMatrix *M2);
void print_matrix(int **matrice,int m,int n,FILE *g);
void print_sparse_matrix(SparseMatrix sparse,FILE *g);
void allocate_and_read(int ***matrice1,int ***matrice2,int *m,int *n,int *p,int *q);
int ** Sparse_to_Normal(SparseMatrix *matR);
int ERROR(SparseMatrix R);
void resolve(int **NormalMat1,int **NormalMat2,int m,int n,int p,int q,int choice);

void generate_input(int choice);
int generate_number(int x);
void generate_matrix(int **mat,int m,int n);
void write_matrix(int **mat,int m,int n,FILE *f);
void allocate(int ***mat,int m,int n);
#endif
