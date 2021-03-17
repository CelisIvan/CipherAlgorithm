#include <bits/stdc++.h>

using namespace std;

//function for rows shifting
void shift( int  mat[32][32]){
    int pos=0, temp, posTemp;
    while(pos<32){
        posTemp=pos;
        while(posTemp){
            // shift a la izquierda
            temp = mat[pos][0];
            for(int i=0;i<32;i++)
               mat[pos][i] = mat[pos][i+1];

            mat[pos][31] = temp;
            posTemp--;
        }
        pos++;
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
    int pos = 0;
    while(pos<message.length()){
        for(int i=0;i<32;i++){
            for(int j=0;j<32;j++){
                block[i][j]=message[pos];
            }
        }
        pos++;
    }

    return 0;
}
