/*
Version 01a 
Does not work...

*/

#include<iostream>
#include<vector>
using namespace std; 

class Slate {
    private:
        int a = 1;
        int iter = 0;
        int counter = 1;
        int depth = 2;

    public:
        int n, kn;
        vector<vector<int>> NKSlate;
    
    Slate ( int n=12, int kn=5, int depth=2 ) {
        this->n = n;
        this->kn = kn;
        this->depth = depth;
    }

    void setN(int n) { this->n = n; }
    void setKn(int kn) { this->kn = kn; }
    void setDepth(int depth) { this->depth = depth; }

    int getN() { return n; }
    int getKn() { return kn; }
    int getDepth() { return depth; }

    // member function makeNK
    void makeSlate() {
        // first make the NK array
        depth--;
        int NK[depth+2];

        // insert middle values in array as starting values
        NK[0] = n;
        NK[depth+1] = kn;
        for(int i=1; i<=depth; i++) { NK[i] = n-i; }
        // then call the makeSlate member function
        NKSlate = makeSlate( a, iter, depth, NK, NKSlate );
    }

    // member function makeSlate
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

    // member function printSlate
    void printSlate() {
        for(int i=0; i<NKSlate.size(); i++) {
            cout<<"Row "<<i<<":\t";
            for(int j=0; j<NKSlate[i].size(); j++) {
                cout<<NKSlate[i][j]<<"\t";
            }
            cout<<endl;
        }
    }
};

int main() { 
    // crucial to set the depth here.
    // depth must be greater than 0, and no greater than 
    // the difference of n and kn (???)

    int depth = 5;
    // these should be taken by cin>> (= user defined) eventually...
    const int n = 14;
    const int kn = 6;

    // this should be integrated somehow into the class Slate

    // make a matrix ("slate")
    // NKSlate = makeSlate(a, iter, depth, NK, NKSlate );

    Slate mySlate;
    mySlate.setN(n);
    mySlate.setKn(kn);
    mySlate.setDepth(depth);
    mySlate.makeSlate();
    mySlate.printSlate();

    return 0;
}