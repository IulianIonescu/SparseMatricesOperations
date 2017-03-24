/// \file main.c
/// \brief Libraries 7. : A library for operations with sparse matrices
///
///Created by Ionescu Iulian
#include<stdlib.h>
#include<stdio.h>
#include <time.h>

#include "functions.h"

#define number_of_testes 5///<The number of operations we will make on matrices.

int main()
{
    ///\fn int main()
    ///\brief Main function : generate matrices, allocate space for matrices, resolve operations with matrices.
    ///\brief Functions calls of generate_input,allocate_and_read and resolve are imported from functions.h header file
    int **NormalMat1=NULL,**NormalMat2=NULL;///<Two double pointers to store the matrices
    int m,n,p,q;///<The number of lines and columns from the matrices
    int i;
    int choice;


    FILE *g;

    g=fopen("output.txt","w");
    srand(time(NULL));
    for(i=0;i<number_of_testes;i++)

    {
        choice=rand()%3+1;
        generate_input(choice);
        allocate_and_read(&NormalMat1,&NormalMat2,&m,&n,&p,&q);
        resolve(NormalMat1,NormalMat2,m,n,p,q,choice);
    }
   fclose(g);
    return 0;
}
