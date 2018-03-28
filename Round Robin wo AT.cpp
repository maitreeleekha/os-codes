#include<iostream>
#include<vector>
using namespace std;


//global time;
int time=0;
class processParams{
public:
    int pId;
    int BT;
    int CT;
    int TAT;
    int WT;
    bool check=false;
};


void execute(vector<processParams> & input,int i,int tq){

if(input[i].check==true || input[i].BT==0 ){
    input[i].check=true;
    return;
}
else if(input[i].BT-tq>0){
        cout<<i<<"executing"<<endl;
    input[i].BT-=tq;
    time+=tq;
}

else if(input[i].BT-tq<0){
    time+=input[i].BT;
    input[i].BT=0;
    input[i].CT=time;
    input[i].TAT=time;
    input[i].WT= input[i].TAT-input[i].BT;
    input[i].check=true;
cout<<i<<"done"<<endl;
}
}
bool checkAllComplete(vector<processParams> input){

for(int i=0;i<input.size();i++){
    if(input[i].check==false){
        return false;
    }
}
return true;

}

int main()
{
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    vector<processParams> input;
    for(int i=0;i<n;i++){
        processParams temp;
        temp.pId=i+1;
        cout<<"Enter the burst time for process "<<i+1;
        cin>>temp.BT;
        input.push_back(temp);
        cout<<endl;
    }

    vector<processParams> inputcopy = input;
    cout<<"Enter the time quantum ";
    int tq;
    cin>>tq;

    while(!checkAllComplete(input)){
    for(int i=0;i<n;i++){
        processParams curr = input[i];
        execute(input,i,tq);
    }
    if(checkAllComplete(input)){break;}
    }

cout<<"P_ID"<<'\t';
cout<<"BT"<<'\t';
cout<<"CT"<<'\t';
cout<<"TAT"<<'\t';
cout<<"WT"<<'\t';
cout<<endl;
for(int i=0;i<50;i++){
    cout<<'-';
}
cout<<endl;
for(int i=0; i<n; i++)
    {
        cout<<input[i].pId<<'\t';
        cout<<inputcopy[i].BT<<'\t';
        cout<<input[i].CT<<'\t';
        cout<<input[i].TAT<<'\t';
        cout<<input[i].WT<<'\t';
        cout<<endl;

for(int i=0;i<50;i++){
    cout<<'-';
}
cout<<endl;
    }


}

