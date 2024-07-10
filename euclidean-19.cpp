/*
====================
Version 19 -- STABLE
====================
Milestones:
Works
Does not iterate
printHyperSet might work better by extending (inheriting) Euclid set
printIOI might also work as an extension of Euclid

Maybe add Deep Copy Constructor.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
// #include <cstdarg>  // for variadic functionality
using namespace std;

// global var for checking input values n, k, ..., kn
static bool isConsecutive = true;

// the user-defined depth we are working with
// default depth is 1 (traditional first-order Euclidean set)
static int depth = 1;

// checks inputs to make sure the values are consecutive
bool checkParameters(int *a, int depth) {
    for(int i=0; i<depth-1; i++) {
        if(a[i]<=a[i+1]) {
            isConsecutive=false;
            return isConsecutive;
        }
    }
    return isConsecutive;
}

// overloads "-" operator
// this allows you to take all of the elements at the INDECIES of vector rhs
// OUT of the vector lhs.
vector<int> operator-(const vector<int> lhs, const vector<int> rhs) {
    // it might be good here to check to see if the rhs has fewer elements than the lhs
    vector<int> result;
    for(int i=0; i < rhs.size(); i++) {
        result.push_back(lhs.at(rhs[i]));
    }
    return result;
}

void printHyperSet(vector<int> theSet, int *NK, int *R, int depth, int indent) {
    string tabs;
    for(int i=0; i<indent; i++) tabs.append("\t");
    cout << tabs << "Hyper Euclidean set ( " << NK[0];   
    for(int j=1; j<depth+1; j++) { cout<<" "<<NK[j]<<"^"<<R[j]; }
    cout<<") = [ ";
    for (const int& l : theSet) { cout << l << " "; }
    cout<<"]"<<endl;
}

class Euclid {
    private:
    int n, k, r;

    public:
    vector<int> euclidSet {}, IOI {}, rotatedEuclid {};

    public:
    // constructor; initializes n and k values
    Euclid ( int n=2, int k=1, int r=0 ) {
        this->n = n;
        this->k = k;
    }

    // write a copy constructor??
    // Euclid ( Euclid &set ) {}
   
    // mutators -- I need these, as when I create multiple instances of the class
    // they contain the DEFAULT values in the constructor above!
    void setN(int n) { this->n = n; }
    void setK(int k) { this->k = k; }
    void setR(int r) { this->r = r; }

    // accessors
    int getN() { return n; }
    int getK() { return k; }
    int getR() { return r; }

    // facilitators, member functions, inline functions
    // this GENERATES a first-order Euclidean set using input n, k.
    vector<int> makeEuclid(int n, int k, int r ) {
        for (int i = 0; i<k; i++) {
            int num = ( i * n ) / k;
            euclidSet.push_back(num);
        }
        // euclid0.rotatedEuclid = euclid0.rotateEuclid(0);
        euclidSet = rotateEuclid(r);
        return euclidSet;
    }

    // calculate the rotated vector
    // example syntax:
    // euclid1.rotatedEuclid = euclid1.rotateEuclid(3);
    vector<int> rotateEuclid(int r) {
        rotatedEuclid = {};
        for (int i = 0; i<k; i++) {
            int num = ( ( euclidSet[i] + r ) % n );
            rotatedEuclid.push_back(num);
        }
        // sort the vector
        sort(rotatedEuclid.begin(), rotatedEuclid.end());
        return rotatedEuclid;
    }

    vector<int> findIOI() {
        for (int i = 0; i<k; i++) {
            // this will only find the IOI of euclidSet, not rotatedEuclid!
            int interval = euclidSet[i+1] - euclidSet[i];
            IOI.push_back(interval);
        }
        // simple fix for the last wraparound element
        // this means: the last element of the IOI is equal to
        // the SPAN plus the first element (e.g. 12+0)
        // MINUS the last element. This should work...there were odd values!
        IOI[k-1] = (n+euclidSet[0])-euclidSet[k-1];
        return IOI;
    }

    // enquiry functions
    void printSet(vector<int> theSet, int indent) {
        string tabs;
        for(int i=0; i<indent; i++) tabs.append("\t");
        cout << tabs << "Euclidean set depth "<<indent<<" = (" << n << ", " << k << "^"<<r<< ") is: [ ";
        for (const int& j : theSet) { cout << j << " "; }
        cout << "]" << endl;
    }
    
    // want to get rid of this function
    /*
    void printRotated(int r) {
        cout << "Rotating set by " << r << " is: [ ";
        for (const int& j : rotatedEuclid) { cout << j << " "; }
        cout << "]" << endl;
    }
    */

    void printIOI(vector<int> set, int indent) {
        string tabs;
        for(int i=0; i<indent; i++) tabs.append("\t");
        cout << tabs << "IOI is: < ";
        for (const int& j : set) { cout << j << " "; }
        cout << ">" << endl;
    }

    // destructor
    ~Euclid() {
    // You could count the number of objects destroyed here
    }

};

int main() {
    cout << "FIND HYPER-EUCLIDEAN SETS" << endl;
    cout<<"What depth (1-5)? ";
    cin>>depth;
    if(depth>5) {
        cout<<"Depth must be 5 or less. Please try again."<<endl;
        return 0;
    }
    int *NK; NK = new int[depth];
    int *R; R = new int[depth]; 

    // prompt user to input values
    for (int i=0; i<=depth; i++) {
         if(i==0) {
            cout<<"Enter n (span): ";
            cin>>NK[0];
         } else {
            cout<<"Enter k"<<i<<": ";
            cin>>NK[i];
            // the first element of the NK[] array (n) is not rotated.
            // subsequent elements of the NK[] array (k1, ..., kn) can be associated with a rotation.
            cout<<"\tEnter this r"<<i<<": ";
            cin>>R[i];
         }
    }

    checkParameters(NK, depth);
    if(isConsecutive == 0) {
        cout<<"Values are not consecutive (descending). Ending program..."<<endl;;
        return 0;   // end execution of this program
    } else cout<<"Values are consecutive (descending). Executing program..."<<endl;

    // instantiate multiple instances of class Euclid
    // depending on the desired depth
    // note that each multiple instance will have default args as defined in the class constructor
    // therefore we override the defaults by explicitly calling the mutators
    Euclid myInstance[depth];
    for(int j=0; j<depth; j++) {
        myInstance[j].setN(NK[j]);
        myInstance[j].setK(NK[j+1]);
        myInstance[j].setR(R[j+1]);
        myInstance[j].euclidSet = myInstance[j].makeEuclid(NK[j], NK[j+1], R[j+1]);
        myInstance[j].printSet(myInstance[j].euclidSet, j);
        myInstance[j].IOI = myInstance[j].findIOI();
        myInstance[j].printIOI(myInstance[j].IOI, j);
    }

    // construct the Hyper Euclidean set by "subtracting"...
    vector<int> hyperEuclid = myInstance[0].euclidSet;
    for(int m=1; m<depth; m++) {
        hyperEuclid = hyperEuclid - myInstance[m].euclidSet;
        // show INTERMEDIATE sets...
        printHyperSet(hyperEuclid, NK, R, depth, 0);
    }
    cout<<endl;

    // maybe inherit Euclid class to hyperEuclid r something like that?
    // might need to make a whole new class of hyperSet, as I would like IOI as well...
    printHyperSet(hyperEuclid, NK, R, depth, 0);
    delete []NK;
    delete []R;
    return 0;
}