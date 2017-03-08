#include "lattice.h"
using namespace std;

Lattice::Lattice(int ndim, int size, double temp){
    static bool called=false;
    if(not called){
        srand (time(NULL));
        called=true;
    }
    _ndim = ndim;
    _size = size;
    setTemp(temp);
    //system.resize(_size,ndim);
    cout<<"dim: "<<_ndim<<endl;
    cout<<"size: "<<_size<<endl;
    cout<<"Temp: "<<_T<<endl;
    cout<<"_pBond: "<<_pBond<<endl;
    _initialArray(ndim,false);
    _initialCluster(ndim);
}

void Lattice::runMontecarlo(int steps){
    for(int step=0; step<steps;++step){
        std::cout << '\r'<<"Steps: "<<step<<std::flush;
       _resetCluster(); 
       int randomIndex[_ndim];
       pickRandomPlace(randomIndex);
       /*
       cout<<"run"<<endl;
       for(int i=0; i<_ndim; ++i){
            cout<<randomIndex[i]<<" ";
       }
       cout<<endl;
       */
       growCluster(randomIndex,getSystemValue(randomIndex));
    }
	cout<<endl;
}

void Lattice::growCluster(int* index, int ClusterSpin){
    updateCluster(index,true);
    updateSystem(index,-1*ClusterSpin);
    vector<int*> nearArray;
    nestNb(nearArray,index); 
    /*
    for(int i=0;i<nearArray.size();++i){
        cout<<"Index "<<i<<" : ";
        for (int j=0;j<_ndim;++j){
            cout<<nearArray[i][j]<<" ";
        }
        cout<<endl;
        delete[] nearArray[i];
    }
    */
    for(int i=0;i<nearArray.size();++i){
        if (!getClusterValue(nearArray[i]))
            tryAdd(nearArray[i],ClusterSpin);
        delete[] nearArray[i];
    }
	
}

void Lattice::tryAdd(int* index, int ClusterSpin){
    static double norm=1.0/static_cast<double>(RAND_MAX);
    if(getSystemValue(index) == ClusterSpin)
        if (norm*static_cast<double>(rand())<_pBond)
            growCluster(index,ClusterSpin);
}

void Lattice::setTemp(double T){
    _T=T;
    _pBond=1-exp(-1.0/_T);
}
bool Lattice::getClusterValue(int* ind){
    if(_ndim==2) return cluster_2d[ind[0]][ind[1]];
    if(_ndim==3) return cluster_3d[ind[0]][ind[1]][ind[2]];
    if(_ndim==4) return cluster_4d[ind[0]][ind[1]][ind[2]][ind[3]];
    if(_ndim==5) return cluster_5d[ind[0]][ind[1]][ind[2]][ind[3]][ind[4]];
    else{
        cerr<<"something is not right"<<endl;
        return false;
    }
}
int Lattice::getSystemValue(int* ind){
    if(_ndim==2) return system_2d[ind[0]][ind[1]];
    if(_ndim==3) return system_3d[ind[0]][ind[1]][ind[2]];
    if(_ndim==4) return system_4d[ind[0]][ind[1]][ind[2]][ind[3]];
    if(_ndim==5) return system_5d[ind[0]][ind[1]][ind[2]][ind[3]][ind[4]];
    else{
        cerr<<"something is not right"<<endl;
        return false;
    }
}


void Lattice::updateSystem(int* ind, int value){
    if (_ndim==2) system_2d[ind[0]][ind[1]]=value;
    if (_ndim==3){
        system_3d[ind[0]][ind[1]][ind[2]]=value;
    }
    if (_ndim==4){
        system_4d[ind[0]][ind[1]][ind[2]][ind[3]]=value;
    }
    if (_ndim==5){
        system_5d[ind[0]][ind[1]][ind[2]][ind[3]][ind[4]]=value;
    }
}
void Lattice::updateCluster(int* ind, bool value){
    if (_ndim==2) cluster_2d[ind[0]][ind[1]]=value;
    if (_ndim==3){
        cluster_3d[ind[0]][ind[1]][ind[2]]=value;
    }
    if (_ndim==4){
        cluster_4d[ind[0]][ind[1]][ind[2]][ind[3]]=value;
    }
    if (_ndim==5){
        cluster_5d[ind[0]][ind[1]][ind[2]][ind[3]][ind[4]]=value;
    }
}
void Lattice::printLattice(){
    if(_ndim==2){
        for(int i=0;i<_size;++i){
            for (int j=0;j<_size;++j)
                cout<<"lattice: ["<<i<<"] ["<<j<<"]: "<<system_2d[i][j]<<endl;
        }
    }
    else return;
}

void Lattice::nestNb(vector<int*>& nearArray, int* index){
    for(int i=0;i<_ndim;++i){
        for (int j=0;j<2;++j){
            int* a=new int[_ndim];
            for(int w=0;w<_ndim;++w){
                a[w]=index[w];
            }
            if(j==0){
                a[i]-=1;
                if(a[i]<0)
                    a[i]=_size-1;
            }
            else{
                a[i]+=1;
                if(a[i]>_size-1)
                    a[i]=0;
            }
//            cout<<a[0]<<" "<<a[1]<<endl;
            nearArray.push_back(a);
       }
    }

}




void Lattice::_initialArray(int ndim, bool random=false){
    if(ndim==2){
        system_2d = new int*[_size]; 
        for(int i =0; i< _size;++i){
            system_2d[i] = new int[_size];
            for(int j=0;j<_size;++j){
                int a;
                if(random)
                     a = rand()%2;
                else
                     a=1;
                if(a == 0) a=-1;
                system_2d[i][j]=a;
            }
        }
    }
    if(ndim==3){
        system_3d = new int**[_size]; 
        for(int i =0; i< _size;++i){
            system_3d[i]=new int*[_size];
            for(int j=0; j< _size;++j){
                system_3d[i][j] =new int[_size];
                for(int k=0;k<_size;++k){
                    int a;
                    if(random)
                         a = rand()%2;
                    else
                         a=1;
                    if(a==0) a=-1;
                    system_3d[i][j][k] = a;
                }
            }
        }
    }
    if(ndim==4){
        system_4d = new int***[_size]; 
        for(int i =0; i< _size;++i){
            system_4d[i]=new int**[_size];
            for(int j=0; j< _size;++j){
                system_4d[i][j] =new int*[_size];
                for(int k=0;k<_size;++k){
                    system_4d[i][j][k] =new int[_size];
                    for(int w=0;w<_size;++w){
                        int a;
                        if(random)
                            a = rand()%2;
                        else
                            a=1;
                        if(a==0) a=-1;
                        system_4d[i][j][k][w]=a;
                    }
                }
            }
        }
    }
    if(ndim==5){
        system_5d = new int****[_size]; 
        for(int i =0; i< _size;++i){
            system_5d[i]=new int***[_size];
            for(int j=0; j< _size;++j){
                system_5d[i][j] =new int**[_size];
                for(int k=0;k<_size;++k){
                    system_5d[i][j][k] =new int*[_size];
                    for(int w=0;w<_size;++w){
                        system_5d[i][j][k][w]= new int[_size];
                        for(int m=0;m<_size;++m){
                            int a;
                            if(random)
                                a = rand()%2;
                            else
                                a=1;
                            if(a==0) a=-1;
                            system_5d[i][j][k][w][m]=a;
                        }
                    }
                }
            }
        }
    }
}
void Lattice::_initialCluster(int ndim){
    if(ndim==2){
        cluster_2d = new bool*[_size]; 
        for(int i =0; i< _size;++i){
            cluster_2d[i] = new bool[_size];
            for(int j=0;j<_size;++j)
                cluster_2d[i][j]=false;
        }
    }
    if(ndim==3){
        cluster_3d = new bool**[_size]; 
        for(int i =0; i< _size;++i){
            cluster_3d[i]=new bool*[_size];
            for(int j=0; j< _size;++j){
                cluster_3d[i][j] =new bool[_size];
                for(int k=0;k<_size;++k){
                    cluster_3d[i][j][k] = false;
                }
            }
        }
    }
    if(ndim==4){
        cluster_4d = new bool***[_size]; 
        for(int i =0; i< _size;++i){
            cluster_4d[i]=new bool**[_size];
            for(int j=0; j< _size;++j){
                cluster_4d[i][j] =new bool*[_size];
                for(int k=0;k<_size;++k){
                    cluster_4d[i][j][k] =new bool[_size];
                    for(int w=0;w<_size;++w){
                        cluster_4d[i][j][k][w]=false;
                    }
                }
            }
        }
    }
    if(ndim==5){
        cluster_5d = new bool****[_size]; 
        for(int i =0; i< _size;++i){
            cluster_5d[i]=new bool***[_size];
            for(int j=0; j< _size;++j){
                cluster_5d[i][j] =new bool**[_size];
                for(int k=0;k<_size;++k){
                    cluster_5d[i][j][k] =new bool*[_size];
                    for(int w=0;w<_size;++w){
                        cluster_5d[i][j][k][w]= new bool[_size];
                        for(int m=0;m<_size;++m){
                        cluster_5d[i][j][k][w][m]=false;
                        }
                    }
                }
            }
        }
    }
}
void Lattice::_resetCluster(){
    if(_ndim==2){
        for(int i =0; i< _size;++i){
            for(int j=0;j<_size;++j)
                cluster_2d[i][j]=false;
        }
    }
    if(_ndim==3){
        for(int i =0; i< _size;++i){
            for(int j=0; j< _size;++j){
                for(int k=0;k<_size;++k){
                    cluster_3d[i][j][k] = false;
                }
            }
        }
    }
    if(_ndim==4){
        for(int i =0; i< _size;++i){
            for(int j=0; j< _size;++j){
                for(int k=0;k<_size;++k){
                    for(int w=0;w<_size;++w){
                        cluster_4d[i][j][k][w]=false;
                    }
                }
            }
        }
    }
    if(_ndim==5){
        for(int i =0; i< _size;++i){
            for(int j=0; j< _size;++j){
                for(int k=0;k<_size;++k){
                    for(int w=0;w<_size;++w){
                        for(int m=0;m<_size;++m){
                        cluster_5d[i][j][k][w][m]=false;
                        }
                    }
                }
            }
        }
    }
}

void Lattice::pickRandomPlace(int index[]){
    if(_ndim==2){
        index[0]=rand()%_size; index[1]=rand()%_size;
    }
    if(_ndim==3){
        index[0]=rand()%_size; index[1]=rand()%_size;index[2]=rand()%_size; 
    }
    if(_ndim==4){
        index[0]=rand()%_size; index[1]=rand()%_size; index[2]=rand()%_size; index[3]=rand()%_size; 
    }
    if(_ndim==5){
        index[0]=rand()%_size; index[1]=rand()%_size,index[2]=rand()%_size;index[3]=rand()%_size;index[4]=rand()%_size; 
     }   
}

double Lattice::magnetization(){
    double mag=0.0;
    if(_ndim==2){
        for(int i =0; i< _size;++i){
            for(int j=0;j<_size;++j){
                mag+=system_2d[i][j];
            }
        }
    }
    if(_ndim==3){
        for(int i =0; i< _size;++i){
            for(int j=0; j< _size;++j){
                for(int k=0;k<_size;++k){
                    mag+=system_3d[i][j][k];
                }
            }
        }
    }
    if(_ndim==4){
        for(int i =0; i< _size;++i){
            for(int j=0; j< _size;++j){
                for(int k=0;k<_size;++k){
                    for(int w=0;w<_size;++w){
                        mag+=system_4d[i][j][k][w];
                    }
                }
            }
        }
    }
    if(_ndim==5){
        for(int i =0; i< _size;++i){
            for(int j=0; j< _size;++j){
                for(int k=0;k<_size;++k){
                    for(int w=0;w<_size;++w){
                        for(int m=0;m<_size;++m){
                            mag+=system_5d[i][j][k][w][m];
                        }
                    }
                }
            }
        }
    }
//   cout<<mag<<endl;
    mag /= pow(_size,_ndim);
    return mag;
}
   
void Lattice::storenpy(string filename){
  ofstream myfile (filename);
  if (myfile.is_open())
  {
    if(_ndim==2){
        for(int i =0; i< _size;++i){
            for(int j=0;j<_size;++j){
                myfile<<i<<" "<<j<<" "<<system_2d[i][j]<<"\n";
            }
        }
    }
    if(_ndim==3){
        for(int i =0; i< _size;++i){
            for(int j=0; j< _size;++j){
                for(int k=0;k<_size;++k){
                    myfile<<i<<" "<<j<<" "<<k<<" "<<system_3d[i][j][k]<<"\n";
                }
            }
        }
    }
    if(_ndim==4){
        for(int i =0; i< _size;++i){
            for(int j=0; j< _size;++j){
                for(int k=0;k<_size;++k){
                    for(int w=0;w<_size;++w){
                        myfile<<i<<" "<<j<<" "<<k<<" "<<w<<" "<<system_4d[i][j][k][w]<<"\n";
                    }
                }
            }
        }
    }
    if(_ndim==5){
        for(int i =0; i< _size;++i){
            for(int j=0; j< _size;++j){
                for(int k=0;k<_size;++k){
                    for(int w=0;w<_size;++w){
                        for(int m=0;m<_size;++m){
                        	myfile<<i<<" "<<j<<" "<<k<<" "<<w<<" "<<m<<" "<<system_5d[i][j][k][w][m]<<"\n";
                        }
                    }
                }
            }
        }
    }
   }
   else cout << "Unable to open file";
 
}
//double Lattice::susceptibility()
//double Lattice::correlationLength()
