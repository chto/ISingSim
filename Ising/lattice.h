#ifndef LATTICE_H
#define LATTICE_H
#include <cmath>
#include <vector>
#include <cmath>
#include <map>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
using namespace std;
class Lattice{
public:
    Lattice(int , int , double);
    void setTemp(double T);
    void nestNb(vector<int*>& nearArray,int* index); 
    void updateSystem(int*, int);
    void updateCluster(int* , bool );
    void printLattice();
    bool getClusterValue(int* );
    int getSystemValue(int* );
    void pickRandomPlace(int []);
    void runMontecarlo(int);
    void growCluster(int* , int);
    void tryAdd(int* , int);
//    double susceptibility();
    double magnetization();
//    double correlationLength();
    void storenpy(string);
private:
    void _initialArray(int, bool);
    void _initialCluster(int);
    void _resetCluster();
    int _ndim;
    int _size;
    double _T;
    double _pBond;

    int** system_2d;
    int*** system_3d;
    int**** system_4d;
    int***** system_5d;

    bool** cluster_2d;
    bool*** cluster_3d;
    bool**** cluster_4d;
    bool***** cluster_5d;
};



#endif

