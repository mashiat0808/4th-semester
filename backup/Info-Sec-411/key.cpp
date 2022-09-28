#include<vector>
#include<iostream>
using namespace std;
#define POSITION_COUNT 20 // How many indices/position of character should the mappping table include. e.g. [0-19], [0-5]
#define CHARACTER_COUNT 128
#define START_CHARATER '\0'

int KEY = 0; // This key will also be used to generate mapping table. new_char = plainText[i]+index+key
char mapping[CHARACTER_COUNT][POSITION_COUNT]; 				
void generate_mapping_table();
string encrypt(string plainText);
string decrypt(string encryptedText);
char findSubstitution(int position, char decryptedCharacter); // Its an auxiliary function. Given (position,character), it iterates through the mapping table to find the appropriate substitution.

int main(){
    
    printf("Enter a string to encrypt: ");
    string input; 
    getline(cin, input);
    printf("Enter key: ");
    cin>>KEY;
    generate_mapping_table();
    string encryptedText = encrypt(input);
    cout<<"Encrypted message = "<< encryptedText<<endl;
    cout << "Decrypted message:" << decrypt(encryptedText) << endl;
    return 0;
}

void generate_mapping_table(){
    for(int i=0; i<POSITION_COUNT; i++){
        for(int j=0; j<CHARACTER_COUNT; j++){
            mapping[j][i] = START_CHARATER + (j + i + KEY)%CHARACTER_COUNT ;
        }
    }
}

string encrypt(string plainText){
    string encryptedText = "";
    for(int i=0; i<plainText.size(); i++){
        char substitutedCharacter = mapping[plainText[i]-START_CHARATER][i%POSITION_COUNT];
        encryptedText += string(1, substitutedCharacter);
        //printf("%c->%c\n", plainText[i], substitutedCharacter);
    }
    return encryptedText;
}

char findSubstitution(int position, char encryptedCharacter){
    for(int i = 0; i<CHARACTER_COUNT; i++){
        if(mapping[i][position]==encryptedCharacter) return START_CHARATER + i;
    }
}

string decrypt(string encryptedText){
    string plainText = "";
    for(int i=0; i<encryptedText.size(); i++){
        plainText += string(1, findSubstitution(i%POSITION_COUNT, encryptedText[i]));
    }
    return plainText;
}