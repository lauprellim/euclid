// WORKS!!!

#include<iostream>
using namespace std; 

const int n = 16;
const int kn = 8;

int a = 1;
int iter = 0;

void recursion_for( int a, int iter, int depth, int* NK ) {
    // terminal condition
    if(a == depth+1) { return; }

    for(NK[a]=NK[a-1]-1; NK[a]>=NK[depth+1]+(depth-iter); NK[a]--) {
        // print all the elements in the array
        // check to see if the deepest loop has been reached.
        // only then print out the variables
        if(a == depth) {
            for(int i=0; i<depth+2; i++) cout<<NK[i]<<"\t";
            cout<<endl;
        }
        recursion_for( a+1, iter+1, depth, NK );
    }
}

int main() 
{ 
    // crucial to set the depth here.
    // depth must be greater than 0, and no greater than 
    // the difference of n and kn (???)
    int depth = 1;

    int NK[depth+2];

    // insert middle values in array as starting values
    NK[0] = n;
    NK[depth+1] = kn;
    for(int i=1; i<=depth; i++) { NK[i] = n-i; }

    recursion_for( a, iter, depth, NK);

    return 0;
}