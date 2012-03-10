#include <stdlib.h>
#include <stdio.h> 
typedef float (*UpdateCallback)(float element);
 
void UpdateElements(float *array, int n, UpdateCallback updateCallback)
{
    int i;
    for ( i = 0; i < n; ++i ) {
        array[i] = updateCallback(array[i]);
    }
}
 
float DoubleValue(float value)
{
    return 2.0 * value;
}
 
int main(void) {
    const int N = 10;
    float a[N];
 
    // Initialize array
    int i;
    for ( i = 0; i < N; ++i ) a[i] = rand() / (float)RAND_MAX;


    for ( i = 0; i < N; ++i ) printf("a[%d]=%f\n",i,a[i]); 
    // Double elements
    UpdateElements( a, N, DoubleValue );
    printf("\nAfter statement: UpdateElements( a, N, DoubleValue );\n");
    for ( i = 0; i < N; ++i ) printf("a[%d]=%f\n",i,a[i]); 
 


    return 0;
}

