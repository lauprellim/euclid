/*
===========================
Version 21 -- STABLE
===========================
Milestones:
Works
Setting NK[] and R[] arrays correctly in class hyperEuclid

Ideas:
Print partial hyperEuclid sets instead of/in addition to regular euclidean sets

Maybe add Copy Constructor(s)...
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

// checks inputs to make sure the n, k1, k2, ..., kn values are consecutive
bool checkParameters(int *NK, int depth) {
    for(int i=0; i<depth; i++) {
        // cout<<"Comparing "<<NK[i]<<" and "<<NK[i+1]<<"..."<<endl;
        if(NK[i] <= NK[i+1]) {
            isConsecutive=false;
            return isConsecutive;
        }
    }
    return isConsecutive;
}

// overloads "-" operator
// this allows you to take all of the elements at the INDECIES of vector rhs OUT of the vector lhs.
vector<int> operator-(const vector<int> lhs, const vector<int> rhs) {
    // it might be good here to check to see if the rhs has fewer elements than the lhs
    vector<int> result;
    for(int i=0; i < rhs.size(); i++) {
        result.push_back(lhs.at(rhs[i]));
    }
    return result;
}

/*
// this used to be its own function, outside of a class.
void printHyperSet(vector<int> theSet, int *NK, int *R, int depth, int indent) {
    string tabs;
    for(int i=0; i<indent; i++) tabs.append("\t");
    cout << tabs << "Hyper Euclidean set ( " << NK[0];   
    for(int j=1; j<depth+1; j++) { cout<<" "<<NK[j]<<"^"<<R[j]; }
    cout<<") = [ ";
    for (const int& l : theSet) { cout << l << " "; }
    cout<<"]"<<endl;
}
*/

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

    // member functions
    // This GENERATES a first-order Euclidean set using input n, k, and r
    // and rotates it using the member function rotateEuclid.
    vector<int> makeEuclid(int n, int k, int r ) {
        for (int i = 0; i<k; i++) {
            // using integer division - YES
            int num = ( i * n ) / k;
            euclidSet.push_back(num);
        }
        euclidSet = rotateEuclid(r);
        return euclidSet;
    }

    // Calculate the rotated vector. Example syntax:
    // euclid1.rotatedEuclid = euclid1.rotateEuclid(3);
    // -- but usually this will just be called from makeEuclid();
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
        // Simple fix for the last wraparound element.
        // This means: the last element of the IOI is equal to
        // the SPAN plus the first element (e.g. 12+0) minus the last element
        IOI[k-1] = (n+euclidSet[0])-euclidSet[k-1];
        return IOI;
    }

    // enquiry functions
    void printSet(vector<int> theSet, int indent) {
        string tabs;
        for(int i=0; i<indent; i++) tabs.append("\t");
        cout << tabs << "Euclidean set (" << n << ", " << k << "^"<<r<< ") is: [ ";
        for (const int& j : theSet) { cout << j << " "; }
        cout << "]" << endl;
    }

    void printIOI(vector<int> set, int indent) {
        string tabs;
        for(int i=0; i<indent; i++) tabs.append("\t");
        cout << tabs << "IOI is: < ";
        for (const int& j : set) { cout << j << " "; }
        cout << ">" << endl;
    }

    // destructor
    ~Euclid() { }
};

// very much under development!
class hyperEuclid:public Euclid {
    private:
        int *NK, *R;
        int depth;
    public:
    // do I need all these??!?
    vector<int> hyperEuclidSet {}, hyperIOI {}; // the series itself

    // setters
    void setNK( int* new_NK, int depth ) {
        // allocate size of NK[] array first
        NK = new int[depth];
        for(int j=0; j<depth+1; j++) { this->NK[j] = new_NK[j]; }
    }

    void setR( int* new_R, int depth ) {
        R = new int[depth];
        for(int i=0; i<depth+1; i++ ) { this->R[i] = new_R[i]; }
    }

    void setDepth( int depth ) { this->depth = depth; }

    // getters
    vector<int> getHyperEuclidSet() { return hyperEuclidSet; }
    vector<int> getHyperIOI() { return hyperIOI; }
    int getNK() { return *NK; }
    int getR() { return *R; }
    int getDepth() { return depth; }

    // print
    void printNK() {
        cout<<"NK array is: ";
        for (int i = 0; i<getDepth()+1; i++) { cout<<NK[i]<<" "; }
        cout<<endl;
    }

    void printR() {
        cout<<"R array is: ";
        for (int i=1; i<getDepth()+1; i++) { cout<<R[i]<<" "; }
        cout<<endl;
    }

    // member functions
    // void printHyperSet(vector<int> theSet, int *NK, int *R, int depth, int indent) {
    vector<int> makeHyperEuclid( int *NK, int *R, int depth ) {
        // Instantiate multiple instances of class Euclid depending on the desired depth
        // Note that each multiple instance will have default args as defined in the class constructor
        // therefore we override the defaults by explicitly calling the mutators

        // It might not be too difficult to modify this to produce subtract-first sets.

        Euclid myInstance[depth];
        for(int j=0; j<depth; j++) {
            myInstance[j].setN(NK[j]);
            myInstance[j].setK(NK[j+1]);
            myInstance[j].setR(R[j+1]);
            myInstance[j].euclidSet = myInstance[j].makeEuclid(NK[j], NK[j+1], R[j+1]);
            // this is printing the UNROTATED euclid set.
            // might be nice to print the partial hyperEuclid set also...see below vvvvvvv
            myInstance[j].printSet(myInstance[j].euclidSet, j);
            myInstance[j].IOI = myInstance[j].findIOI();
            myInstance[j].printIOI(myInstance[j].IOI, j);
        }

        // calculate the hyperEuclid set by using the overloaded 'subtraction' operator
        vector<int> hyperEuclid = myInstance[0].euclidSet;
        for(int m=1; m<depth; m++) {
            hyperEuclid = hyperEuclid - myInstance[m].euclidSet;
            // option to show INTERMEDIATE sets...???
        }
        hyperEuclidSet = hyperEuclid;
        return hyperEuclidSet;
    }

    // member functions
    // these functions OVERRIDE the printSet(), findIOI() and printIOI() function in Euclid class.
    void printSet(vector<int> theSet, int *NK, int *R, int depth) {
        string tabs;
        for(int i=0; i<depth; i++) tabs.append("\t");
        cout << tabs << "\e[1mHyper Euclidean set ( " << NK[0];   
        for(int j=1; j<depth+1; j++) { cout<<" "<<NK[j]<<"^"<<R[j]; }
        cout<<") = [ ";
        for (const int& l : theSet) { cout << l << " "; }
        cout<<"]\e[0m"<<endl;
    }

    vector<int> findIOI() {
        for (int i = 0; i<hyperEuclidSet.size(); i++) {
            int interval = hyperEuclidSet[i+1] - hyperEuclidSet[i];
            hyperIOI.push_back(interval);
        }
        // Fix for the last wraparound element.
        hyperIOI[hyperEuclidSet.size()-1] = (NK[0]+hyperEuclidSet[0])-hyperEuclidSet[hyperEuclidSet.size()-1];
        return hyperIOI;
    }

    void printIOI(vector<int> set, int indent) {
        string tabs;
        for(int i=0; i<indent; i++) tabs.append("\t");
        cout << tabs << "\e[1mHyperEuclid IOI is: < ";
        for (const int& j : set) { cout << j << " "; }
        cout << ">\e[0m" << endl;
    }

   // destructor
   ~hyperEuclid() { }
};

int main() {
    cout << "FIND HYPER-EUCLIDEAN SETS" << endl;
    // There is no inherent reason to limit depth to 5,
    // but as the problem is O(n^depth) we try not to let it grow
    // exponentially too far.
    cout<<"What depth (1-5)? ";
    cin>>depth;
    if(depth>5) {
        cout<<"Depth must be 5 or less. Please try again."<<endl;
        return 0;
    }

    int *NK; NK = new int[depth];
    int *R; R = new int[depth]; 

    // prompt user to input appropriate n, k and r values
    for (int i=0; i<=depth; i++) {
         if(i==0) {
            cout<<"Enter n (span): ";
            cin>>NK[0];
         } else {
            cout<<"Enter k"<<i<<": ";
            cin>>NK[i];
            // the first element of the NK[] array (n) is NOT rotated.
            // subsequent elements of the NK[] array (k1, ..., kn) CAN be associated with a rotation.
            cout<<"\tEnter this r"<<i<<": ";
            cin>>R[i];
         }
    }

    // n, k1, k2, k3, ..., kn must be in descending order (and not equal).
    checkParameters(NK, depth);
    if(isConsecutive == 0) {
        cout<<"Values are not consecutive (descending). Ending program..."<<endl;;
        return 0;   // end execution of this program
    } else cout<<"Values are consecutive (descending). Executing program..."<<endl;

    hyperEuclid hyperEuclidSet0;

    hyperEuclidSet0.setNK(NK, depth);
    hyperEuclidSet0.setR(R, depth);
    hyperEuclidSet0.setDepth(depth);

    // Do I need to send these arguments now that they've been set in the class?
    hyperEuclidSet0.makeHyperEuclid( NK, R, depth );
    hyperEuclidSet0.printSet(hyperEuclidSet0.hyperEuclidSet, NK, R, depth);
    hyperEuclidSet0.hyperIOI = hyperEuclidSet0.findIOI();
    hyperEuclidSet0.printIOI(hyperEuclidSet0.hyperIOI, depth);

    // to check stuff -- maybe make a printDepth() too
    // hyperEuclidSet0.printNK();
    // hyperEuclidSet0.printR();

    // Make a whole new class of hyperEuclidSet, as I would like IOI as well...
    // printHyperSet(hyperEuclid, NK, R, depth, 0);
    delete []NK;
    delete []R;
    return 0;
}