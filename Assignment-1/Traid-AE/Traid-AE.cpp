/*
Name : Ishan Mehta
Roll : 2019309

Implementing Triple Traid-AE.

*/

#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;
uint8_t get_random_byte()
{
    return (uint8_t)(rand() % 256);
}
// message length
const int mlen = 20;

void display(const uint8_t a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << (int)a[i] << " ";
    }
    cout << "\n";
}
class TraidAE
{
private:
    uint8_t a[10], b[11], c[11];
    uint8_t con[4];
    uint8_t get_bit(uint8_t arr[], int pos)
    {
        int index = pos--;
        int byte = (index/8);
        int bit_from_left = index%8;
        int bit_from_right = 7 - bit_from_left;
        int bit = 0;
        if ((arr[byte] & (1 << bit_from_right)))
            bit = 1;
        return bit;
    }
    uint8_t traidUPD(uint8_t msg)
    {
        uint8_t t1 = get_bit(a, 68) ^ get_bit(a, 80) ^ (get_bit(b, 85) & get_bit(c, 85));
        uint8_t t2 = get_bit(b, 64) ^ get_bit(b, 88);
        uint8_t t3 = get_bit(c, 68) ^ get_bit(c, 88);
        uint8_t z = t1 ^ t2 ^ t3;
        t1 = t1 ^ (get_bit(a, 73) & get_bit(a, 79)) ^ get_bit(b, 66) ^ msg;
        t2 = t2 ^ (get_bit(b, 65) & get_bit(b, 87)) ^ get_bit(c, 84) ^ msg;
        t3 = t3 ^ (get_bit(c, 77) & get_bit(c, 87)) ^ get_bit(a, 74) ^ msg;

        for(int i=9;i>0;i--)
        {
            a[i]/=2;
            a[i]+= (a[i-1]&1) << 7;
        }
        a[0]/=2;
        a[0]+= (t3 << 7);

        for(int i=10;i>0;i--)
        {
            b[i]/=2;
            b[i]+=(b[i-1]&1)<<7;
        }
        b[0]/=2;
        b[0]+= (t1<<7);

        for(int i=10;i>0;i--)
        {
            c[i]/=2;
            c[i]+=(c[i-1]&1)<<7;
        }
        c[0]/=2;
        c[0]+=(t2<<7);
        return z;
    }
    void traidP()
    {
        for (int i = 0; i < 1024; i++)
        {
            uint8_t z = traidUPD(0);
        }
    }
    void traidSC(const uint8_t key[], const uint8_t nonce[], const uint8_t text[], uint8_t output[])
    {
        int index = 0;
        a[index++] = nonce[0];
        a[index++] = key[4];
        a[index++] = con[3];
        a[index++] = key[3];
        a[index++] = con[2];
        a[index++] = key[2];
        a[index++] = con[1];
        a[index++] = key[1];
        a[index++] = con[0];
        a[index++] = key[0];

        index = 0;
        for (int i = 11; i >= 1; i--)
            b[index++] = nonce[i];
        index = 0;
        for (int i = 15; i >= 5; i--)
            c[index++] = key[i];

        traidP();

        for (int i = 0; i < mlen; i++)
            output[i] = 0;

        for (int i = 0; i < mlen; i++)
        {
            for (int j = 8 - 1; j >= 0; j--)
            {
                uint8_t z = traidUPD(0);
                output[i] += (text[i] & (1 << j)) ^ (z << j);
            }
        }
    }

public:
    TraidAE()
    {
        for (int i = 0; i < 10; i++)
            a[i] = 0;
        for (int i = 0; i < 11; i++)
        {
            b[i] = 0;
            c[i] = 0;
        }
        for (int i = 3; i >= 0; i--)
            con[i] = 255;
        con[0]--;
    }
    void encrypt(const uint8_t key[], const uint8_t nonce[], const uint8_t msg[], uint8_t output[])
    {
        traidSC(key, nonce, msg, output);
    }
    void decrypt(const uint8_t key[], const uint8_t nonce[], const uint8_t cipher[], uint8_t output[])
    {
        traidSC(key, nonce, cipher, output);
    }
};
int main()
{
    srand(time(0));
    // K = Key, N = Nonce, M = Message, C = Ciphertext, D = Decrypted text, B = buffer array(to store outputs);
    uint8_t K[16], N[12], M[20], B[mlen], C[mlen], D[mlen];

    for (int i = 0; i < 16; i++)
        K[i] = get_random_byte();
    for (int i = 0; i < 12; i++)
        N[i] = get_random_byte();
    for (int i = 0; i < 20; i++)
        M[i] = get_random_byte();

    cout << "Message ->\n";
    display(M, mlen);

    TraidAE *obj = new TraidAE();

    obj->encrypt(K, N, M, B);
    for (int i = 0; i < mlen; i++)
        C[i] = B[i];

    cout << "Ciphertext ->\n";
    display(C, mlen);

    obj->decrypt(K, N, C, B);
    for (int i = 0; i < mlen; i++)
        D[i] = B[i];

    cout << "Decrypted text ->\n";
    display(D, mlen);

    bool ok = true;
    for (int i = 0; i < mlen; i++)
    {
        if (M[i] != D[i])
            ok = false;
    }
    if (ok)
    {
        cout << "Message and Decrypted text are same\n";
    }
    else
    {
        cout << "Message and Decrypted text are different\n";
    }

    return 0;
}