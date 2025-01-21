#include <stdio.h>

int main()
{
    int n;
    printf("Enter the rows of the matrix:");
    scanf("%d", &n);

    int m;
    printf("Enter the columns of the matrix:");
    scanf("%d", &m);
    int mat[n][m];

   for(int i=0; i<n; i++) for(int j=0; j<m; j++) scanf("%d", &mat[i][j]);

    int row = (n%2==0) ? n/2 : n/2 + 1;
    int col = (m%2==0) ? m/2 : m/2 + 1;
    
    int new[row][col];

    for (int i=0 ; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            if (n%2==0 && m%2==0) new[i][j] = mat[i][j]*mat[i][m-j-1]*mat[n-i-1][j]*mat[n-i-1][m-j-1];

            else if (n%2!=0 && m%2!=0)
            {
                if (i==row-1 && j!=col-1) new[i][j] = mat[i][j]*mat[i][m-j-1];
                else if (i<=row-1 && j==col-1) new[i][j] = mat[i][j];
                else new[i][j] = mat[i][j]*mat[i][m-j-1]*mat[n-i-1][j]*mat[n-i-1][m-j-1];  
            }

            else if (n%2==0 && m%2!=0)
            {
                if (i<=row-1 && j==col-1) new[i][j] = mat[i][j]*mat[n-i-1][m-j-1];
                else new[i][j] = mat[i][j]*mat[i][m-j-1]*mat[n-i-1][j]*mat[n-i-1][m-j-1];  
            }

            else
            {
                if (i==row-1 && j!=col-1) new[i][j] = mat[i][j]*mat[i][m-j-1];
                else new[i][j] = mat[i][j]*mat[i][m-j-1]*mat[n-i-1][j]*mat[n-i-1][m-j-1];  
            }
        }
    }

    for (int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            printf("%d ", new[i][j]);
        }
        printf("\n");
    }

    return 0;
}

