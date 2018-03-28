#include<iostream>
#include<vector>
#include<climits>
using namespace std;

class process
{
public:
    int pId;
    int AT;
    int BT;
    bool complete=false;
};

class finalAns
{
public:
    process p;
    int ST;
    int CT;
    int TAT;
    int WT;
    bool check;
};

class gandt
{
public:
    process p;
    int ST;
    int FT;
};

void sortByArrivalTime(vector<process> & input)
{

    for(int i=0; i<input.size()-1; i++)
    {
        for(int j=0; j<input.size()-1-i; j++)
        {
            if(input[j].AT>input[j+1].AT)
            {
                process temp;
                temp.BT=input[j].BT;
                input[j].BT= input[j+1].BT;
                input[j+1].BT= temp.BT;

                temp.AT=input[j].AT;
                input[j].AT= input[j+1].AT;
                input[j+1].AT= temp.AT;

                temp.pId=input[j].pId;
                input[j].pId= input[j+1].pId;
                input[j+1].pId= temp.pId;
            }
        }
    }

}

void decreaseBT(vector<process> & input,int pId)
{
    for(int i=0; i<input.size(); i++)
    {
        if(input[i].pId==pId)
        {
            input[i].BT=input[i].BT-1;
            if(input[i].BT<=0)
            {
                input[i].complete=true;
            }
            break;
        }
    }
}

process fetchNextProcess(vector<process> input,int t)
{
    process next;
    next.pId=INT_MAX;
    next.AT=INT_MAX;
    next.BT=INT_MAX;

    for(int i=0; i<input.size(); i++)
    {
        if(input[i].complete==false && input[i].AT<=t && input[i].BT<next.BT && input[i].BT>0 )
        {
            next.pId=input[i].pId;
            next.AT=input[i].AT;
            next.BT=input[i].BT;
        }
    }
    return next;
}


bool checkAllComplete(vector<process>input)
{

    bool ans=true;
    for(int i=0; i<input.size(); i++)
    {
        if(input[i].complete!=true)
        {
            return false;
        }
    }
    return ans;

}

int main()
{
    cout<<"Enter the number of processes: ";
    int n;
    cin>>n;
    cout<<endl;
    vector<process> input;
    vector<process>inputCopy;

    for(int i=0; i<n; i++)
    {
        process tempObject;
        cout<<"Enter arrival time for process "<<i+1<<": ";
        cin>>tempObject.AT;
        cout<<endl;
        cout<<"Enter burst time for process "<<i+1<<": ";
        cin>>tempObject.BT;
        cout<<endl;
        tempObject.pId=i+1;
        input.push_back(tempObject);
    }
    for(int i=0; i<input.size(); i++)
    {
        process temp;
        temp.AT=input[i].AT;
        temp.BT=input[i].BT;
        temp.pId=input[i].pId;
        temp.complete=input[i].complete;
        inputCopy.push_back(temp);
    }
    sortByArrivalTime(input);
    sortByArrivalTime(inputCopy);
    int totalTime=0;
    for(int i=0; i<n; i++)
    {
        totalTime+=input[i].BT;
    }
    vector<gandt> gandtChart;
    int t=input[0].AT;
    totalTime+=t;
    process currProcess= input[0];
    bool allComplete=false;
    while(!allComplete)
    {
        gandt temp;
        temp.p=currProcess;
        if(currProcess.BT==INT_MAX)
        {
            t++;
            currProcess=fetchNextProcess(input,t);
            continue;
        }
       // cout<<"current process: "<<currProcess.pId<<endl;
        temp.ST=t;
        temp.FT=++t;

        if(gandtChart.size()!=0 && temp.p.pId==gandtChart[gandtChart.size()-1].p.pId)
        {
            gandtChart[gandtChart.size()-1].FT=temp.FT;
        }
        else
        {
            gandtChart.push_back(temp);

        }
        decreaseBT(input,currProcess.pId);
        currProcess=fetchNextProcess(input,t);
        allComplete=checkAllComplete(input);
    }
   /* cout<<"pId"<<'\t'<<"ST"<<'\t'<<"FT"<<endl;

    for(int i=0; i<gandtChart.size(); i++)
    {

        cout<<gandtChart[i].p.pId<<'\t';
        cout<<gandtChart[i].ST<<'\t';
        cout<<gandtChart[i].FT<<'\t';
        cout<<endl;
    }*/

    vector<finalAns> ans;
    for(int i=0; i<n; i++)
    {
        finalAns temp;
        temp.p.AT=input[i].AT;
        temp.p.BT=inputCopy[i].BT;
        temp.p.pId=input[i].pId;
        temp.CT=-1;
        temp.TAT=-1;
        temp.WT=-1;
        temp.check=false;
        ans.push_back(temp);
    }
    int counter=0;
    for(int i=gandtChart.size()-1; counter<n; i--)
    {
        for(int j=0; j<ans.size(); j++)
        {
            if(ans[j].p.pId==gandtChart[i].p.pId && ans[j].check==false)
            {
                ans[j].CT=gandtChart[i].FT;
                ans[j].check=true;
                counter++;
                break;
            }
        }
    }

    for(int i=0; i<ans.size(); i++)
    {
        ans[i].TAT=ans[i].CT-ans[i].p.AT;
        ans[i].WT=ans[i].TAT-ans[i].p.BT;
    }

    cout<<"P_ID"<<'\t';
    cout<<"AT"<<'\t';
    cout<<"BT"<<'\t';
    cout<<"CT"<<'\t';
    cout<<"TAT"<<'\t';
    cout<<"WT"<<'\t';
    cout<<endl;

    for(int i=0; i<50; i++)
    {
        cout<<'-';
    }
    cout<<endl;


    for(int i=0; i<n; i++)
    {
        cout<<ans[i].p.pId<<'\t';
        cout<<ans[i].p.AT<<'\t';
        cout<<ans[i].p.BT<<'\t';
        cout<<ans[i].CT<<'\t';
        cout<<ans[i].TAT<<'\t';
        cout<<ans[i].WT<<'\t';
        cout<<endl;

        for(int i=0; i<50; i++)
        {
            cout<<'-';
        }
        cout<<endl;
    }




}
