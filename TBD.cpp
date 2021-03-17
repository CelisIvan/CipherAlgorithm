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
    string message;
    int block[32][32];

    cout << "Please enter the message to cipher\n";
    getline(cin,message);
    for(int pos = 0; pos < message.length(); pos++){
        for(int i=0;i<32;i++){
            for(int j=0;j<32;j++){
                block[i][j]=message[pos];
            }
        }
    }

    return 0;
}
