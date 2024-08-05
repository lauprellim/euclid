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
bool checkParameters(vector<int> NK, int depth) {
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
        cout << tabs << "Euclidean set ( " << boldOn << n << ", " << k << "^"<<r<< boldOff << " ) is: [ ";
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

// class hyperEuclid:public Euclid {
class hyperEuclid {
    private:
        // convert these into vector<int>s...
        vector<int> NK, R;
        int depth;
    public:
        vector<int> hyperEuclidSet {}, hyperIOI {}, rotatedHyperEuclid {};// the series itself

    // setters
    void setNK( vector<int> new_NK, int depth ) {
        // allocate size of NK[] array first
        // this seems to be causing the malloc_error_break...
        // int *NK = NULL;
        // int NK = new int[depth];
        // void setN(int n) { this->n = n; }
        this->NK = new_NK;
    }

    void setR( vector<int> new_R, int depth ) {
        // int *R = NULL;
        // int R = new int[depth];
        // for(int i=0; i<depth+1; i++ ) { this->R[i] = new_R[i]; }
        this->R = new_R;
    }

    void setDepth( int depth ) { this->depth = depth; }

    // getters
    vector<int> getNK() { return NK; }
    vector<int> getR() { return R; }
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
    void makeOneHERF() {
        // This is the rotate first method.
        Euclid euclidInstance[depth];
        hyperEuclid hyperEuclidSetInstance[depth];
        for(int j=0; j<depth; j++) {
            // in the first iteration we just want to make a basic Euclid set, no hyperSet.
            if(j == 0) {
                // make first Euclidean set
                euclidInstance[0].setN(NK[0]);
                euclidInstance[0].setK(NK[1]);
                euclidInstance[0].setR(R[1]);
                euclidInstance[0].makeEuclid();
                euclidInstance[0].printSet(0);
                euclidInstance[0].IOI = euclidInstance[0].findIOI();
                euclidInstance[0].printIOI(0);
            } else {
                euclidInstance[j].setN(NK[j]);
                euclidInstance[j].setK(NK[j+1]);
                euclidInstance[j].setR(R[j+1]);
                euclidInstance[j].makeEuclid();
                // the first time you just subtract the top-level euclid set from the newly generated one
                if(j == 1) {
                    hyperEuclidSetInstance[j].hyperEuclidSet = euclidInstance[0].euclidSet - euclidInstance[1].euclidSet;
                } else {
                    hyperEuclidSetInstance[j].hyperEuclidSet = hyperEuclidSetInstance[j-1].hyperEuclidSet - euclidInstance[j].euclidSet;
                }
                hyperEuclidSetInstance[j].setNK(NK, j+1);
                // something could be wrong here
                hyperEuclidSetInstance[j].setR(R, j+1);
                hyperEuclidSetInstance[j].setDepth(j+1);
                hyperEuclidSetInstance[j].printSet();
                hyperEuclidSetInstance[j].hyperIOI = hyperEuclidSetInstance[j].findIOI();
                hyperEuclidSetInstance[j].printIOI(j);
            }
        }
    }

    void makeOneHESF() {
        // Subtract first method
        Euclid euclidInstance[depth];
        hyperEuclid hyperEuclidSetInstance[depth];
        for(int j=0; j<depth; j++) {
            if(j == 0) {
                // make the first Euclidean set
                euclidInstance[0].setN(NK[0]);
                euclidInstance[0].setK(NK[1]);
                euclidInstance[0].setR(R[1]);
                euclidInstance[0].makeEuclid();
                euclidInstance[0].printSet(0);
                euclidInstance[0].IOI = euclidInstance[0].findIOI();
                euclidInstance[0].printIOI(0);
            } else {
                euclidInstance[j].setN(NK[j]);
                euclidInstance[j].setK(NK[j+1]);
                // this is different from rotate first:
                euclidInstance[j].setR(0);
                euclidInstance[j].makeEuclid();
                // do subtract first:
                if( j == 1 ) {
                    hyperEuclidSetInstance[j].hyperEuclidSet = euclidInstance[0].euclidSet - euclidInstance[1].euclidSet;
                } else {
                    hyperEuclidSetInstance[j].hyperEuclidSet = hyperEuclidSetInstance[j-1].hyperEuclidSet - euclidInstance[j].euclidSet;
                }
                hyperEuclidSetInstance[j].setNK(NK, j+1);
                // something could be wrong here
                hyperEuclidSetInstance[j].setR(R, j+1);
                hyperEuclidSetInstance[j].setDepth(j+1);
                // NOW do rotate...
                // hyperEuclidSetInstance[j].rotateHyperEuclid(j+1);
                hyperEuclidSetInstance[j].rotateHyperEuclid();
                hyperEuclidSetInstance[j].printSet();
                hyperEuclidSetInstance[j].hyperIOI = hyperEuclidSetInstance[j].findIOI();
                hyperEuclidSetInstance[j].printIOI(j);
            }
        }
    }

    vector<int> rotateHyperEuclid() {
        for (int i = 0; i<hyperEuclidSet.size(); i++) {
            int num = ( ( hyperEuclidSet[i] + R[depth] ) % NK[0] );
            rotatedHyperEuclid.push_back(num);
        }
        // sort the vector
        sort(rotatedHyperEuclid.begin(), rotatedHyperEuclid.end());
        hyperEuclidSet = rotatedHyperEuclid;
        return hyperEuclidSet;
    }

    // member functions
    // these functions OVERRIDE the printSet(), findIOI() and printIOI() function in Euclid class.
    void printSet() {
        string tabs;
        for(int i=0; i<depth-1; i++) tabs.append("\t");
        cout << tabs << "Hyper Euclidean set ( " << boldOn << NK[0];   
        for(int j=1; j<depth+1; j++) { cout<<" "<<NK[j]<<"^"<<R[j]; }
        cout<<boldOff<<" ) = [ ";
        for (const int& l : hyperEuclidSet) { cout << l << " "; }
        cout<< "] " << endl;
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
        cout << tabs << "HyperEuclid IOI is: < ";
        for (const int& j : hyperIOI) { cout << j << " "; }
        cout << "> " << endl;
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

    // initialize all array values to 0
    vector<int> NK;
    vector<int> R;

    // prompt user to input appropriate n, k and r values
    for (int i=0; i<=depth; i++) {
        int nkInput, rInput;
        if(i==0) {
            cout<<"Enter n (span): ";
            cin>>nkInput;
            NK.push_back(nkInput);
            // cin>>NK[0];
            R.push_back(0);
        } else {
            cout<<"Enter k"<<i<<": ";
            cin>>nkInput;
            NK.push_back(nkInput);
            // the first element of the NK[] array (n) is NOT rotated.
            // subsequent elements of the NK[] array (k1, ..., kn) CAN be associated with a rotation.
            cout<<"\tEnter this r"<<i<<": ";
            cin>>rInput;
            R.push_back(rInput);
        }
    }

    // n, k1, k2, k3, ..., kn must be in descending order (and not equal).
    checkParameters(NK, depth);
    if(isConsecutive == 0) {
        cout<<"Values are not consecutive (descending). Ending program..."<<endl;;
        return 0;   // end execution of this program
    } else cout<<"Values are consecutive (descending). Executing program..."<<endl;

    // this is basically a dummy instance...
    hyperEuclid starterHESet;

    starterHESet.setNK(NK, depth+1);
    starterHESet.setR(R, depth);
    starterHESet.setDepth(depth);

    /*
    // check array values
    cout<<"=================================="<<endl;
    basicHESet.printNK();
    basicHESet.printR();
    cout<<"=================================="<<endl;
    */

    if(method=='r') starterHESet.makeOneHERF();
    else starterHESet.makeOneHESF();

    cout<<"Would you like to find another set? (y/n): ";
    char cont;
    cin>>cont;
    if(cont =='y') main();
    else if(cont == 'n') { cout<<"Goodbye!"<<endl; return 0; }
    else { cout<<"Didn't understand your response, quitting."; return 0; }
}