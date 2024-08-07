#include<iostream>
#include<vector>
using namespace std;


class hyperEuclid {
    public:
        vector<int> HESet;
        int depth = HESet.size();
        int a, counter;
        vector<int> rList;
    
    hyperEuclid( int a=1, vector<int> rList={0}, int counter=0 )  {
        this->a = a;
        this->rList = rList;
        this->counter = counter;
    }

    void setDepth(int depth) { this->depth = depth;}

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
            if(a>depth-1) {
                for(int i=0; i<depth+1; i++ ) { 
                    // the vector HESet contains the correct n and kn values
                    // the vector rList contains all the corresponding r values
                    cout<<HESet[i]<<"^";
                    cout<<rList[i]<<" ";
                }
            }
            if( a == depth ) { 
                cout<<endl;
                // this counts only the unique sets
                counter++;
            }
            rList = makeSetREC( a+1, rList );
        }
        return rList;
    }
};

int main() {

    hyperEuclid test1;
    test1.HESet = { 12, 10, 4 };
    test1.setDepth(test1.HESet.size()-1);

    int a = 1;

    // set the vector and initialize all its entries to 0...
    vector<int> rList = {};
    for(int i=0; i<= test1.depth; i++ ) {
        rList.push_back(0);
    };

    test1.makeSetREC( a, rList );
    cout<<endl<<"Unique sets = "<<test1.counter<<endl;
    return 0;
}