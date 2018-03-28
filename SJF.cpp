#include<iostream>
#include<vector>
using namespace std;
class processParams
{
public:
    int p_id;
    int BT;
};

class finalAns
{
public:
    int p_id;
    int BT;
    int AT=0;
    int ST;
    int CT;
    int TAT;
    int WT;
};

void sortByBurstTime(vector<processParams> & input)
{

    for(int i=0; i<input.size()-1; i++)
    {
        for(int j=0; j<input.size()-1-i; j++)
        {
            if(input[j].BT>input[j+1].BT)
            {
                processParams temp;
                temp.BT=input[j].BT;
                input[j].BT= input[j+1].BT;
                input[j+1].BT= temp.BT;

                temp.p_id=input[j].p_id;
                input[j].p_id= input[j+1].p_id;
                input[j+1].p_id= temp.p_id;

            }
        }
    }

}

int main()
{
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    vector<processParams> input;
    vector<finalAns> ans;
    for(int i=0; i<n; i++)
    {
        cout<<"Enter the burst time for process "<< i+1<<"  ";
        processParams tempObject;
        tempObject.p_id=i+1;
        cin>>tempObject.BT;
        cout<<endl;
        input.push_back(tempObject);
    }
    sortByBurstTime(input);

    for(int i=0; i<n; i++)
    {
        processParams currProcess=input[i];
        finalAns tempAns;
        tempAns.BT = currProcess.BT;
        if(i==0)
        {
            tempAns.ST=0;
        }
        else
        {
            tempAns.ST=ans[i-1].CT;
        }
        tempAns.CT = tempAns.ST + tempAns.BT;
        tempAns.TAT = tempAns.CT;
        tempAns.WT = tempAns.TAT-tempAns.BT;
        tempAns.p_id=currProcess.p_id;
        ans.push_back(tempAns);
    }


cout<<"P_ID"<<'\t';
cout<<"AT"<<'\t';
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
        cout<<ans[i].p_id<<'\t';
        cout<<ans[i].AT<<'\t';
        cout<<ans[i].BT<<'\t';
        cout<<ans[i].CT<<'\t';
        cout<<ans[i].TAT<<'\t';
        cout<<ans[i].WT<<'\t';
        cout<<endl;

for(int i=0;i<50;i++){
    cout<<'-';
}
cout<<endl;
    }


}
