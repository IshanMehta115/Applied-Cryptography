/*
Name : Ishan Mehta
Roll : 2019309

Implementing Triple DES.

*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
string round_keys[16];
string pt;
const int pc2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32};
const int init_perm[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};
// The expansion table
const int expansion_table[48] = {
    32, 1, 2, 3, 4, 5, 4, 5,
    6, 7, 8, 9, 8, 9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32, 1};
const int s_box[8][4][16] =
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
      0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
      4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
      15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
     {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
      3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
      0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
      13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
     {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
      13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
      13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
      1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
     {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
      13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
      10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
      3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
     {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
      14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
      4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
      11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
     {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
      10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
      9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
      4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
     {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
      13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
      1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
      6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
     {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
      1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
      7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
      2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};
const int perm_tab[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25};
const int inv_perm[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};
string decimal_to_binary(int decimal)
{
    string binary;
    while (decimal)
    {
        binary.push_back((decimal % 2) + '0');
        decimal /= 2;
    }
    while (binary.length() < 4)
        binary.push_back('0');
    reverse(binary.begin(), binary.end());
    return binary;
}
int binary_to_decimal(string binary)
{
    int decimal = 0;
    int prod = 1;
    for (int i = binary.length() - 1; i >= 0; i--)
    {
        decimal += prod * ((binary[i] == '1')?1:0);
        prod *= 2;
    }
    return decimal;
}
string left_shift(string key)
{
    string shifted = key;
    for (int i = 0; i < 28; i++)
        shifted[i] = key[(i + 1) % 28];
    return shifted;
}
string string_xor(string a, string b)
{
    int size = b.size();
    string result(size, '0');
    for (int i = 0; i < size; i++)
    {
        result[i] = (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}
string DES()
{
    string perm(64, '0');
    for (int i = 0; i < 64; i++)
        perm[i] = pt[init_perm[i] - 1];
    string left(32, '0'), right(32, '0');
    for (int i = 0; i < 32; i++)
        left[i] = perm[i];
    for (int i = 0; i < 32; i++)
        right[i] = perm[i + 32];
    for (int i = 0; i < 16; i++)
    {
        string expanded_right(48, '0');
        for (int i = 0; i < 48; i++)
        {
            expanded_right[i] = right[expansion_table[i] - 1];
        };
        string xored = string_xor(round_keys[i], expanded_right);
        string res = "";
        for (int i = 0; i < 8; i++)
        {
            string row1 = "";
            string col1 = "";
            for(int j=0;j<6;j+=5) row1 += xored.substr(i * 6 + j, 1);
            for (int j = 1; j <= 4; j++) col1 += xored.substr(i * 6 + j, 1);
            int row = binary_to_decimal(row1);
            int col = binary_to_decimal(col1);
            int val = s_box[i][row][col];
            res += decimal_to_binary(val);
        }
        string perm2(32, '0');
        for (int i = 0; i < 32; i++)
            perm2[i] = res[perm_tab[i] - 1];
        xored = string_xor(perm2, left);
        left = xored;
        if (i < 15)
        {
            string temp = right;
            right = xored;
            left = temp;
        }
    }
    string comb_text = left + right;
    string ciphertext(64, '0');
    for (int i = 0; i < 64; i++)
    {
        ciphertext[i] = comb_text[inv_perm[i] - 1];
    }
    return ciphertext;
}
void generate_keys(string key)
{
    string perm_key = key;
    string left(28, '0'), right(28, '0');
    for (int i = 0; i < 28; i++)
        left[i] = perm_key[i];
    for (int i = 0; i < 28; i++)
        right[i] = perm_key[i + 28];
    for (int i = 1; i <= 16; i++)
    {
        if (i == 1 || i == 2 || i == 9 || i == 16)
        {
            left = left_shift(left);
            right = left_shift(right);
        }
        else
        {
            left = left_shift(left);
            left = left_shift(left);
            right = left_shift(right);
            right = left_shift(right);
        }
        string comb = left + right;
        string round_key(48, '0');
        for (int i = 0; i < 48; i++)
        {
            round_key[i] = comb[pc2[i - 1] - 1];
        }
        round_keys[i - 1] = round_key;
    }
}
string DES_encrypt(string k, string plaintext)
{
    generate_keys(k);
    pt = plaintext;
    return DES();
}
string DES_decrypt(string k, string ciphertext)
{
    generate_keys(k);
    pt = ciphertext;
    for(int i=0;i<8;i++)
    {
        swap(round_keys[i], round_keys[16-i-1]);
    }
    return DES();
}
string Triple_DES_encrypt(string k1, string k2, string k3, string plaintext)
{
    string val1 = DES_encrypt(k1, plaintext);
    string val2 = DES_decrypt(k2, val1);
    string val3 = DES_encrypt(k3, val2);
    return val3;
}
string Triple_DES_decrypt(string k1, string k2, string k3, string ciphertext)
{
    string val1 = DES_decrypt(k3, ciphertext);
    string val2 = DES_encrypt(k2, val1);
    string val3 = DES_decrypt(k1, val2);
    return val3;
}
int main()
{
    // 56 bits key
    string key1 = "00001110100100100101001011111100101111110000111011100111";
    string key2 = "01010111110000010100111101000100011000100011000001000100";
    string key3 = "10110101010001101000010100111001010000111101000100000100";
    // A block of plain text of 64 bits 
    string text = "1010101111001101111001101010101111001101000100110010010100110110";
    cout << "Plain text: " << text << endl;
    string ct = Triple_DES_encrypt(key1,key2,key3,text);
    cout << "Ciphertext: " << ct << endl;
    string decrypted = Triple_DES_decrypt(key1,key2,key3, ct);
    cout << "Decrypted text:" << decrypted << endl;
    // Comapring the initial plain text with the decrypted text
    if (decrypted == text)
    {
        cout << "Plain text encrypted and decrypted successfully." << endl;
    }
    else
    {
        cout << "Plain text encryption and decryption failed." << endl;
    }
}