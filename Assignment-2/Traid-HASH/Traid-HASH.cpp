/*
Name : Ishan Mehta
Roll : 2019309

Implementing Traid-HASH.

*/
#include <iostream>
#include <stdio.h>
#include <time.h>
#include<vector>
using namespace std;

const int mlen = 64;
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
void display(const uint32_t a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << (uint32_t)a[i] << " ";
    }
    cout << "\n";
}
void modify(uint8_t m[],int mlen,uint32_t m_dash[],const int hlen)
{
    vector<uint8_t> temp(hlen * 4);
    for(int i=0;i<mlen;i++) temp[i] = m[i];
    temp[mlen] = 1<<7;
    for(int i=mlen+1;i<=hlen*4;i++) temp[i] = 0;

    for(int i=0;i<hlen;i++)
    {
        m_dash[i] = (temp[4 * i + 3] << 24) + (temp[4 * i + 2] << 16) + (temp[4 * i + 1] << 8) + temp[4 * i];
    }
}
class TRAID
{
    private:
    uint8_t a[10], b[11], c[11];
    uint8_t get_bit(uint8_t arr[], int pos)
    {
        int index = pos - 1;
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
    public:
    TRAID()
    {

    }
    void traidHASH(uint8_t K[], uint8_t N[], uint32_t M_dash[], uint8_t Z[],int hlen)
    {
        for(int i=0;i<10;i++)
        {
            a[i] = 0;
        }
        for(int i=0;i<11;i++)
        {
            c[i] = 0; 
        }
        b[0] = 183;
        b[1] = 225;
        b[2] = 81;
        b[3] = 98;
        b[4] = 138;
        b[5] = 14 << 4;

        b[5]+=2;
        b[6] = 67;
        b[7] = 246;
        b[8] = 168;
        b[9] = 136;
        b[10] = 90;


        for(int i=0;i<hlen;i++)
        {
            a[0] = a[0] ^ ((M_dash[i] >> 24) & 255);
            a[1] = a[1] ^ ((M_dash[i] >> 16) & 255);
            a[2] = a[2] ^ ((M_dash[i] >> 8) & 255);
            a[3] = a[3] ^ ((M_dash[i] >> 0) & 255);
            traidP();
        }

        int index = 0;
        for(int i=15;i>=6;i--) Z[i] = a[index++];
        index = 0;
        for(int i=5;i>=0;i--) Z[i] = b[index++];

        traidP();

        index = 0;
        for (int i = 31; i >= 22; i--) Z[i] = a[index++];
        index = 0;
        for (int i = 21; i >= 16; i--) Z[i] = b[index++];
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
    
    const int hlen = ((8*mlen + 1 + 31)/32);

    uint32_t M_dash[hlen];

    modify(M,mlen,M_dash,hlen);

    cout << "\nMessage ->\n";
    display(M, mlen);

    cout << "\nmodified message ->\n";
    display(M_dash, hlen);


    TRAID *obj = new TRAID();
    uint8_t Z[32];
    obj->traidHASH(K,N,M_dash,Z,hlen);
    cout << "\nZ value ->\n";
    display(Z, 32);
    return 0;
}