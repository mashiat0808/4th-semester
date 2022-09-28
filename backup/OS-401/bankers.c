#include <stdio.h>
int main()
{
    int a = 5; // process no
    int b= 3; // resource no
    int alloc[5][3] = { { 3, 1, 0 }, { 2, 1, 0 },  { 2, 0, 1 },  { 0, 0, 1 },   { 0, 0, 1 } }; 
 
    int max[5][3] = { { 6, 3, 2},   { 2, 1, 3 },   { 4, 3, 1 },  { 0, 1, 2 },   { 2, 3, 1} }; 
 
    int avail[3] = { 3, 3, 2 }; // Avail Resources
 
    int f[a], ans[a], ind = 0;
    for ( int k = 0; k < a; k++) {
        f[k] = 0;
    }
    int need[a][b];
    for (int i = 0; i < a; i++) {
        for ( int j = 0; j < b; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < a; i++) {
            if (f[i] == 0) {
 
                int flag = 0;
                for (int j = 0; j < b; j++) {
                    if (need[i][j] > avail[j]){
                        flag = 1;
                         break;
                    }
                }
 
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < b; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }
   
      int flag = 1;
       
      for(int i=0;i<a;i++)
    {
      if(f[i]==0)
      {
        flag=0;
         printf("The system is UNSAFE");
        break;
      }
    }
     
      if(flag==1)
    {
      printf("Following is the Sequence to get all the processes done: \n");
      for (int i = 0; i < a - 1; i++)
      {
        printf(" P%d ->", ans[i]);
      }
      printf(" P%d", ans[a - 1]);
    }
     
 
    return (0);

}