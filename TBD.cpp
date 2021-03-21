#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned char uchar;
typedef unsigned int uint;

const uint SIZE = 10;
const uint ENCRYPT = 0;
const uint DECRYPT = 1;

void shift_rows(uchar mat[SIZE][SIZE], int flag)
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

void shift_bits(uchar mat[SIZE][SIZE])
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      uchar aux1 = mat[i][j], aux2 = mat[i][j];
      aux1 <<= 4;
      aux2 >>= 4;
      uchar res = aux1 | aux2;
      mat[i][j] = res;
    }
  }
}

void transpose(uchar mat[SIZE][SIZE])
{
  for (int i = 0; i < SIZE; ++i)
    for (int j = i + 1; j < SIZE; ++j)
      swap(mat[i][j], mat[j][i]);
}

void bit_operations(uchar key[SIZE][SIZE], uchar message[SIZE][SIZE], uchar newMat[SIZE][SIZE], int encrypt)
{
  if (encrypt == ENCRYPT)
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

string mutate_key(string key, int x)
{
  string newKey = "";

  for (int i = 0; i < key.length(); i++)
  {
    uchar letter = static_cast<uchar>(key[i] + x + i);
    newKey += letter;
  }
  return newKey;
}

void encode(uchar block[SIZE][SIZE], uchar key_block[SIZE][SIZE], uchar res_block[SIZE][SIZE])
{
  shift_rows(block, ENCRYPT);
  shift_bits(block);
  transpose(block);
  bit_operations(key_block, block, res_block, ENCRYPT);
}

void decode(uchar block[SIZE][SIZE], uchar key_block[SIZE][SIZE], uchar res_block[SIZE][SIZE])
{
  bit_operations(key_block, block, res_block, DECRYPT);
  transpose(res_block);
  shift_bits(res_block);
  shift_rows(res_block, DECRYPT);
}

int main()
{
  string message, key, option_str;
  uchar block[SIZE][SIZE], key_block[SIZE][SIZE], res_block[SIZE][SIZE];
  uint option = 0;

  cout << "MENU\n1) Encrypt\n2) Decrypt\n3) Exit\nOption: ";
  cin >> option;

  char c;
  while (cin.get(c) && c != '\n')
    if (!std::isspace(c))
    {
      std::cerr << "ERROR unexpected character '" << c << "' found\n";
      exit(EXIT_FAILURE);
    }

  if (option == 1)
    option_str = "encrypt";
  else if (option == 2)
    option_str = "decrypt";
  else
  {
    cout << "\nThat was fun, bye!\n";
    return 0;
  }

  // Get message
  cout << "Name of the file with message to " << option_str << ":\n";
  getline(cin, message);
  string line;
  ifstream myfile(message);
  message = "";
  if (myfile.is_open())
  {
    while (getline(myfile, line))
    {
      message += line;
      message += '\n';
    }
    myfile.close();
    message = message.substr(0, message.size() - 1);
  }

  else
    cout << "Unable to open file";

  int pos = 0;
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (pos < message.length())
        block[i][j] = message[pos];
      else
        block[i][j] = uchar(0);
      pos++;
    }
  }

  // Get key
  cout << "Please enter the key:\n";
  getline(cin, key);
  cout << "------------------------------" << endl;

  // Mutate key
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
      pos++;
    }
  }

  string newMessage = "";

  if (option == 1)
  {
    // Encode
    encode(block, key_block, res_block);
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        newMessage += res_block[i][j];
      }
    }
    cout << "Ecoded message:\n"
         << newMessage << endl;
  }

  else
  {
    // Decode
    decode(block, key_block, res_block);
    bool eom = false;
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        if (res_block[i][j] == uchar(0))
        {
          eom = true;
          break;
        }
        newMessage += res_block[i][j];
      }
      if (eom)
        break;
    }
    cout << "Decoded message:\n"
         << newMessage << endl;
  }

  ofstream resfile;
  resfile.open("res.txt");
  resfile << newMessage;
  resfile.close();

  cout << "\n(The message has been written in res.txt)\n";

  return 0;
}
