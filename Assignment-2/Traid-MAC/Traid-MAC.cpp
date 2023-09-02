/*
Name : Ishan Mehta
Roll : 2019309

Implementing Traid-MAC.

*/
#include<iostream>
#include <stdio.h>
#include <time.h>
using namespace std;

// message length
const int mlen = 64;
const long long adlen = 64;
uint8_t A[adlen], A_dash[adlen + 7];
uint8_t get_random_byte()
{
    return (uint8_t)(rand() % 256);
}
void display(const uint8_t a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << (int)a[i] << " ";
    }
    cout << "\n";
}

class TRAID
{
    private:
    uint8_t a[10],b[11],c[11],con[4];
    uint8_t get_bit(uint8_t arr[], int pos)
    {
        int index = pos-1;
        int byte = (index / 8);
        int bit_from_left = index % 8;
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

        for (int i = 9; i > 0; i--)
        {
            a[i] /= 2;
            a[i] += (a[i - 1] & 1) << 7;
        }
        a[0] /= 2;
        a[0] += (t3 << 7);

        for (int i = 10; i > 0; i--)
        {
            b[i] /= 2;
            b[i] += (b[i - 1] & 1) << 7;
        }
        b[0] /= 2;
        b[0] += (t1 << 7);

        for (int i = 10; i > 0; i--)
        {
            c[i] /= 2;
            c[i] += (c[i - 1] & 1) << 7;
        }
        c[0] /= 2;
        c[0] += (t2 << 7);
        return z;
    }
    void traidP()
    {
        for (int i = 1; i <= 1024; i++)
        {
            uint8_t z = traidUPD(0);
        }
    }
    void traidPB()
    {
        uint8_t z = traidUPD(1);
        for(int i=2;i<=1024;i++)
        {
            uint8_t z = traidUPD(0);
        }
    }
    public:
    TRAID()
    {
        for (int i = 0; i < 10; i++)
            a[i] = 0;
        for (int i = 0; i < 11; i++)
        {
            b[i] = 0;
            c[i] = 0;
        }
        for (int i = 3; i >= 0; i--) con[i] = 255;
        con[0]--;
    }
    void traidMAC(uint8_t K[], uint8_t N[], uint8_t M[], uint8_t T[])
    {
        int index = 0;
        a[index++] = N[0];
        a[index++] = K[4];
        a[index++] = con[3];
        a[index++] = K[3];
        a[index++] = con[2];
        a[index++] = K[2];
        a[index++] = con[1];
        a[index++] = K[1];
        a[index++] = con[0];
        a[index++] = K[0];

        index = 0;
        for (int i = 11; i >= 1; i--)
            b[index++] = N[i];
        index = 0;
        for (int i = 15; i >= 5; i--)
            c[index++] = K[i];


        traidPB();

        for(int i=0;i<=adlen+7-1;i++)
        {
            for(int j=8-1;j>=0;j--)
            {
                traidUPD(get_bit(A_dash, 8*i + j));
            }
        }

        for(int i=0;i<mlen;i++)
        {
            for(int j=8-1;j>=0;j--)
            {
                traidUPD(get_bit(M, 8 * i + j));
            }
        }

        traidPB();
        for(int i=0;i<7;i++) T[i] = 0;
        for(int i=0;i<7;i++)
        {
            for(int j=8-1;j>=0;j--)
            {
                // t[i][j] = traidUPD(0);

                uint8_t z = traidUPD(0);
                T[i] += (z<<j);
            }
        }
    }
};
int main()
{
    srand(time(0));
    // K = Key, N = Nonce, M = Message
    uint8_t K[16], N[12], M[mlen];

    for (int i = 0; i < 16; i++)
        K[i] = get_random_byte();
    for (int i = 0; i < 12; i++)
        N[i] = get_random_byte();
    for (int i = 0; i < mlen; i++)
        M[i] = get_random_byte();
    for(int i=0;i<adlen;i++)
        A[i] = get_random_byte();

    for(int i=1;i<=adlen + 7 - 1;i++)
    {
        if(i<=adlen)
        {
            A_dash[i-1] = A[i-1];
        }
        else if((adlen + 1)==i)
        {
            A_dash[i - 1] = (adlen & 255);
        }
        else if ((adlen + 2) == i)
        {
            A_dash[i - 1] = ((adlen>>8) & 255);
        }
        else if ((adlen + 3) == i)
        {
            A_dash[i - 1] = ((adlen>>16) & 255);
        }
        else if ((adlen + 4) == i)
        {
            A_dash[i - 1] = ((adlen>>24) & 255);
        }
        else if ((adlen + 5) == i)
        {
            A_dash[i - 1] = ((adlen>>32) & 255);
        }
        else if ((adlen + 6) == i)
        {
            A_dash[i - 1] = ((adlen>>40) & 255);
        }
        else if ((adlen + 7) == i)
        {
            A_dash[i - 1] = ((adlen>>48) & 255);
        }
    }

    cout << "Message ->\n";
    display(M, mlen);

    TRAID *obj = new TRAID();
    uint8_t T[8];
    obj->traidMAC(K,N,M,T);

    cout << "TAG ->\n";
    display(T, 8);

    return 0;
}