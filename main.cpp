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
                double x = generateRandomNumber();
                if(x!=0){
                    U*=x;
                }
                else{
                    do{
                        x = generateRandomNumber();;
                    }while(x==0);
                    U*=x;
                }
            	
        	}
           // cout << "shape="<<shape<<" U="<< U<<endl;
        	return U;
	}
    public:
    Random();
    int chooseAPRandom(double arr[],int numAp){
        int index = -1;
        double rm = generateRandomNumber();
       // cout << "rm=" <<rm<<endl;
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
       // cout<< "n="<<n<<endl;
        double U = calculatePI(n);
        double rm = (-1/lamda)*log(U);
       // cout << "U="<<U <<" rm="<<rm <<endl;
        return rm;
    }
};
Random::Random(){
    time_t t;
	srand((unsigned) time(&t)+rand());
}

int FindMinIndex(double list[],int size){
    double min = list[0];
    int index = 0;
    for(int i=0;i<size;i++)
    {
        if(min>list[i]){
            min = list[i];
            index = i;
        }
    }
    return index;
}

int main(int argc, char *argv[]) {
    int num_ap = 5;
    int N_Simulation = 100;
    double file_size = 5; // Mbyte
    double bandwidth[num_ap] = {10,50,150,300,500};
    double count1[num_ap] = {0};
    double count2[num_ap] = {0};
    double ti1[num_ap]={0};
    double ti2[num_ap]={0};
    //cout << "hello new project" << endl;
    cout << "file_size = " << file_size << "Mbyte" <<endl;
    cout << "Bandwidth : " ;
    for(int i=0;i<num_ap;i++)
    {
        cout << "B["<<i<<"]=" <<bandwidth[i] << "MB/s ";
    }
    cout << endl;
    Random rm;

    double popsum  = 1;

    double arr[num_ap]={0};
    double lamda[num_ap]={0};
    double ni[num_ap]={0};
    double Eni[num_ap]={0};
    // generate poisson random number...
    
    for(int n=0;n<N_Simulation;n++)
    {
        cout << "# of people used : ";
        for(int i=0;i<num_ap;i++)
        {
            lamda[i] = (double)(bandwidth[i]/file_size);
            ni[i] = rm.poissonRandomNumber(lamda[i]);
            Eni[i]+=ni[i];
            cout <<" AP"<<i<<"="<<ni[i];
        }
        cout << endl;
        //rm.getListProbability(arr,num_ap);

        // without wifi selection
        cout << "************** Without WIFI Selection **************" <<endl; 
        arr[0]= double(popsum/num_ap);
       // cout << "arr[0]="<<arr[0]<<endl;
        for(int i=1;i<num_ap;i++)
        {
            arr[i]=arr[i-1]+ double(popsum/num_ap);
         //cout << "arr["<<i<<"]="<<arr[i]<<endl;
        }

        int index  = rm.chooseAPRandom(arr,num_ap);
        cout << "Select WIFI AP = " << index << endl;
        count1[index]+=1;
        //generate ti
        //cout << lamda[index] <<endl;
        double ti = rm.erlangRandomnumber(lamda[index],ni[index]+1);
        cout << "download time ti = " << ti << endl;
        ti1[index]+=ti;
        cout << "************** With WIFI Selection **************" <<endl; 
        //calculate min E[Ti]
        cout << "Expected download time =";
        double eti[num_ap]={0};
        for(int i=0;i<num_ap;i++)
        {
            eti[i]=(ni[i]+1)/lamda[i];
            cout << " eti["<< i << "]="<<eti[i];
        }
        cout << endl;
        int selectwifi = FindMinIndex(eti,num_ap);
        cout << "Select WIFI AP = " << selectwifi << endl;
        count2[selectwifi]+=1;
        double sti = rm.erlangRandomnumber(lamda[selectwifi],ni[selectwifi]+1);
        cout << "download time ti = " << sti << endl;
        ti2[selectwifi]+=sti;
    }
    cout << "***********Simulation result****************"<<endl;
    cout << "Simulation rounds =" << N_Simulation <<endl;
    cout << "----- Average # of user E[ni] -----" <<endl;
    for(int i=0;i<num_ap;i++){
        double Ani = (double)(Eni[i]/N_Simulation);
        cout << "E[n"<<i<<"]="<<Ani << " ";
    }
    cout <<endl;
    cout << "==== without selection ====" <<endl;
    cout << "# of people for ";
    for(int i=0;i<num_ap;i++)
    {
        cout <<"AP["<<i<<"]="<<count1[i]<<" ";
    }
    cout <<endl;
    cout << "Propability : " << endl;
    for(int i=0;i<num_ap;i++)
    {
        double p = (double)(count1[i]/N_Simulation);
        double eti = (double)(ti1[i]/N_Simulation);
        cout <<"P[AP"<<i<<"]="<<p<< " E[t"<<i<<"]="<<eti<<endl;
    }
    cout << "==== with selection ====" <<endl;
    cout << "# of people for ";
    for(int i=0;i<num_ap;i++)
    {
        cout <<"Select AP["<<i<<"]="<<count2[i]<<" ";
    }
    cout <<endl;
    for(int i=0;i<num_ap;i++)
    {
        double p = (double)(count2[i]/N_Simulation);
        double eti = (double)(ti2[i]/N_Simulation);
        cout <<"P[AP"<<i<<"]="<<p<< " E[t"<<i<<"]="<<eti<<endl;
    }

    return 0;
}
