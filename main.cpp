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
};
Random::Random(){
    time_t t;
	srand((unsigned) time(&t)+rand());
}

int main(int argc, char *argv[]) {
    int num_ap = 5;
    cout << "hello new project" << endl;
    Random rm;

    double popsum  = 1;

    double arr[num_ap];
    //rm.getListProbability(arr,num_ap);
   
    arr[0]= double(popsum/num_ap);
    cout << "arr[0]="<<arr[0]<<endl;
    for(int i=1;i<num_ap;i++){
        arr[i]=arr[i-1]+ double(popsum/num_ap);
        cout << "arr["<<i<<"]="<<arr[i]<<endl;
    }
    for(int i=0;i<10;i++)
    {
        int index  = rm.chooseAPRandom(arr,num_ap);
        cout << "index = " << index << endl;
    }

    return 0;
}
