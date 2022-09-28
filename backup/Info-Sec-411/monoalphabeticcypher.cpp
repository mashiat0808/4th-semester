#include <iostream>
using namespace std;
char encrypt(char);
char decrypt(char);
 char mapping[28][3]={
    {'a','x'}, {'b','c'}, {'c', 'r'}, {'d', 'e'}, {'e', 'a'}, {'f','b'},{'g','d'}, {'h','z'}, 
    {'i','y'},{'j','w'}, {'k','l'}, {'l', 'm'},{'m','f'},{'n','j'}, {'o','k'},{'p','g'}, {'q','h'}, 
    {'r','p'},{'s','i'},{'t', 'n'},{'u','v'},{'v','o'},{'w','q'},{'x','s'}, {'y','t'}, {'z','u'}, {' ',' '}
};
char encrypt (char a)
{
    int i;
    for(i=0;i<26;i++)
    {
        if (a==mapping[i][0]) break;
    }
    return mapping[i][1];
}
char decrypt (char a)
{
    int i;
    for(i=0;i<26;i++)
    {
        if (a==mapping[i][1]) break;
    }
    return mapping[i][0];
}

int main()
{
    string x;
    cout<<"enter input\n";
    getline(cin, x);
    string y;
    int i;
    for(i=0;x[i];i++)
    {
        y[i]=encrypt(x[i]);
    }
    y[i+1]= '\0';
    cout<<"Encrypted message\n";
    for(i=0;y[i];i++)
    {
        cout<<y[i];
    }
    cout<<"\n";

    cout<<"Decypted message\n";
    for(i=0;y[i];i++)
    {
        cout<<decrypt(y[i]);
    }
cout<<"\n";
    
}

  