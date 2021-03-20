
#include <bits/stdc++.h>
using namespace std;
int main(){
    // unsigned char c = 'z';
    // unsigned char temp ;
    // cout<<c<<" ";
    // temp = ((c & 0x0F) >> 4 | (c & 0xF0) << 4) ;
    // c=temp;
    // cout<<c<<" ";
    // temp = ((c & 0x0F) << 4 | (c & 0xF0) >> 4);
    // c=temp;
    // cout<<c;

    unsigned char aux1='P';
    unsigned char aux2='P';
    cout<<aux1<<" ";
    cout<<aux2<<" ";
    aux1 = aux1 << 4;
    
    aux2 = aux2 >> 4;
    unsigned char res = aux1 | aux2;

    cout<<res<<" ";

    aux1 = res >> 4;
    
    aux2 = res << 4;
    res = aux1 | aux2;
    // cout<<res<<" ";


    for (int c = 0; c < SIZE_TEXT; c++)
    {
        
    }
    
}