#include <iostream>
#include <string>
using namespace std;
char encrypt(char);
char decrypt(char);
 char mapping[27][5]={
    {'a','x','y','z'}, {'b','c','d', 'e'}, {'c', 'r', 's', 't'}, {'d', 'e', 'f', 'g'}, {'e', 'a', 'b','c'}, {'f','b','c','d'},{'g','d', 'e', 'f'}, {'h','z','a', 'b'}, 
    {'i','y', 'z', 'a'},{'j','w','x','y'}, {'k','l', 'm', 'n'}, {'l', 'm','n','o'},{'m','f', 'g', 'h'},{'n','j','k','l'}, {'o','k','l', 'm'},{'p','g', 'h', 'i'}, {'q','h', 'i','j'}, 
    {'r','p','q','r'},{'s','i','j','k'},{'t', 'n', 'o', 'p'},{'u','v','w','x'},{'v','o', 'p','q'},{'w','q','r','s'},{'x','s','t','u'}, {'y','t', 'u','v'}, {'z','u','v','w'}
};
char encrypt (char a, int k)
{
    int i;
    for(i=0;i<26;i++)
    {
        if (a==mapping[i][0]) break;
        else if (a==' ') return ' ';
        else if (a==',') return ',';
        else if (a=='.') return '.';
        else if (a=='?') return '?';
    }
    if(k%4==0)
    return mapping[i][0];
    else if (k%4==1) return mapping[i][1];
    else if(k%4==2) return mapping[i][2];
    else return mapping[i][3];
}
char decrypt (char a, int k)
{
    int i;
    for(i=0;i<26;i++)
    {
        if (a==mapping[i][0] && k%4==0) return mapping[i][0];
        else if (a==mapping[i][1] && k%4==1)return mapping[i][0];
        else if (a==mapping[i][2] && k%4==2)return mapping[i][0];
        else if  (a==mapping[i][3] && k%4==3)return mapping[i][0];
        else if (a==' ') return ' ';
        else if (a==',') return ',';
        else if (a=='.') return '.';
        else if (a=='?') return '?';
    }

}
int main()
{
    string x;
    cout<<"enter input\n";
    getline(cin, x);
   // cout<<x;
    int count=0;
    while(x[count]){ count++;}
    //cout<<count;
    string y;
    int i;
    for(i=0;i<count;i++)
    {
        y[i]=encrypt(x[i],i);
    }
    cout<<"Encrypted message\n";
    for(i=0;i<count;i++)
    {
        cout<<y[i];
    }
    cout<<"\n";
    
   cout<<"Decypted message\n";

    for(i=0;i<count;i++)
    {
        cout<<decrypt(y[i],i);
    }
cout<<"\n";
    
}
