///\file generare.c
///\brief C library implementation to generate sparse matrices
///\brief The program implements functions to generate a sparse matrix,to write a matrix,
///\brief to allocate a matrix and a final function which includes all of the previous functions
///\brief and is used in the main program.
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
int generate_number(int x)
{
    ///\fn int generate_number(int x)
    ///\brief Function used to generate a random number between 0 and x
    ///\brief ,using rand() function
    return rand()%x;
}
void generate_matrix(int **mat,int m,int n)
{
    ///\fn void generate_matrix(int **mat,int m,int n)
    ///\brief Function used to create a sparse matrix by generating a small number of nenull elements and their positions in the matrix
    int elements_number,element,Line,Column;
     elements_number=(float)0.4*(m*n);

    while(elements_number!=0)
    {
        element=generate_number(10)+1;
        Line=generate_number(m);
        Column=generate_number(n);
        mat[Line][Column]=element;
        elements_number--;
    }

}
void write_matrix(int **mat,int m,int n,FILE *f)
{
    ///\fn void write_matrix(int **mat,int m,int n,FILE *f)
    ///\brief Function used to write a matrix in the file specified by the file pointer parameter
    ///\param **mat Double pointer used to store the elements of matrix
    ///\param m,n Dimensions of matrix
    ///\param *f File pointer used to write at the position described
    int i,j;
    for(i=0; i<m ; i++)
    {
        for(j=0; j<n; j++)
            fprintf(f,"%d ",mat[i][j]);
        fprintf(f,"\n");
    }
    fprintf(f,"\n");

}
void allocate(int ***mat,int m,int n)
{
    ///\fn void allocate(int ***mat,int m,int n)
    ///\brief Function used to allocate a matrix unsing double pointer transmitted by reference
    ///\brief It is used the calloc function to initialize simultaneously elements with null elements
    int i;
    *mat = calloc(m, sizeof(int *));
    for(i = 0; i < m; i++)
     (*mat)[i] = calloc(n, sizeof(int));
}
void generate_input(int choice)
{
    ///\fn void generate_input(int choice)
    ///\brief Function that uses the above functions to provide the input, such that the conditions for summ or
    ///\brief product of matrices will be satisfied in equal measure, also for the fail case, when the dimensions are
    ///\brief entirely random generated.
    ///\param choice Parameter used to generate matrices that satisfies the conditions for matrices summ or product or
    ///it generates completely random matrices used for one of the operations.

    FILE *f;
    f=fopen("input.txt","w");

    int m,n,p,q,**mat1=NULL,**mat2=NULL;
    if(choice==1)
     {
         m=rand()%5+1;
         n=rand()%5+1;

         fprintf(f,"%d ",m);
         fprintf(f,"%d\n",n);
         allocate(&mat1,m,n);
         generate_matrix(mat1,m,n);
         write_matrix(mat1,m,n,f);

         fprintf(f,"%d ",m);
        fprintf(f,"%d\n",n);
        allocate(&mat2,m,n);
        generate_matrix(mat2,m,n);
        write_matrix(mat2,m,n,f);
     }
     else
        if(choice==2)
     {
         m=rand()%5+1;
         n=rand()%5+1;
         p=rand()%5+1;

        fprintf(f,"%d ",m);
        fprintf(f,"%d\n",n);
        allocate(&mat1,m,n);
        generate_matrix(mat1,m,n);
        write_matrix(mat1,m,n,f);


        fprintf(f,"%d ",n);
        fprintf(f,"%d\n",p);
        allocate(&mat2,n,p);
        generate_matrix(mat2,n,p);
        write_matrix(mat2,n,p,f);
     }
     else
     {
         m=rand()%5+1;
         n=rand()%5+1;
         p=rand()%5+1;
         q=rand()%5+1;

        fprintf(f,"%d ",m);
        fprintf(f,"%d\n",n);
        allocate(&mat1,m,n);
        generate_matrix(mat1,m,n);
        write_matrix(mat1,m,n,f);

        fprintf(f,"%d ",p);
        fprintf(f,"%d\n",q);
        allocate(&mat2,p,q);
        generate_matrix(mat2,p,q);
        write_matrix(mat2,p,q,f);
     }


      fclose(f);
}
