#include "lattice.h"
using namespace std;

Lattice::Lattice(int ndim, int size, double temp){
    static bool called=false;
    if(not called){
        srand (time(NULL));
        called=true;
    }
    _ndim = Ndim;
    _size = size;
    setTemp(temp);
    //system.resize(_size,ndim);
    cout<<"dim: "<<_ndim<<endl;
    cout<<"size: "<<_size<<endl;
    cout<<"Temp: "<<_T<<endl;
    cout<<"_pBond: "<<_pBond<<endl;
    _initialArray(_ndim,true);
    _initialCluster(_ndim);
}
void Lattice::runMontecarlo_rc(int steps){
    for(int step=0; step<steps;++step){
        std::cout << '\r'<<"Steps: "<<step<<std::flush;
       _resetCluster();
       int randomIndex[_ndim];
       pickRandomPlace(randomIndex);
       growCluster(randomIndex,getSystemValue(randomIndex),0);
    }
    cout<<endl;
}        
void Lattice::runMontecarlo(int steps){
    int* site;
    stack<int*> clusterSites;
    static double norm=1.0/static_cast<double>(RAND_MAX);
    for(int step=0; step<steps;++step){
        std::cout << '\r'<<"Steps: "<<step<<std::flush;
        _resetCluster();
        int randomIndex[Ndim];
        pickRandomPlace(randomIndex);
        int* temp = new int[Ndim];
        for(unsigned int m=0; m<Ndim;++m)
            temp[m]=randomIndex[m];
        clusterSites.push(temp);
        int ClusterSpin=getSystemValue(randomIndex);
        int init=0;
        while(not clusterSites.empty()){
            site=clusterSites.top();
//            cout<<site[0]<<" "<<site[1]<<endl;
            clusterSites.pop();
            if(!getClusterValue(site)){   
               if(getSystemValue(site) == ClusterSpin){
                  double random=norm*static_cast<double>(rand());
               //   cout<<"Random: "<<random<<endl;
                  if ((random<_pBond) || (init==0)){
  //                   cout<<ClusterSpin<<endl;
                     updateCluster(site,true);
                     updateSystem(site,-1*ClusterSpin);
	                  int nearArray[Arraysize][Ndim];
                     nestNb(nearArray,site); 
                     ++init;
                  //   random_shuffle(&nearArray[0], &nearArray[Arraysize]); 
                  //   cout<<"near: ";
                     for(unsigned int i=0;i<Arraysize;i++){
                             int* temp = new int[Ndim];
                             for(unsigned int m=0; m<Ndim;++m)
                                temp[m]=nearArray[i][m];
                             clusterSites.push(temp);
              //            cout<<" ;"<<nearArray[i][0]<<" "<<nearArray[i][1];
                     }
               //      cout<<endl;
                  }
    /*
                  stack<int*> newStack=clusterSites;
                  cout<<"Stack: ";
                  while( !newStack.empty() ) {
                          cout << "; "<<newStack.top()[0] << " "<<newStack.top()[1];
                               newStack.pop(); 
                  }
                  cout<<endl;
     */
               }
               else{
                  ;
           //       cout<<"Rejected system:"<<getSystemValue(site);
           //       cout<<" at: "<<site[0]<<" "<<site[1]<<endl;
               }
            }
            else{
               ;
      //            cout<<"Rejected Cluster:"<<getClusterValue(site)<<" "<<getSystemValue(site);
      //            cout<<" at: "<<site[0]<<" "<<site[1]<<endl;
            }
            delete[] site;
         }
     }
	cout<<endl;
}

void Lattice::growCluster(int* index, int ClusterSpin, int accumulator=0){
    updateCluster(index,true);
    updateSystem(index,-1*ClusterSpin);
    if(accumulator >= 10000)
        return;
	 int nearArray[Arraysize][Ndim];
    nestNb(nearArray,index);
    for(unsigned int i=0;i<Arraysize;++i){
        if (!getClusterValue(nearArray[i]))
            tryAdd(nearArray[i],ClusterSpin, accumulator+1);
    } 

}

void Lattice::tryAdd(int* index, int ClusterSpin, int accumulator=0){
    static double norm=1.0/static_cast<double>(RAND_MAX);
    if(getSystemValue(index) == ClusterSpin)
        if (norm*static_cast<double>(rand())<_pBond)
            growCluster(index,ClusterSpin, accumulator);
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

        for(int i=0;i<_size;++i){
            for (int j=0;j<_size;++j)
                cout<<"cluster: ["<<i<<"] ["<<j<<"]: "<<cluster_2d[i][j]<<endl;
        }
    }
    else return;
}

void Lattice::nestNb(int nearArray[][Ndim], int* index){
    for(int i=0;i<_ndim;++i){
        for (int j=0;j<2;++j){
            for(int w=0;w<_ndim;++w){
                nearArray[i*2+j][w]=index[w];
            }
            if(j==0){
                nearArray[i*2+j][i]-=1;
                if(nearArray[i*2+j][i]<0)
                    nearArray[i*2+j][i]=_size-1;
            }
            else{
                nearArray[i*2+j][i]+=1;
                if(nearArray[i*2+j][i]>_size-1)
                    nearArray[i*2+j][i]=0;
            }
//            cout<<a[0]<<" "<<a[1]<<endl;
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
  ofstream myfile (filename.c_str());
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
