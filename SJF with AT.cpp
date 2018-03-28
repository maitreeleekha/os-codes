#include<iostream>
#include<climits>
using namespace std;


class process
{
public:
    int pId;
    int AT;
    int BT;
    bool flag=true;
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
void sortProcessByAT(process* input,int n)
{
    process firstProcess=input[0];
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
    // return firstProcess;
}



void sortByBT(process * input, int start,int n)
{

    for(int i=start; i<n; i++)
    {
        for(int j=start; j<n-i-1; j++)
        {
            if(input[j].BT>input[j+1].BT)
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

process getNextProcess(process * input, int start, int n, int prevCT)
{

    process shortestJob=input[start];
    int index=start;
    for(int i=1; i<n; i++)
    {
        if(input[i].AT>prevCT)
        {
            break;
        }
        if(input[i].flag==true && input[i].BT<shortestJob.BT)
        {
            shortestJob.AT=input[i].AT;
            shortestJob.pId=input[i].pId;
            shortestJob.BT=input[i].BT;
            index=i;
        }
    }
    input[index].BT=INT_MAX;

    return shortestJob;
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

    sortProcessByAT(input,n);



    finalAns * ans=new finalAns[n];
//process firstProcess=minATprocess(input,n);
    process currProcess;
    for(int i=0; i<n; i++)
    {
        finalAns temp;
        if(i==0)
        {
            temp.p.AT=input[i].AT;
            temp.p.BT=input[i].BT;
            temp.p.pId=input[i].pId;
            temp.ST=input[i].AT;
            temp.CT= temp.ST+temp.p.BT;
            temp.TAT= temp.CT-temp.p.AT;
            temp.WT=temp.TAT-temp.p.BT;
            ans[i]=temp;
            currProcess=getNextProcess(input,i+1,n,temp.CT);
        }

        else
        {
            temp.p.AT= currProcess.AT;
            temp.p.BT= currProcess.BT;
            temp.p.pId= currProcess.pId;

            if(currProcess.AT>ans[i-1].CT)
            {
                temp.ST=currProcess.AT;

            }
            else
            {
                temp.ST=ans[i-1].CT;
            }



            temp.CT=temp.ST+currProcess.BT;
            temp.TAT=temp.CT-temp.p.AT;
            temp.WT=temp.TAT-temp.p.BT;
            ans[i]=temp;
            currProcess=getNextProcess(input,i+1,n,temp.CT);
        }
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

