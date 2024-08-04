/*
===========================
Version 03 -- STABLE ROTATE
===========================

Maybe add Copy Constructor(s)...
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// global var for checking input values n, k, ..., kn
static bool isConsecutive = true;

// the user-defined depth we are working with
// default depth is 1 (traditional first-order Euclidean set)
static int depth = 1;

// boldface
static const string boldOn = "\e[1m";
static const string boldOff = "\e[0m";

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
   
    // mutators -- When I create multiple instances of the class
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
    // and rotates it using rotateEuclid.
    vector<int> makeEuclid() {
        for (int i = 0; i<k; i++) {
            // using integer division - YES
            int num = ( i * n ) / k;
            euclidSet.push_back(num);
        }
        euclidSet = rotateEuclid();
        return euclidSet;
    }

    // Calculate the rotated vector. Example syntax:
    // euclid1.rotatedEuclid = euclid1.rotateEuclid(3);
    // -- but usually this will just be called from makeEuclid();
    vector<int> rotateEuclid() {
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
            // this will only find the IOI of euclidSet, not rotatedEuclid
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
    void printSet(int indent) {
        string tabs;
        for(int i=0; i<indent; i++) tabs.append("\t");
        cout << tabs << "Euclidean set (" << n << ", " << k << "^"<<r<< ") is: [ ";
        for (const int& j : euclidSet) { cout << j << " "; }
        cout << "]" << endl;
    }

    void printIOI(int indent) {
        string tabs;
        for(int i=0; i<indent; i++) tabs.append("\t");
        cout << tabs << "IOI is: < ";
        for (const int& j : IOI) { cout << j << " "; }
        cout << ">" << endl;
    }

    // destructor
    ~Euclid() { }
};

class hyperEuclid:public Euclid {
    private:
        int *NK, *R;
        int depth;
    public:
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
    void makeHyperEuclidRotateFirst() {
        // Instantiate multiple instances of class Euclid depending on the desired depth
        // Note that each multiple instance will have default args as defined in the class constructor
        // therefore we override the defaults by explicitly calling the mutators

        // This is the rotate first method.
        Euclid myInstance[depth];
        for(int j=0; j<depth; j++) {
            myInstance[j].setN(NK[j]);
            myInstance[j].setK(NK[j+1]);
            myInstance[j].setR(R[j+1]);
            myInstance[j].euclidSet = myInstance[j].makeEuclid();

            if(j>0) {
                myInstance[j].euclidSet = myInstance[j-1].euclidSet - myInstance[j].euclidSet;
            }
            myInstance[j].printSet(j);
            // set this intance's N back to the global value
            myInstance[j].setN(NK[0]);
            myInstance[j].IOI = myInstance[j].findIOI();
            myInstance[j].printIOI(j);
        }
        hyperEuclidSet = myInstance[depth-1].euclidSet;
    }

    void makeHyperEuclidSubtractFirst() {
        // Subtract first method

        Euclid myInstance[depth];
        for(int j=0; j<depth; j++) {
            myInstance[j].setN(NK[j]);
            myInstance[j].setK(NK[j+1]);
            // For subtract first, set this R value to 0, BEFORE rotation!
            myInstance[j].setR(0);
            myInstance[j].euclidSet = myInstance[j].makeEuclid();

            // do SUBTRACTION FIRST
            if(j>0) {
                // don't do this for the first set!
                myInstance[j].euclidSet = myInstance[j-1].euclidSet - myInstance[j].euclidSet;
            }
            // now do ROTATION -- but first, we need to reset this instance's R value
            myInstance[j].setR(R[j+1]);
            // otherwise the local "n" variable will incorrectly rotate this -- we need to use global n
            myInstance[j].setN(NK[0]);
            myInstance[j].euclidSet = myInstance[j].rotateEuclid();
            myInstance[j].IOI = myInstance[j].findIOI();
            // set this intance's N back to the correct value
            myInstance[j].setN(NK[j]);
            myInstance[j].printSet(j);
            myInstance[j].printIOI(j);
        }
        hyperEuclidSet = myInstance[depth-1].euclidSet;
    }

    // member functions
    // these functions OVERRIDE the printSet(), findIOI() and printIOI() function in Euclid class.
    void printSet() {
        string tabs;
        for(int i=0; i<depth; i++) tabs.append("\t");
        cout << tabs << boldOn << "Hyper Euclidean set ( " << NK[0];   
        for(int j=1; j<depth+1; j++) { cout<<" "<<NK[j]<<"^"<<R[j]; }
        cout<<" ) = [ ";
        for (const int& l : hyperEuclidSet) { cout << l << " "; }
        cout<<boldOff<< "] " << endl;
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

    void printIOI(int indent) {
        string tabs;
        for(int i=0; i<indent; i++) tabs.append("\t");
        cout << tabs << boldOn << "HyperEuclid IOI is: < ";
        for (const int& j : hyperIOI) { cout << j << " "; }
        cout << boldOff << "> " << endl;
    }

   // destructor
   ~hyperEuclid() { }
};

int main() {
    cout << boldOn << "FIND A HYPER-EUCLIDEAN SET" << boldOff << endl;

    // ask whether user wants rotate or subtract first method
    cout<<"Rotate first or subtract first method (r/s/q)? ";
    char method;
    cin>>method;
    if(method =='q') { cout<<"Goodbye!"<<endl; return 0; }
    if(method !='r' && method !='s') { cout<<"Please enter r (rotate first) or s (subtract first)."<<endl;; main(); }

    // There is no inherent reason to limit depth to 5
    cout<<"What depth (1-5)? ";
    cin>>depth;
    if(depth>5) {
        cout<<"Depth must be 5 or less. Please try again."<<endl;
        return 0;
    }

    int *NK; NK = new int[depth];
    // initialize all array values to 0
    NK[depth] = {};
    int *R; R = new int[depth+1]; 
    R[depth+1] = {};

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

    hyperEuclidSet0.setNK(NK, depth+1);
    hyperEuclidSet0.setR(R, depth);
    hyperEuclidSet0.setDepth(depth);

    /*
    // check array values
    cout<<"=================================="<<endl;
    hyperEuclidSet0.printNK();
    hyperEuclidSet0.printR();
    cout<<"=================================="<<endl;
    */

    if(method=='r') hyperEuclidSet0.makeHyperEuclidRotateFirst();
    else hyperEuclidSet0.makeHyperEuclidSubtractFirst();

    hyperEuclidSet0.printSet();
    hyperEuclidSet0.hyperIOI = hyperEuclidSet0.findIOI();
    hyperEuclidSet0.printIOI(depth);

    delete []NK;
    delete []R;

    cout<<"Would you like to find another set? (y/n): ";
    char cont;
    cin>>cont;
    if(cont =='y') main();
    else if(cont == 'n') { cout<<"Goodbye!"<<endl; return 0; }
    else { cout<<"Didn't understand your response, quitting."; return 0; }
}