#include <bits/stdc++.h>

using namespace std;

typedef unsigned char uchar;
typedef unsigned int uint;

const uint SIZE = 10;
const uint ENCRYPT = 0;
const uint DECRYPT = 1;
const uint PRINTABLE_CHARS = 95;

void shift_rows(char mat[SIZE][SIZE], int flag)
{
  int temp, posTemp;
  if (flag == ENCRYPT)
  {
    for (int pos = 0; pos < SIZE; pos++)
    {
      for (posTemp = pos; posTemp > 0; posTemp--)
      {
        // left shift
        temp = mat[pos][0];
        for (int i = 0; i < SIZE; i++)
          mat[pos][i] = mat[pos][i + 1];

        mat[pos][SIZE - 1] = temp;
      }
    }
  }
  else if (flag == DECRYPT)
  {
    for (int pos = 0; pos < SIZE; pos++)
    {
      for (posTemp = pos; posTemp > 0; posTemp--)
      {
        // right shift
        temp = mat[pos][SIZE - 1];
        for (int i = SIZE - 1; i >= 0; i--)
          mat[pos][i] = mat[pos][i - 1];

        mat[pos][0] = temp;
      }
    }
  }
}

void shift_bits(char mat[SIZE][SIZE])
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      uchar aux1 = mat[i][j] << 4;
      uchar aux2 = mat[i][j] >> 4;

      mat[i][j] = aux1 | aux2;
    }
  }
}

void transpose(int mat[SIZE][SIZE])
{
  for (int i = 0; i < SIZE; ++i)
    for (int j = i + 1; j < SIZE; ++j)
      swap(mat[i][j], mat[j][i]);
}

void bit_operations(char key[SIZE][SIZE], char message[SIZE][SIZE], char newMat[SIZE][SIZE], int encrypt)
{
  if (!encrypt)
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        int temp = message[i][j] ^ key[i][j];
        newMat[i][j] = ~temp;
      }
    }
  }
  else
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        int temp = ~message[i][j];
        newMat[i][j] = temp ^ key[i][j];
      }
    }
  }
}

int get_next_printable_char(int value)
{
  int res = value;
  while(value > 126) {
    value -= PRINTABLE_CHARS;
  }
  return res;
}

int get_prev_printable_char(int value)
{
  int res = value;
  while(value < 32) {
    value += PRINTABLE_CHARS;
  }
  return res;
}

string mutate_key(string key, int x, int encrypt)
{
  string newKey = "";

  for (int i = 0; i < key.length(); i++)
  {
    char letter;
    int value;
    if(encrypt == ENCRYPT)
    {
      value = key[i] + x + i;
      letter = static_cast<char>(get_next_printable_char(value));
    }
    else
    {
      value = key[i] - x - i;
      letter = static_cast<char>(get_prev_printable_char(value));
    }
    newKey += letter;
  }
  return newKey;
}

int main()
{
  string message, key;
  char block[SIZE][SIZE], key_block[SIZE][SIZE];
  cout << "Please enter the message to cipher:\n";
  getline(cin, message);
  int pos = 0;
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (pos < message.length())
        block[i][j] = message[pos];
      else
        block[i][j] = '|';
      pos++;
    }
  }
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      cout << block[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "------------------------------" << endl;

  shift_rows(block, ENCRYPT);
  // shift_bits(block);
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      cout << block[i][j] << " ";
    }
    cout << "\n";
  }
  // shift_bits(block);
  shift_rows(block, DECRYPT);
  cout << "******************" << endl;
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      cout << block[i][j] << " ";
    }
    cout << "\n";
  }

  cout << "Please enter the key:\n";
  getline(cin, key);
  pos = 0;
  int count = 0;
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (pos >= key.length())
      {
        count++;
        key = mutate_key(key, count);
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
