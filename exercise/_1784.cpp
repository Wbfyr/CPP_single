#include<iostream>
using namespace std;


    int map[9][9];

int main(){

    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j) cin>>map[i][j];
    }
    void solute(int &mapvalue,int i,int j);
    
    
}

void solute(int &mapvalue,int i,int j){

        if(mapvalue==0){
            for(int k=1;k<10;++k){
                mapvalue=k;
                bool flag=0;
                for(int u=0;u<9;++u){
                    if(mapvalue==map[i][u]) {
                        flag=1;
                        break;
                    }
                if(flag==1) continue;
                for(int u=0;u<9;++u){
                    if(mapvalue==map[u][j]) {
                        flag=1;
                        break;
                    }
                if(flag==1) continue;
                for(int u=0;u<9;++u){
                    if(mapvalue==map[u][j]) {
                        flag=1;
                        break;
                    }
                if(flag==1) continue;
                int s=i%3,t=j%3;
                switch (s)
                {
                case 0:
                    switch (t)
                    {
                    case 0:
                        for(int u=0;u<3;++u){
                            for(int v=0;v<3;++v){
                                if(u==0&&v==0) continue;
                                if(mapvalue==map[i-u][j-v]) {
                                    flag=1;
                                    break;
                                }
                            }
                            if(flag==1) break;
                        }
                        break;
                    case 1:
                        for(int u=-1;u<2;++u){
                            for(int v=-1;v<2;++v){
                                if(u==0&&v==0) continue;
                                if(mapvalue==map[i-u][j-v]) {
                                    flag=1;
                                    break;
                                }
                            }
                            if(flag==1) break;
                        }
                        break;
                    case 2:
                        for(int u=-2;u<1;++u){
                            for(int v=-2;v<1;++v){
                                if(u==0&&v==0) continue;
                                if(mapvalue==map[i-u][j-v]) {
                                    flag=1;
                                    break;
                                }
                            }
                            if(flag==1) break;
                        }
                        break;
                    }
                    break;
                
                default:
                    break;
                }
                }
            }
        }
    }}}