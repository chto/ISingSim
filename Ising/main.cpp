#include "lattice.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std; 
int main(int argc, char* argv[]){
    int steps=1E1;
    if (argc < 3){
        cout << "please type size"<<endl; 
        return 0;
    }
    const int ndim = atoi(argv[1]);
    const int size = atoi(argv[2]);
    double T=0.5;
    Lattice lattice=Lattice(ndim,size,T); 
    lattice.runMontecarlo(steps);
    cout << lattice.magnetization()<<endl;
    std::ostringstream ss1;
    ss1<<ndim;
    std::ostringstream ss2;
    ss2<<size;
    std::ostringstream ss3;
    ss3<<T;
    lattice.storenpy(ss1.str()+"_D_"+ss2.str()+"_sides_"+ss3.str()+"_temp.txt");
//    int index[2]={1,1};
//    lattice.updateSystem(index, 0);
//    lattice.printLattice();
/*
    int index[3]={0,0,0};
    vector<int*> result;
    lattice.nestNb(result,index);
    for(int i=0;i<result.size();++i){
        cout<<i<<" "<<result[i][0]<<" "<<result[i][1]<<" "<<result[i][2]<<endl;
        delete[] result[i];
    }
*/    
    return 0;
}
