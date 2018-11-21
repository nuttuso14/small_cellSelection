#include <iostream>
#include <cstdio>
#include <time.h> 
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> // setprecision
#include <vector>

using namespace std;

class Random{
    private:
    double generateRandomNumber(){
        return ((double) rand() / (RAND_MAX));
    }
    double calculatePI(int shape){
			double U = 1;
        	for(int i=0;i<shape;i++){
            	U*=generateRandomNumber();
        	}
        	return U;
	}
    public:
    Random();
    int chooseAPRandom(double arr[],int numAp){
        int index = -1;
        double rm = generateRandomNumber();
        cout << "rm=" <<rm<<endl;
        if(rm<arr[0])
        {
            index = 0;
        }
        else{
            for(int i=1;i<numAp;i++)
            {
                if(rm>=arr[i-1] && rm<=arr[i])
                {
                    index = i;
                }
           
            }
        }
        return index;
    }
    int poissonRandomNumber(double lamda){
        int X=-1;
        double U =generateRandomNumber();
        double p=exp(-1*lamda), f=p;
        int i=0;
        do{
    
            if(U<f){
                //x=i;
                break;
            }
            p = (lamda*p)/(i+1);
            f = f+p;
            i++;
        }while(U>=f);
        X=i;
        return X;
    }
    double erlangRandomnumber(double lamda,int n){
         return (-1/lamda)*log(calculatePI(n));
    }
};
Random::Random(){
    time_t t;
	srand((unsigned) time(&t)+rand());
}

int main(int argc, char *argv[]) {
    int num_ap = 5;
    double file_size = 5; // Mbyte
    double bandwidth[num_ap] = {10,50,150,300,500};
    cout << "hello new project" << endl;
    cout << "file_size = " << file_size <<endl;
    Random rm;

    double popsum  = 1;

    double arr[num_ap];
    double lamda[num_ap];
    double ni[num_ap];
    // generate poisson random number...
    for(int i=0;i<num_ap;i++)
    {
        lamda[i] = (double)(bandwidth[i]/file_size);
        ni[i] = rm.poissonRandomNumber(lamda[i]);
        cout <<"AP"<<i<<"="<<ni[i]<< endl;
    }

    //rm.getListProbability(arr,num_ap);

   // without wifi selection
    arr[0]= double(popsum/num_ap);
    cout << "arr[0]="<<arr[0]<<endl;
    for(int i=1;i<num_ap;i++){
        arr[i]=arr[i-1]+ double(popsum/num_ap);
       // cout << "arr["<<i<<"]="<<arr[i]<<endl;
    }

    int index  = rm.chooseAPRandom(arr,num_ap);
    cout << "Select WIFI AP = " << index << endl;

    //generate ti
    double ti = rm.erlangRandomnumber(lamda[index],ni[index]+1);
    cout << "download time ti = " << ti << endl;

    return 0;
}
