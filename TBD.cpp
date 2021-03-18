#include <bits/stdc++.h>

using namespace std;

//function for rows shifting
void shift(int  mat[32][32]){
    int temp, posTemp;
    for(int pos = 0; pos < 32; pos++){
        for(posTemp = pos; posTemp > 0; posTemp--){
            // shift a la izquierda
            temp = mat[pos][0];
            for(int i = 0; i < 32; i++)
               mat[pos][i] = mat[pos][i+1];

            mat[pos][31] = temp;
        }
    }
}

void transpose(int mat[32][32]){
     for (int i = 0; i < 32; ++i)
      for (int j = i+1; j < 32; ++j)
        swap(mat[i][j], mat[j][i]);
}

int main(){
  unsigned int SIZE = 16;
  string message;
  char block[SIZE][SIZE];

  cout << "Please enter the message to cipher\n";
  getline(cin,message);
  int pos = 0;
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      if(pos < message.length())
        block[i][j]=message[pos];
      else
        block[i][j] = '|';
      pos++;
    }
  }

  return 0;
}
