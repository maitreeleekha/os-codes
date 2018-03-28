#include<iostream>
#include<vector>
using namespace std;

//global time;
int time=0;

class processParams{
public:

    int pId;
    int AT;
    int BT;
    int priority; // lower the priority  number higher the priority
    int CT;
    int TAT;
    int WT;
    bool check=false;
};


processParams fetchProcess(vector<processParams> input){

//min priority number wala process with at<=time
int i=0;
processParams p;
vector<processParams> candidates;
for(i=0;i<input.size();i++){
   if(input[i].AT<=time && input[i].check==false){
    candidates.push_back(input[i]);
   }
}

if(candidates.size()==0){
    processParams temp;
    temp.pId=-1;
    return temp;
}

p=candidates[0];
for(i=0;i<candidates.size();i++){
        if(candidates[i].priority<p.priority){
            p=candidates[i];
        }
}

return p;
}

void execute(vector<processParams> & input, processParams curr){

if(curr.check==true){
    return;
}

//cout<<"execute "<<curr.pId<<endl;
int i;
for(i=0;i<input.size();i++){
    if(input[i].pId== curr.pId){
        break;
    }
}

input[i].BT-=1;
time++;
if(input[i].BT==0){
    input[i].check=true;
    input[i].CT=time;
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

int main(){

int n;
cout<<"Enter the number of processes: ";
cin>>n;
cout<<endl;

vector<processParams> input;

for(int i=0;i<n;i++){
    processParams temp;

    temp.pId=i+1;
    cout<<"Enter the arrival time for process "<<i+1<<':';
    cin>>temp.AT;
    cout<<endl;

    cout<<"Enter the burst time for process "<<i+1<<':';
    cin>>temp.BT;
    cout<<endl;

    cout<<"Enter the priority number for process "<<i+1<<':';
    cin>>temp.priority;
    cout<<endl;

    input.push_back(temp);
}

vector<processParams> inpcpy = input;

//onnput sorted by AT.
while(time<input[0].AT){
    time++;
}
 processParams curr;

while(!checkAllComplete(input)){

curr = fetchProcess(input);
if(curr.pId!=-1){
execute(input,curr);
}

}


 cout<<endl;
    cout<<"pID"<<'\t';
    cout<<"AT"<<'\t';
    cout<<"BT"<<'\t';
    cout<<"pri"<<'\t';
    cout<<"CT"<<'\t';
    cout<<"TAT"<<'\t';
    cout<<"WT"<<'\t';
    cout<<endl;
    for(int j=0; j<60; j++)
    {
        cout<<"-";
    }
    cout<<endl;
    for(int i=0;i<input.size();i++){
        cout<<input[i].pId<<'\t';
        cout<<input[i].AT<<'\t';
        cout<<inpcpy[i].BT<<'\t';
        cout<<input[i].priority<<'\t';
        cout<<input[i].CT<<'\t';
        cout<<input[i].CT-input[i].AT<<'\t';
        cout<<input[i].CT-input[i].AT-inpcpy[i].BT<<endl;
    }
for(int j=0; j<60; j++)
    {
        cout<<"-";
    }
    cout<<endl;
}
