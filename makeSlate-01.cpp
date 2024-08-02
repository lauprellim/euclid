/*
Version 9a

Attempting to save NKSlate into a 2D matrix and return it to the main() function

*/

#include<iostream>
#include<vector>
using namespace std; 

// these should be taken by cin>> (= user defined) eventually...
const int n = 12;
const int kn = 3;

int a = 1;
int iter = 0;
// could be static?
int counter = 1;

// make a 2D NKVector
static vector<vector<int>> NKSlate;

class Slate {


};


vector<vector<int>> makeSlate( int a, int iter, int depth, int* NK, vector<vector<int>> NKSlate ) {
    // terminal condition
    if(a == depth+1) { return NKSlate; }

    for(NK[a]=NK[a-1]-1; NK[a]>=NK[depth+1]+(depth-iter); NK[a]--) {
        // check to see if the deepest loop has been reached.
        // only then print out the variables
        if(a == depth) {
            // fill a row of the 2D vector first
            vector<int> NKSlateThisRow;
            for(int i=0; i<depth+2; i++) {
                NKSlateThisRow.push_back(NK[i]);
            }
            // now push the row onto the 2D vector
            NKSlate.push_back(NKSlateThisRow);
            counter++;
        }
        NKSlate = makeSlate( a+1, iter+1, depth, NK, NKSlate );
    }
    return NKSlate;
}

int main() { 
    // crucial to set the depth here.
    // depth must be greater than 0, and no greater than 
    // the difference of n and kn (???)
    int depth = 2;
    depth--;
    int NK[depth+2];

    // insert middle values in array as starting values
    NK[0] = n;
    NK[depth+1] = kn;
    for(int i=1; i<=depth; i++) { NK[i] = n-i; }

    // make a matrix ("slate")
    NKSlate = makeSlate(a, iter, depth, NK, NKSlate );

    // display matrix data
    for(int i=0; i<NKSlate.size(); i++) {
        cout<<"Row "<<i<<":\t";
        for(int j=0; j<NKSlate[i].size(); j++) {
            cout<<NKSlate[i][j]<<"\t";
        }
        cout<<endl;
    }

    return 0;
}