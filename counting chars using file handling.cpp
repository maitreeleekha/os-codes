
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    fstream file;
   /* file.open("test.txt",ios::out);
    char input[1000];
    cin.getline(input,10000);
    fflush(stdin);
    file<<input;
    file.close();*/
    file.open("test.txt",ios::in);
    char c;
    int space=0,characters=0,special=0,number=0,words=0,lines=1;
    while(!file.eof() && file.get(c))
    {
        if((c>='A' && c<='Z') || (c>='a' && c<='z'))
            characters++;
        else   if(c==' ')
            space++;
        else if(c>='0' &&c<='9')
            number++;
            else if(c=='\n'){
                lines++;
            }

        else
        {
            special++;
        }

    }
    words=space+1;
    cout<<"alphabets: "<<characters;
    cout<<endl;
    cout<<"space: "<<space;
    cout<<endl;
    cout<<"numbers: "<<number;
    cout<<endl;
    cout<<"words: "<<words;
    cout<<endl;
    cout<<"special: "<<special;
    cout<<endl;
    cout<<"lines: "<<lines;
        file.close();
    return 0;
}


