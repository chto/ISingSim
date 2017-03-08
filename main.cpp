#include "lattice.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "common.h"
using namespace std; 
int main(int argc, char* argv[]){
    int steps=1E5;
    if (argc < 4){
        cout << "please type size"<<endl; 
        return 0;
    }
    const int ndim = atoi(argv[1]);
    const int size = atoi(argv[2]);
    double T = atof(argv[3]);
//    int ndim=constants::Ndim;
    Lattice lattice=Lattice(ndim,size,T); 
    /*
    int index[2]={0,0};
    int nearArray[4][2];
    lattice.nestNb(nearArray, index);
    for(int i=0;i<4;++i){
        for(int m=0;m<2;++m){
            cout<<"test";
            cout<<nearArray[i][m]<<endl;
        }
    }
    */
//    lattice.runMontecarlo_rc(steps);
    lattice.runMontecarlo(steps);
    cout << lattice.magnetization()<<endl;
    std::ostringstream ss1;
    ss1<<ndim;
    std::ostringstream ss2;
    ss2<<size;
    std::ostringstream ss3;
    ss3<<T;
    string basedir="./Result/statmechResult/"+ss1.str()+"D/";
    lattice.storenpy(basedir+ss1.str()+"_D_"+ss2.str()+"_sides_"+ss3.str()+"_temp.txt");
//    int index[2]={1,1};
//    lattice.updateSystem(index, 0);
//    lattice.printLattice();
/*
    vector<int*> result;
    lattice.nestNb(result,index);
    for(int i=0;i<result.size();++i){
        cout<<i<<" "<<result[i][0]<<" "<<result[i][1]<<" "<<result[i][2]<<endl;
        delete[] result[i];
    }
*/    
    return 0;
}
