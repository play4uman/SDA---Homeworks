#include <iostream>

using namespace std;

// Recursive execution of Fibonacci's sequence with complexity O(2^n)
int fibRecursion (int n){
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    else
        return fibRecursion(n-1) + fibRecursion(n-2);
}

// Fibonacci's sequence using dynamical optimisation with complexity O(n)
int fibDynamic (int n){
    int* arr = new int[n];
    arr[0] = 0;
    arr[1] = 1;
    if (n == 0)
        return arr[0];
    if (n == 1)
        return arr[1];

    int counter = 2;
    while (counter <= n){
        arr[counter] = arr[counter - 1] + arr[counter - 2];
        counter++;
    }

    return arr[n];
}


// Helper functions for Fib using matrices
void multiply2x2Matrix (int F[2][2], int M[2][2]){
    int x =  F[0][0]*M[0][0] + F[0][1]*M[1][0];
    int y =  F[0][0]*M[0][1] + F[0][1]*M[1][1];
    int z =  F[1][0]*M[0][0] + F[1][1]*M[1][0];
    int w =  F[1][0]*M[0][1] + F[1][1]*M[1][1];

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

// Helper functions for Fib using matrices
void power (int F[2][2], int n){
    int M[2][2] = {{1,1}, {1,0}};
    for (int i = 2; i <= n; i++)
      multiply2x2Matrix(F, M);
}


//Fib sequence using 2x2 matrices with complexity (logn)
int fibMatrix (int n){
    int F[2][2] = {{1,1},{1,0}};
    if (n == 0)
      return 0;
    power(F, n-1);
    return F[0][0];
}


int main()
{
    return 0;
}
