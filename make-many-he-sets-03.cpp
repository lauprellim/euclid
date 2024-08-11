#include<iostream>
#include<vector>
#include <algorithm>
#include <string>
using namespace std;

// boldface
static const string boldOn = "\e[1m";
static const string boldOff = "\e[0m";

static long int globalCounter = 0;

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

    void printQuick(int indent) {
        string tabs;
        for(int i=0; i<indent; i++) tabs.append("\t");
        cout << tabs << "E ( " << n << ", " << k << "^"<<r << " ) = [ ";
        for (const int& j : euclidSet) { cout << j << " "; }
        cout<<"] < ";
        for (const int& j : IOI) { cout << j << " "; }
        cout << "> "<<endl;
    }

    // destructor
    ~Euclid() { }
};

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

    void makeManyHERF() {
        // This is the rotate first method.
        Euclid euclidInstance[depth];
        hyperEuclid hyperEuclidSetInstance[depth];
        for(int j=0; j<depth; j++) {
            // in the first iteration we just want to make a basic Euclid set, no hyperSet.
            if(j == 0) {
                // Increment globalCounter only ONCE per generated group of HE sets: 
                globalCounter++;
                // make first Euclidean set
                euclidInstance[0].setN(NK[0]);
                euclidInstance[0].setK(NK[1]);
                euclidInstance[0].setR(R[1]);
                euclidInstance[0].makeEuclid();
                euclidInstance[0].IOI = euclidInstance[0].findIOI();
                euclidInstance[0].printQuick(0);
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
                hyperEuclidSetInstance[j].hyperIOI = hyperEuclidSetInstance[j].findIOI();
                hyperEuclidSetInstance[j].printQuick(j);
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

    void makeManyHESF() {
        // Subtract first method
        Euclid euclidInstance[depth];
        hyperEuclid hyperEuclidSetInstance[depth];
        for(int j=0; j<depth; j++) {
            if(j == 0) {
                // increment globalCounter only ONCE per generated group of HE sets: 
                globalCounter++;
                // make the first Euclidean set
                euclidInstance[0].setN(NK[0]);
                euclidInstance[0].setK(NK[1]);
                euclidInstance[0].setR(R[1]);
                euclidInstance[0].makeEuclid();
                euclidInstance[0].IOI = euclidInstance[0].findIOI();
                euclidInstance[0].printQuick(0);
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
                hyperEuclidSetInstance[j].hyperIOI = hyperEuclidSetInstance[j].findIOI();
                hyperEuclidSetInstance[j].printQuick(j);
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

    void printQuick(int indent) {
        string tabs;
        for(int i=0; i<indent; i++) tabs.append("\t");
        cout << globalCounter << tabs << "HE ( " << NK[0];   
        for(int j=1; j<depth+1; j++) { cout<<" "<<NK[j]<<"^"<<R[j]; }
        cout<<" ) = [ ";
        for (const int& l : hyperEuclidSet) { cout << l << " "; }
        cout<< "] < ";
        for (const int& j : hyperIOI) { cout << j << " "; }
        cout << ">"<<endl;
    }

   // destructor
   ~hyperEuclid() { }
};




class Slate {
    private:
        int a = 1;
        int iter = 0;
        int counter = 1;
        int depth;

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

    // make a matrix ("slate")
    // NKSlate = makeSlate(a, iter, depth, NK, NKSlate );

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
        cout<<endl<<"-----------------"<<endl;
        cout<<"Your slate is:"<<endl;
        for(int i=0; i<NKSlate.size(); i++) {
            cout<<"Row "<<i<<":\t";
            for(int j=0; j<NKSlate[i].size(); j++) {
                cout<<NKSlate[i][j]<<"\t";
            }
            cout<<endl;
        }
        cout<<"----------------"<<endl;
    }
};

// Class Stream calculates all the r values (rotation) and iterates
class Stream {
    public:
        vector<int> rList, HESet;
        int depth = HESet.size();
        int a, counter;

        // method r = "rotation first"; method s = "subtraction first"
        char method;
    
    Stream( int a=1, vector<int> rList={0}, int counter=0 )  {
        this->a = a;
        this->rList = rList;
        this->counter = counter;
    }

    // void setDepth(int depth) { this->depth = depth;}
    // This is the NON-RECURSIVE version of this function...it only works to depth 2.
    // This function is never called, it's vestigal...NR = "non-recursive"
    void makeSetNR() {
        for(int i=0; i<HESet[0]; i++) {
            for(int j=0; j<HESet[0]; j++) {
                    cout<<HESet[0]<<" "<<HESet[1]<<"^"<<i<<" "<<HESet[2]<<"^"<<j<<endl;
            }
        }
    }

    vector<int> makeSetREC( int a, vector<int> rList ) {
        if(a == depth+1) { return rList; }
        for(rList[a] = 0; rList[a] < HESet[0]; rList[a]++) {
            if( a == depth ) { 

                // make the hyperEuclid set
                hyperEuclid thisHESet;
                thisHESet.setDepth(depth);
                thisHESet.setNK(HESet, depth+1);
                thisHESet.setR(rList, depth);

                // this comparison should probably go somewhere else...
                // comparison, r- or s-first...
                if(method == 'r') thisHESet.makeManyHERF();
                else thisHESet.makeManyHESF();

                cout<<endl;
                // this counts only the unique sets
            }
            rList = makeSetREC( a+1, rList );
        }
        return rList;
    }
};



int main() {

    int depth, n, kn;
    char method;

    cout<<"MAKE MANY HYPEREUCLIDEAN SETS"<<endl;
 
    cout<<"Rotate first or subtract first method (r/s/q)? ";
    cin>>method;
    if(method =='q') { cout<<"Goodbye!"<<endl; return 0; }
    if(method !='r' && method !='s') { cout<<"Please enter r (rotate first) or s (subtract first)."<<endl;; main(); }
 
    cout<<"What is your desired depth? (1-5): ";
    cin>>depth;

    cout<<"What is your desired starting span (n)? ";
    cin>>n;

    cout<<"What is your desired ending span (kn)? ";
    cin>>kn;
\
    if( n-kn < depth ) {
        cout<<"Your depth doesn't permit your n and kn values. Please try again..."<<endl;
        return 0;
    }

    // print out user-defined data
    cout<<endl<<"-----------------"<<endl;
    cout<<"User Parameters:"<<endl;
    cout<<"Method = "<<method<<" | Depth = "<<depth<<" | Starting span (n) = "<<n<<" | Ending span (kn): "<<kn<<endl;
    cout<<"-----------------"<<endl;

    // First make the 2D vector which is the Slate
    // A slate contans all the n, k1, ... , kn values
    Slate mySlate;
    mySlate.setN(n);
    mySlate.setKn(kn);
    mySlate.setDepth(depth);
    mySlate.makeSlate();
    mySlate.printSlate();

    // for each vector in the Slate, make HEsets.
    for(int i=0; i<mySlate.NKSlate.size(); i++) {
        Stream myStream;
        // there are no private vars in Stream...why??
        myStream.HESet = mySlate.NKSlate[i];
        myStream.depth = depth;
        myStream.method = method;

        int a = 1;
        // set the vector and initialize all its entries to 0...
        vector<int> rList = {};
        for(int i=0; i<= myStream.depth; i++ ) {
            rList.push_back(0);
        };

        // should probably call a different makeSetREC function
        // depending on whether method = r or method = s
        myStream.makeSetREC ( a, rList );

    }
    return 0;
}