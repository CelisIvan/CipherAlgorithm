#include <bits/stdc++.h>

using namespace std;

void shift( array<array<int, 32>, 32> &mat){
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
    }
    return 0;
}