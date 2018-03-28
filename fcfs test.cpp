#include<iostream>
using namespace std;

class process
{
public:
    int pId;
    int AT;
    int BT;
};

class finalAns
{
public:
    process p;
    int ST;
    int CT;
    int TAT;
    int WT;
};

void sortProcessesByAT(process* input,int n)
{
    for(int i=0; i<n; i++)
    {

        for(int j=0; j<n-i-1; j++)
        {

            if(input[j].AT>input[j+1].AT)
            {

                int temp=input[j].pId;
                input[j].pId=input[j+1].pId;
                input[j+1].pId=temp;

                temp=input[j].AT;
                input[j].AT=input[j+1].AT;
                input[j+1].AT=temp;

                temp=input[j].BT;
                input[j].BT=input[j+1].BT;
                input[j+1].BT=temp;
            }
        }
    }

}

int main()
{
    cout<<"Enter the number of processes: ";
    int n;
    cin>>n;

    process * input= new process[n];

    for(int i=0; i<n; i++)
    {
        cout<<"Enter arrival time for process "<<i+1<<" : ";
        cin>>input[i].AT;
        cout<<endl;
        cout<<"Enter burst time for process "<<i+1<<" : ";
        cin>>input[i].BT;
        cout<<endl;
        input[i].pId=i+1;
    }

    sortProcessesByAT(input,n);

    finalAns * ans=new finalAns[n];

    for(int i=0; i<n; i++)
    {

        process currProcess= input[i];
        finalAns tempAns;
        tempAns.p.pId=currProcess.pId;
        tempAns.p.AT=currProcess.AT;
        tempAns.p.BT=currProcess.BT;

        if(i==0)
        {
            tempAns.ST=currProcess.AT;
        }
        else if(ans[i-1].CT<currProcess.AT)
        {
            tempAns.ST=currProcess.AT;
        }
        else if(ans[i-1].CT>currProcess.AT)
        {
            tempAns.ST=ans[i-1].CT;
        }

        tempAns.CT= tempAns.ST+tempAns.p.BT;
        tempAns.TAT=tempAns.CT-tempAns.p.AT;
        tempAns.WT=tempAns.TAT-tempAns.p.BT;

        ans[i]=tempAns;
    }


    cout<<endl;
    cout<<"pID"<<'\t';
    cout<<"AT"<<'\t';
    cout<<"BT"<<'\t';
    cout<<"CT"<<'\t';
    cout<<"TAT"<<'\t';
    cout<<"WT"<<'\t';
    cout<<endl;
    for(int j=0; j<60; j++)
    {
        cout<<"-";
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
        for(int j=0; j<60; j++)
        {
            cout<<"-";
        }
        cout<<endl;
    }


    return 0;

}
