#include <bits/stdc++.h>

using namespace std;

const unsigned int SIZE_TEXT = 10;
const unsigned int ENCRYPT = 0;
const unsigned int DECRYPT = 1;

typedef unsigned char uchar;

//function for rows shifting
void shift(char mat[SIZE_TEXT][SIZE_TEXT], int flag){
  int temp, posTemp;
  if(flag == ENCRYPT){
    for(int pos = 0; pos < SIZE_TEXT; pos++){
        for(posTemp = pos; posTemp > 0; posTemp--){
            // shift a la izquierda
            temp = mat[pos][0];
            for(int i = 0; i < SIZE_TEXT; i++)
               mat[pos][i] = mat[pos][i+1];

            mat[pos][SIZE_TEXT-1] = temp;
        }
    }
  }else if(flag == DECRYPT){
    for(int pos = 0; pos < SIZE_TEXT; pos++){
        for(posTemp = pos; posTemp > 0; posTemp--){
            // shift a la izquierda
            temp = mat[pos][SIZE_TEXT-1];
            for(int i = SIZE_TEXT-1; i >= 0; i--)
               mat[pos][i] = mat[pos][i-1];

            mat[pos][0] = temp;
        }
    }
  }
}


void shift_bits(char mat[SIZE_TEXT][SIZE_TEXT]){
  
    uchar aux1;
    uchar aux2;
    for (int i = 0; i < SIZE_TEXT; i++) {
      for (int j = 0; j < SIZE_TEXT; j++) {
        aux1 = mat[i][j];
        aux2 = mat[i][j];
        // Shift
        aux1 = aux1 << 4;
        aux2 = aux2 >> 4;
        mat[i][j] = aux1 | aux2;
    }
  }
  
  
}


void transpose(int mat[SIZE_TEXT][SIZE_TEXT]){
     for (int i = 0; i < SIZE_TEXT; ++i)
      for (int j = i+1; j < SIZE_TEXT; ++j)
        swap(mat[i][j], mat[j][i]);
}

void bitOperations(char key[SIZE_TEXT][SIZE_TEXT], char message[SIZE_TEXT][SIZE_TEXT], char newMat[SIZE_TEXT][SIZE_TEXT], int encrypt){
  int temp;
  if(!encrypt){
    for(int i=0;i<SIZE_TEXT; i++){
      for(int j=0; j<SIZE_TEXT;j++){
        temp= message[i][j] ^ key[i][j];
        newMat[i][j] = ~temp;
      }
    }
  }else{
    for(int i=0;i<SIZE_TEXT; i++){
      for(int j=0; j<SIZE_TEXT;j++){
        temp = ~  message[i][j];
        newMat[i][j]= temp ^ key[i][j];
      }
  }
  }
  
}

string mutateKey(string key, int x){
  string newKey = "";

  for(int i = 0; i < key.length(); i++){
    char letter = static_cast<char>((key[i] + x + i)%94 + 32);
    newKey += letter;
  }
  return newKey;
}

int main(){
  string message, key;
  char block[SIZE_TEXT][SIZE_TEXT], key_block[SIZE_TEXT][SIZE_TEXT];
  cout << "Please enter the message to cipher:\n";
  getline(cin,message);
  int pos = 0;
  for(int i = 0; i < SIZE_TEXT; i++){
    for(int j = 0; j < SIZE_TEXT; j++){
      if(pos < message.length())
        block[i][j] = message[pos];
      else
        block[i][j] = '|';
      pos++;
    }
  }
  for (int i = 0; i < SIZE_TEXT; i++)
  {
    for (int j = 0; j < SIZE_TEXT; j++)
    {
      cout<<block[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "------------------------------" <<endl;

  shift(block,ENCRYPT);
  // shift_bits(block);
  for (int i = 0; i < SIZE_TEXT; i++)
  {
    for (int j = 0; j < SIZE_TEXT; j++)
    {
      cout<<block[i][j] << " ";
    }
    cout << "\n";
  }
  // shift_bits(block);
  shift(block,DECRYPT);
  cout << "******************" <<endl;
  for (int i = 0; i < SIZE_TEXT; i++)
  {
    for (int j = 0; j < SIZE_TEXT; j++)
    {
      cout<<block[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "Please enter the key:\n";
  getline(cin,key);
  pos = 0;
  int count = 0;
  for(int i = 0; i < SIZE_TEXT; i++){
    for(int j = 0; j < SIZE_TEXT; j++){
      if(pos >= key.length()) {
        count++;
        key = mutateKey(key, count);
        pos = 0;
      }
      key_block[i][j] = key[pos];
      cout << key_block[i][j];
      pos++;
    }
    cout << endl;
  }
  
  return 0;
}
