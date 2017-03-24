///\file functions.c
///\brief C library implementation for sparse matrix operations.
///\brief Implements the summ and the product of two sparse matrices,
///\brief  the conversions between a normal matrix and a sparse one
/// \brief and the printing of the matrices in both formes.
#include<stdlib.h>
#include<stdio.h>

#include "functions.h"


void freeEverything(SparseMatrix sparse)
{
    ///\fn void freeEverything(SparseMatrix sparse)
    ///\brief Deallocate memory used for structure variable and the structure fields
    free(sparse->Line);
    free(sparse->Column);
    free(sparse->Value);
    free(sparse);
}

SparseMatrix SparseMatrix_Conversion(int **mat, int m, int n)
{
       ///\fn SparseMatrix SparseMatrix_Conversion(int **mat,int m,int n)
       ///\brief Computes the conversion of a matrix to a form where only the nenull elements
       ///\brief are stored with their positions, using a structure . It returns the resulted structure.
       ///\param **mat Double pointer which stores the elements of matrix
       ///\param m ,n The number of lines and columns of matrix
       struct Sparse *matR;///<A Sparse type variable
       ///Allocate memory for structure
       matR = (struct Sparse *)malloc(sizeof(struct Sparse));

       int i, j, nrElements = 0, MatRIndex = 0;
       for (i = 0; i < m; i++)
              for (j = 0; j < n; j++)
                     if (mat[i][j] != 0)
                           nrElements++;

       matR->Line=(int *) malloc(nrElements*sizeof(int));
       matR->Column=(int *) malloc(nrElements*sizeof(int));
       matR->Value=(int *) malloc(nrElements*sizeof(int));

       matR->nrElements = nrElements;
       matR->nrLines = m;
       matR->nrColumns = n;

       for (i = 0; i < m; i++)
              for (j = 0; j < n; j++)
                     if (mat[i][j] != 0)
                     {
                           matR->Line[MatRIndex] = i;
                           matR->Column[MatRIndex] = j;
                           matR->Value[MatRIndex] = mat[i][j];

                           MatRIndex++;
                     }
        return matR;

        freeEverything(matR);

}
SparseMatrix SparseMatrix_Addition(SparseMatrix *M1,SparseMatrix *M2)
{
    ///\fn SparseMatrix SparseMatrix_Addition(SparseMatrix *M1,SparseMatrix *M2)
    ///\brief Computes the addition of two sparse matrices. It returns the resulted matrix as a structure/
    ///\param *M1,*M2 Two matrices stored in structure used for addition
    struct Sparse *R;
    /
       R = (struct Sparse *)malloc(sizeof(struct Sparse));
 int i = 0, j = 0, nr = 0, k ;

      R->Line=NULL;
      R->Column=NULL;
      R->Value=NULL;
      R->nrColumns=0;
      R->nrElements=0;
      R->nrLines=0;

       if (((*M1)->nrLines == (*M2)->nrLines) && ((*M1)->nrColumns == (*M2)->nrColumns))
       {


       while (i < (*M1)->nrElements && j < (*M2)->nrElements)
       {
              if ((*M1)->Line[i] < (*M2)->Line[j])
                     i++;
              else
                  if ((*M1)->Line[i] > (*M2)->Line[j])
                     j++;
              else
              {
                     if ((*M1)->Column[i] < (*M2)->Column[j])
                           i++;
                     else if ((*M1)->Column[i] > (*M2)->Column[j])
                           j++;
                     else
                     {
                           if ((*M1)->Value[i] + (*M2)->Value[j] == 0)
                                  {
                                      nr = nr + 2;
                                  }
                           else
                                  {
                                      nr = nr + 1;
                                  }

                           i++; j++;
                     }
              }
       }


       nr = (*M1)->nrElements + (*M2)->nrElements - nr  ;


       R->Line = (int *) malloc(nr*sizeof(int));
       R->Column = (int *) malloc(nr*sizeof(int));
       R->Value = (int *) malloc(nr*sizeof(int));
       R->nrElements = nr;
       R->nrLines = (*M1)->nrLines;
       R->nrColumns = (*M1)->nrColumns;


       i = 0; j = 0; k=0;
       while (k < R->nrElements)
       {
               if ((*M1)->Line[i] < (*M2)->Line[j])
              {
                     R->Line[k] = (*M1)->Line[i];
                     R->Column[k] = (*M1)->Column[i];
                     R->Value[k] = (*M1)->Value[i];
                     i++; k++;
              }
              else if ((*M1)->Line[i] > (*M2)->Line[j])
              {
                     R->Line[k] = (*M2)->Line[j];
                     R->Column[k] = (*M2)->Column[j];
                     R->Value[k] = (*M2)->Value[j];
                     j++; k++;
              }
              else
              {
                     if ((*M1)->Column[i] < (*M2)->Column[j])
                     {
                           R->Line[k] = (*M1)->Line[i];
                           R->Column[k] = (*M1)->Column[i];
                           R->Value[k] = (*M1)->Value[i];
                           i++; k++;
                     }
                     else if ((*M1)->Column[i] > (*M2)->Column[j])
                     {
                           R->Line[k] = (*M2)->Line[j];
                           R->Column[k] = (*M2)->Column[j];
                           R->Value[k] = (*M2)->Value[j];
                           j++; k++;
                     }
                     else
                     {
                           if ((*M1)->Value[i] + (*M2)->Value[j] == 0)
                           {
                                  i++; j++;     // element comun nul
                           }
                           else
                           {
                                  R->Line[k] = (*M1)->Line[i];;
                                  R->Column[k] = (*M1)->Column[i];
                                  R->Value[k] = (*M1)->Value[i] +(*M2)->Value[j];
                                  i++; j++; k++; // element comun nenul
                           }
                     }
              }
       }

                return R;
       freeEverything(R);

       }
      else
      {

        return R;

      }

}
SparseMatrix SparseMatrix_Product(SparseMatrix *M1, SparseMatrix *M2)
{
    ///\fn SparseMatrix SparseMatrix_Product(SparseMatrix *M1,SparseMatrix *M2)
    ///\brief Computes the product of two sparse matrices stored using the structure. It returns the resulted matrix by a structure.
    ///\param *M1,*M2 Two structures used to store two sparse matrices used for product
    struct Sparse *R;///<A Sparse type varible

       R = (struct Sparse *)malloc(sizeof(struct Sparse));
        int nr = 0, summ,i,j,i1,i2,col,index = 0;

      R->Line=NULL;
      R->Column=NULL;
      R->Value=NULL;
      R->nrColumns=0;
      R->nrElements=0;
      R->nrLines=0;

       if ((*M1)->nrColumns != (*M2)->nrLines)
       {
              return R;
       }
       for ( i = 0; i < (*M1)->nrLines; i++)
              {
                  for ( j = 0; j < (*M2)->nrLines; j++)
              {
                     summ = 0;

                     for ( col = 0; col < (*M1)->nrColumns; col++)
                           for ( i1 = 0; i1 < (*M1)->nrElements; i1++)
                                  if (((*M1)->Line)[i1] == i && ((*M1)->Column)[i1] == col)
                                         {
                                             for ( i2 = 0; i2 < (*M2)->nrElements; i2++)
                                               if (((*M2)->Line)[i2] == col && ((*M2)->Column)[i2] == j)
                                                       {
                                                           summ += ((*M1)->Value)[i1] * ((*M2)->Value)[i2];
                                                       }
                                         }
                     if (summ)
                        {
                            nr++;
                        }
              }
              }


       R->Line = (int *) malloc(nr*sizeof(int));
       R->Column = (int *) malloc(nr*sizeof(int));
       R->Value = (int *) malloc(nr*sizeof(int));
       R->nrElements = nr;
       R->nrLines = (*M1)->nrLines;
       R->nrColumns = (*M2)->nrColumns;

       for ( i = 0; i < (*M1)->nrLines; i++)
              for ( j = 0; j < (*M2)->nrLines; j++)
              {
                     summ = 0;
                     for ( col = 0; col < (*M1)->nrColumns; col++)
                           for ( i1 = 0; i1 < (*M1)->nrElements; i1++)
                                if (((*M1)->Line)[i1] == i && ((*M1)->Column)[i1] == col)
                                           {
                                               for ( i2 = 0; i2 < (*M2)->nrElements; i2++)
                                                    if (((*M2)->Line)[i2] == col && ((*M2)->Column)[i2] == j)
                                                        {
                                                            summ += ((*M1)->Value)[i1] * ((*M2)->Value)[i2];
                                                        }
                                           }
                     if (summ)
                     {
                           R->Line[index] = i;
                           R->Column[index] = j;
                           R->Value[index] = summ;
                           index++;
                     }
              }

        return R;
        freeEverything(R);
}
void print_matrix(int **matrice,int m,int n,FILE *g)
{
    ///\fn void print_matrix(int **matrice,int m,int n,FILE *g)
    ///\brief It prints a matrix in the file specified by *g file pointer
    int i,j;
     for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
            fprintf(g,"%d ",matrice[i][j]);
        fprintf(g,"\n");
    }
}
void print_sparse_matrix(SparseMatrix sparse,FILE *g)
{
    ///\fn void print_sparse_matrix(SparseMatrix sparse,FILE *g)
    ///\brief It prints a sparse matrix ih this form: the line index, the column index and the nenull value
    int i;

    if(sparse->nrElements!=0)
    {
        for(i=0;i<sparse->nrElements;i++)
        fprintf(g,"%d     ",sparse->Line[i]);
     fprintf(g,"\n");
     for(i=0;i<sparse->nrElements;i++)
        fprintf(g,"%d     ",sparse->Column[i]);
     fprintf(g,"\n");
     for(i=0;i<sparse->nrElements;i++)
        fprintf(g,"%d     ",sparse->Value[i]);
    }
    else
    {
        fprintf(g,"       The matrix has only null elements.\n");
    }
}
void allocate_and_read(int ***matrice1,int ***matrice2,int *m,int *n,int *p,int *q)
{
    ///\fn void allocate_and_read(int ***matrice1,int ***matrice2,int *m,int *n,int *p,int *q)
    ///\brief It allocates and reads two matrices.The elements are read from an input file
    int i,j;
    FILE *f;

    f=fopen("input.txt","r+");

    fscanf(f,"%d%d",&(*m),&(*n));
    *matrice1 = malloc((*m)*sizeof(int *));
    for(i = 0; i < (*m); i++)
     (*matrice1)[i] = malloc((*n)*sizeof(int));
    for(i=0;i<(*m);i++)
        for(j=0;j<(*n);j++)
           fscanf(f,"%d",&(*matrice1)[i][j]);

    fscanf(f,"%d%d",&(*p),&(*q));
    *matrice2 = malloc((*p)*sizeof(int *));
    for(i = 0; i < (*p); i++)
     (*matrice2)[i] = malloc((*q)*sizeof(int));
    for(i=0;i<(*p);i++)
        for(j=0;j<(*q);j++)
           fscanf(f,"%d",&(*matrice2)[i][j]);


}
int ** Sparse_to_Normal(SparseMatrix *matR)
{
       ///\fn int ** Sparse_to_Normal(SparseMatrix *matR)
       ///\brief Create a normal matrix from the compressed form.
       ///\param *matR A SparseMatrix type parameter
       int i,j;
       int **mat;
      mat = malloc(((*matR)->nrLines)*sizeof(int *));
       for(i=0; i<((*matR)->nrLines); i++)
          mat[i] = malloc(((*matR)->nrColumns)*sizeof(int *));
       for(i=0;i<((*matR)->nrLines);i++)
            for(j=0;j<((*matR)->nrColumns);j++)
               mat[i][j]=0;

       for ( i = 0; i < ((*matR)->nrElements); i++)
              mat[((*matR)->Line)[i]][((*matR)->Column)[i]] = ((*matR)->Value)[i];

       return mat;
}
int ERROR(SparseMatrix R)
{
    ///\fn int ERROR(SparseMatrix R)
    ///\brief If the fields of structure are not filled, results that the addition or the product
    ///\brief operation failed so the function return true or false


    if (R->Line==NULL && R->Column==NULL && R->Value==NULL && R->nrColumns==0 && R->nrElements==0 && R->nrLines==0)
        return 1;
    else
        return 0;
}
void resolve(int **NormalMat1,int **NormalMat2,int m,int n,int p,int q,int choice)
{
    ///\fn void resolve(int **NormalMat1,int **NormalMat2,int m,int n,int p,int q,int choice)
    ///\brief Function where the above operations are executed and the results are printed in an output file
    ///\param **NormalMat1,**NormalMat2 Two double pointers used for the matrices operations
    ///\param m,n,p,q The number of lines and columns of the matrices
    ///\param choice Parameter which will randomly decide what operation is executed
    int **Summ_Matrix_Normal=NULL,**Product_Matrix_Normal=NULL; ///< Two double pointers used to store the elements of the matrix summ
                                                                ///and matrix product
    int auxiliar;
    FILE *g;
    g=fopen("output.txt","a");
    fprintf(g,"\n\nNEW TEST\n\n");

    SparseMatrix R1,R2;
    SparseMatrix R_summ,R_product;

    R1=SparseMatrix_Conversion(NormalMat1,m,n);
    R2=SparseMatrix_Conversion(NormalMat2,p,q);

    fprintf(g,"Matrix 1:\n");
    print_matrix(NormalMat1,m,n,g);

    fprintf(g,"Matrix 2:\n");
    print_matrix(NormalMat2,p,q,g);

    fprintf(g,"\nPrint as sparse matrix\n");
    fprintf(g,"\nMatrix 1:\n");
    print_sparse_matrix(R1,g);
    fprintf(g,"\nMatrix 2:\n");
    print_sparse_matrix(R2,g);
    auxiliar = rand()%2;

    if(choice==1 || (auxiliar==1 && choice!=2))
    {
        fprintf(g,"\n\nAddition of matrixes\n\n");
        R_summ=SparseMatrix_Addition(&R1,&R2);
        if(ERROR(R_summ)==0)
        {

            Summ_Matrix_Normal=Sparse_to_Normal(&R_summ);
        fprintf(g,"The summ matrix represented as normal matrix\n");
        print_matrix(Summ_Matrix_Normal,R_summ->nrLines,R_summ->nrColumns,g);
        fprintf(g,"The summ matrix represented as sparse matrix\n");
        print_sparse_matrix(R_summ,g);

        }
        else
        {
            fprintf(g,"Error: The matrices doesn't have the same number of lines and columns\n\n");
            fprintf(g,"Matrix1 lines columns: %d %d\n",m,n);
            fprintf(g,"Matrix2 lines columns: %d %d\n",p,q);
        }

    }
    else
        if(choice==2 || auxiliar == 0)
    {
        fprintf(g,"\n\nMultiplication of matrices\n\n");
        R_product=SparseMatrix_Product(&R1,&R2);
        if(ERROR(R_product)==0)
        {
           Product_Matrix_Normal=Sparse_to_Normal(&R_product);
        fprintf(g,"The product matrix represented as normal matrix\n\n");
        print_matrix(Product_Matrix_Normal,R_product->nrLines,R_product->nrColumns,g);
        fprintf(g,"The product matrix represented as sparse matrix\n\n");
        print_sparse_matrix(R_product,g);

        }
        else
        {
            fprintf(g,"Error: The dimensions of matrixes doesn't match\n\n");
            fprintf(g,"Matrix1 lines columns: %d %d\n",m,n);
            fprintf(g,"Matrix2 lines columns: %d %d\n",p,q);
        }
    }

  fclose(g);
}

