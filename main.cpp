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
    double* getListProbability(double arr[],int numAp){
        //double arr[numAp]={0};
        double pi = 0;
        for(int i=0;i<numAp-1;i++){
            arr[i]=generateRandomNumber();
            pi+=arr[i];
        }
        arr[numAp-1]=(1-pi);
        return arr;
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

    double arr[num_ap];
    rm.getListProbability(arr,num_ap);
    for(int i=0;i<num_ap;i++){
        cout << "arr["<<i<<"]="<<arr[i]<<endl;
    }

    return 0;
}
