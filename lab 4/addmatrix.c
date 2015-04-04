#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,rows,columns;
    printf("Enter size of the matrices:\t");
    scanf("%d%d",&rows,&columns);
    int matrix1[rows][columns],matrix2[rows][columns],result[rows][columns];
    
    printf("\nEnter elements of matrix 1:\n");
    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
        {
            printf("Enter element m%d%d: ",i+1,j+1);
            scanf("%d",&matrix1[i][j]);
            
        }
    }
    printf("\nEnter elements of matrix 2:\n");
    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
        {
            printf("Enter element n%d%d: ",i+1,j+1);
            scanf("%d",&matrix2[i][j]);
            
        }
    }
    printf("\nmatrix 1:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf("%d\t", matrix1[i][j]);
        }
        printf("\n");
    }
    printf("\nmatrix 2:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf("%d\t", matrix2[i][j]);
        }
        printf("\n");
    }
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    printf("\nSum: \n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf("%d\t", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}
