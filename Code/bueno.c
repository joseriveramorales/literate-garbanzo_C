#include "stdlib.h"
#include "stdio.h"

// compile by running gcc code.c -o executableName
// execute by ./executableName

int main(){
    char c[10];
    int d[10];
    int* darr;
    darr = (int *)(malloc(10*sizeof(int)));
    size_t sizeC = sizeof(c);
    size_t sizeD = sizeof(d);
    size_t sizeDarr = sizeof(darr);
    printf("%zd\n",sizeC);
    printf("%zd\n",sizeD);
    printf("%zd\n", sizeDarr);
    free(darr);
    // int n = 5; 
    // int arr[] = { 0, 23, 14, 12, 9}; 
    // sort(n, arr);


    // change();
    return 0; 

}

// Function to sort the numbers using pointers 
void sort(int n, int* ptr) 
{ 
    int i, j, t; 
  
    // Sort the numbers using pointers 
    for (i = 0; i < n; i++) { 
  
        for (j = i + 1; j < n; j++) { 
  
            if (*(ptr + j) < *(ptr + i)) { 
  
                t = *(ptr + i); 
                *(ptr + i) = *(ptr + j); 
                *(ptr + j) = t; 
            } 
        } 
    } 
  
    // print the numbers 
    for (i = 0; i < n; i++) 
        printf("%d ", *(ptr + i)); 
} 

void change() {
    
    int arrr[] = {1,2,3,4,5};
    int *p;
    p = arrr;
    printf("%zd\n", *p + 1); // Basicamente cuando uso * antes del pointer estoy accesando el primer valor, el resto se puede accesar usando sumas
    *(p + 1) = *(p + 4);
    printf("%zd\n", *(p + 1));
}