#include<iostream>
#include<queue>
using namespace std;

class processParas
{
public:
    int AT;
    int BT;
};

class finalAns
{
public:
    processParas p;
    int ST;
    int CT;
    int TAT;
    int WT;
};


void sortJobsAccordingToAT(queue<processParas> & processes){
vector<processParas> ans;

while(processes.size()!=0){
   processParas curr= processes.front();
   processes.pop();
   ans.push_back(curr);
}

    for(int i=0;i<ans.size()-1;i++){
        for(int j=0;j<ans.size()-i-1;j++){
            if(ans[j].AT>ans[j+1].AT){

                processParas temp;
                temp.AT=ans[j].AT;
                temp.BT=ans[j].BT;
                ans[j].AT=ans[j+1].AT;
                ans[j].BT=ans[j+1].BT;
                ans[j+1].AT=temp.AT;
                ans[j+1].BT=temp.BT;

            }
        }
    }

    for(int i=0;i<ans.size();i++){
        processes.push(ans[i]);
    }
}




int main()
{
    queue<processParas> programQueue;
    int n;
    cout<<"enter the number of processes"<<'\t';
    cin>>n;
    cout<<endl;

    for(int i=0; i<n; i++)
    {
        processParas obj;
        cout<<"enter arrival time for process "<<i+1<<"   ";
        cin>>obj.AT;
        cout<<endl;
        cout<<"enter burst time for process   "<<i+1<<"   ";
        cin>>obj.BT;
        cout<<endl;
        programQueue.push(obj);

    }
    sortJobsAccordingToAT(programQueue);
    vector<finalAns> ans;

    while(programQueue.size()!=0)
    {

        processParas currProcess = programQueue.front();
        programQueue.pop();

        finalAns currAns;
        currAns.p.AT=currProcess.AT;
        currAns.p.BT = currProcess.BT;

        if(ans.size()==0){

            currAns.ST=currAns.p.AT;
        }

        else if(ans.size()!=0 && ans[ans.size()-1].CT<currProcess.AT)
        {
            currAns.ST=currAns.p.AT;
        }
        else if(ans.size()!=0 && ans[ans.size()-1].CT>currProcess.AT)
        {
            currAns.ST=ans[ans.size()-1].CT;
        }
        currAns.CT=currAns.ST+currAns.p.BT;
        currAns.TAT=currAns.CT-currAns.p.AT;
        currAns.WT= currAns.TAT-currAns.p.BT;

        ans.push_back(currAns);
    }



    cout<<"P_ID"<<'\t';
    cout<<"AT"<<'\t';
    cout<<"BT"<<'\t';
    cout<<"CT"<<'\t';
    cout<<"TAT"<<'\t';
    cout<<"WT"<<'\t';
    cout<<endl;
    for(int j=0;j<50;j++){
            cout<<'-';
        }
    cout<<endl;
    for(int i=0; i<ans.size(); i++)
    {
        cout<<i+1<<'\t';
        cout<<ans[i].p.AT<<'\t';
        cout<<ans[i].p.BT<<'\t';
        cout<<ans[i].CT<<'\t';
        cout<<ans[i].TAT<<'\t';
        cout<<ans[i].WT<<'\t';
        cout<<endl;
        for(int j=0;j<50;j++){
            cout<<'-';
        }cout<<endl;
    }

}
