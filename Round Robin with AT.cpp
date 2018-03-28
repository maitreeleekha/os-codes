#include<iostream>
#include<vector>
#include<queue>
using namespace std;


//global time;
int time=0;

class processParams
{
public:
    int pId;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    bool check=false;
};


sortBtArrivalTime(vector<processParams> & input)
{

    for(int i=0; i<input.size(); i++)
    {
        for(int j=0; j<input.size()-i-1; j++)
        {
            if(input[j].AT>input[j+1].AT)
            {
                processParams temp;
                temp.AT=input[j].AT;
                input[j].AT = input[j+1].AT;
                input[j+1].AT = temp.AT;

                temp.BT=input[j].BT;
                input[j].BT = input[j+1].BT;
                input[j+1].BT = temp.BT;

                temp.pId=input[j].pId;
                input[j].pId = input[j+1].pId;
                input[j+1].pId = temp.pId;
            }

        }
    }


}

bool executeCurrProcess(processParams & curr, vector<processParams> & input,int tq)
{
    bool flag;
    cout<<"executing: "<<curr.pId<<endl;
    for(int i=0; i<input.size(); i++)
    {
        if(input[i].pId==curr.pId)
        {

            if(input[i].BT==0){
                return true;
            }
            if(input[i].BT-tq>0)
            {
                input[i].BT-=tq;
                curr.BT-=tq;
                time+=tq;
                flag=false;//incomplete and push again;
            }
            else if(input[i].BT-tq<=0)
            {
                time+=input[i].BT;
                input[i].BT=0;
                curr.BT=0;
                input[i].check=true;
                curr.check=true;
                input[i].CT=time;
                input[i].TAT= input[i].CT-input[i].AT;
                //input[i].WT = input[i].TAT- input[i].BT;
                flag=true;//complete and do not push again

            }

            break;
        }


    }
    return flag;
}

void pushArrivedProcesses(vector<processParams> input, queue<processParams> & rrobin, int prevTime)
{

    for(int i=0; i<input.size(); i++)
    {

        if(input[i].AT>prevTime && input[i].AT<=time)
        {
            rrobin.push(input[i]);
        }
    }
    return;

}

void checkForNewProcess(vector<processParams> input,queue<processParams> & rrobin)
{
    for(int i=0; i<input.size(); i++)
    {
        if(input[i].AT==time && input[i].check==false)
        {
            rrobin.push(input[i]);
        }
    }
}

bool checkAllComplete(vector<processParams> input)
{

    for(int i=0; i<input.size(); i++)
    {
        if(input[i].check==false)
        {
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
    vector<processParams> inpcpy;
    for(int i=0; i<n; i++)
    {
        processParams temp;
        temp.pId=i+1;
        cout<<"Enter the arrival time for process "<<i+1;
        cin>>temp.AT;
        cout<<endl;
        cout<<"Enter the burst time for process "<<i+1;
        cin>>temp.BT;
        input.push_back(temp);
        inpcpy.push_back(temp);
        cout<<endl;
    }

    cout<<"Enter the time quantum ";
    int tq;
    cin>>tq;
    //  sortByArrivalTime(input);
    int startTime = input[0].AT;
    queue<processParams> rrobin;
    rrobin.push(input[0]);
    int prevTime;
    while(!checkAllComplete(input))
    {
        prevTime = time;
        if(rrobin.empty())
        {
            time++;
            checkForNewProcess(input,rrobin);
            continue;
        }
        processParams curr = rrobin.front();
        rrobin.pop();
        bool check =  executeCurrProcess(curr,input,tq);
        pushArrivedProcesses(input,rrobin,prevTime);

        if(check==false)
        {
            rrobin.push(curr);

        }
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
        cout<<input[i].pId<<'\t';
        cout<<input[i].AT<<'\t';
        cout<<inpcpy[i].BT<<'\t';
        cout<<input[i].CT<<'\t';
        cout<<input[i].TAT<<'\t';
        cout<<input[i].TAT-inpcpy[i].BT<<'\t';
        cout<<endl;

        for(int i=0; i<50; i++)
        {
            cout<<'-';
        }
        cout<<endl;
    }









}
