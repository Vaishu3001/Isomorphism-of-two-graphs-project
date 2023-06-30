
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_isomorphic = false;
int n, e;
int adj_1[10][2], adj_2[10][2];
int main(int argc, char const **argv);
bool Degree_equal(int arr1[], int arr2[], int n);
int **ini_mat(int mat[e][2],int inimat[n+1][n+1]);
int **generate_adj_permu(int gen_mat[n+1][n+1], int permu[n], int n);
bool check(int mat1[n+1][n+1], int mat2[n+1][n+1], int n);
void call(int num[n], int n, int inimat1[n+1][n+1],int inimat2[n+1][n+1]);
int *reverse(int num[n],int n);
void generatingcombinations_matrices(int inimat1[n+1][n+1],int inimat2[n+1][n+1], int n);

// main function
int main(int argc, char const **argv)
{
    if (argc != 3)
    {
        printf("Invalid input format\n");
        exit(-1);
    }
    // passing text file as read only file by passing file name as commandline argument
    FILE *input1 = fopen(argv[1], "r");
    if (NULL == input1)
    {
        printf("oops, file can't be read\n");
        exit(0);
    }
    FILE *input2 = fopen(argv[2], "r");
    if (NULL == input2)
    {
        printf("oops, file can't be read\n");
        exit(0);
    }
    // checking initial conditions;
    int n1, n2, e1, e2;
    fscanf(input1, "%d", &n1);
    fscanf(input2, "%d", &n2);
    fscanf(input1, "%d", &e1);
    fscanf(input2, "%d", &e2);

    if (n1 != n2 || e1 != e2)
        printf("Graphs not isomorphic");
    else
    {
        n = n1;
        e = e1;

        // initalising the values of the adjacency matrix to 0
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                adj_1[i][j] = 0;
            }
        }
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                adj_2[i][j] = 0;
            }
        }

        // 2 points are adjacent when they have an edge between them
        // storing the value of edges in the adjacency matrix
        int a, b, c, d;
        for (int i = 0; i < e; i++)
        {
            fscanf(input1, "%d", &a);
            fscanf(input1, "%d", &b);
            adj_1[i][0] = a;
            adj_1[i][1] = b;
        }
        for (int i = 0; i < e; i++)
        {
            fscanf(input2, "%d", &c);
            fscanf(input2, "%d", &d);
            adj_2[i][0] = c;
            adj_2[i][1] = d;
        }
        int final1[e][2];
        int final2[e][2];
        for (int i = 0; i < e; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                final1[i][j] = adj_1[i][j];
            }
        }
        for (int i = 0; i < e; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                final2[i][j] = adj_2[i][j];
            }
        }
        // checking and storing degree of each node
        int deg1[n];
        int x1 = 1;
        while (x1 <= n)
        {
            int count = 0;
            for (int i = 0; i < e; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if (adj_1[i][j] == x1)
                    {
                        count++;
                    }
                }
            }
            deg1[x1 - 1] = count;
            x1++;
        }

        int deg2[n];
        int x2 = 1;
        while (x2 <= n)
        {
            int count = 0;
            for (int i = 0; i < e; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if (adj_2[i][j] == x2)
                    {
                        count++;
                    }
                }
            }
            deg2[x2 - 1] = count;
            x2++;
        }
        // sorting the degree array in non decreasing order
        int temp1;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (deg1[i] < deg1[j])
                {
                    temp1 = deg1[i];
                    deg1[i] = deg1[j];
                    deg1[j] = temp1;
                }
            }
        }
        int temp2;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (deg2[i] < deg2[j])
                {
                    temp2 = deg2[i];
                    deg2[i] = deg2[j];
                    deg2[j] = temp2;
                }
            }
        }
        bool t = Degree_equal(deg2, deg1, n);
        if (!t)
        {
            printf("Graphs not isomorphic");
        }
        else
        {
            int inimat1[n + 1][n + 1];
            for (int i = 0; i < n + 1; i++)
            {
                for (int j = 0; j < n + 1; j++)
                {
                    inimat1[i][j] = 0;
                }
            }
            for (int i = 1; i < n + 1; i++)
            {
                inimat1[0][i] = i;
                inimat1[i][0] = i;
            }
            int inimat2[n + 1][n + 1];
            for (int i = 0; i < n + 1; i++)
            {
                for (int j = 0; j < n + 1; j++)
                {
                    inimat2[i][j] = 0;
                }
            }
            for (int i = 1; i < n + 1; i++)
            {
                inimat2[0][i] = i;
                inimat2[i][0] = i;
            }

            ini_mat(final1,inimat1);
            ini_mat(final2,inimat2);
            generatingcombinations_matrices(inimat1, inimat2, n);
            if(!is_isomorphic)
            printf("Graphs not isomorphic,no bijection found");
        }
        return 0;
    }
}
// check if degreearrays are equal
bool Degree_equal(int arr1[n], int arr2[n], int n)
{
    bool t = true;
    // Linearly compare elements
    for (int i = 0; i < n; i++)
    {
        int temp1, temp2;
        temp1 = arr1[i];
        temp2 = arr2[i];
        if (temp1 != temp2)
        {
            t = false;
            break;
        }
    }
    return t;
}

// intial adjacency matrix
int **ini_mat(int mat[e][2],int inimat[n+1][n+1])
{
    for (int i = 0; i < e; i++)
    {
        int a, b;
        a = mat[i][0];
        b = mat[i][1];
        inimat[a][b] = 1;
        inimat[b][a] = 1;
    }
    return inimat;
}
// generating an adjacency matrix with node values
int **generate_adj_permu(int gen_mat[n+1][n+1], int permu[n], int n)
{   
    int adj[n+1][n+1];
    for (int i = 0; i < n+1; i++)
        {
            for (int j = 0; j < n+1; j++)
            {
                adj[i][j] = gen_mat[i][j];
            }
        }
    for (int i = 1; i < n + 1; i++)
    {
        gen_mat[0][i] = permu[i - 1];
        gen_mat[i][0] = permu[i - 1];
    }
    int temp;
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {   
            gen_mat[i][j]=adj[gen_mat[i][0]][gen_mat[0][j]];
            
        }
    }
    return gen_mat;
}
// to check if matrix are same
bool check(int mat1[n+1][n+1], int mat2[n+1][n+1], int n)
{   bool t=true;
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            if (mat1[i][j] != mat2[i][j])
            {t=false;break;}
        }
    }
    if(t)
    {
        is_isomorphic=true;
        printf("Graphs are isomorphic \n");
        for(int i=1;i<n+1;i++)
        {
            printf("%d %d \n",mat1[0][i],mat2[0][i]);
        }
        exit(0);
    }
}
void call(int num[n], int n, int inimat1[n+1][n+1],int inimat2[n+1][n+1])
{   bool t=false;
    int gen_mat[n+1][n+1];
    for (int i = 0; i < n+1; i++)
        for (int j = 0; j < n+1; j++)
         gen_mat[i][j]=inimat2[i][j];
    generate_adj_permu(gen_mat,num,n);
    check(inimat1,gen_mat, n);
}
int *reverse(int num[n],int n)
{
    int i , tmp ;  
  for( i=0; i < n/2 ; i++ )  
  {  
    tmp = num [ i ] ;  
    num [ i ] = num[ n - 1 - i ] ;  
    num [ n - 1 - i ] = tmp ;  
  }  
  return num;
}
// generating factorial combinations
void generatingcombinations_matrices(int inimat1[n+1][n+1],int inimat2[n+1][n+1], int n)
{
    bool t = false;
    int count = 0;
    int num[n];
    int num1[n];
    int temp;
    for (int i = 0; i < n; i++)
        num[i] = i + 1;
    for (int j = 0; j < n+1; j++)
    {
        for (int i = 0; i < n-1 ; i++)
        {
            temp = num[i];
            num[i] = num[i + 1];
            num[i + 1] = temp;
            for (int i = 0; i < n; i++)
                 num1[i] = num[i];
            call(num,n,inimat1,inimat2);
            call(num1,n,inimat1,inimat2);
            
        }
    }
}

