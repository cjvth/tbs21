#include<iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int BLOCK_SIZE= 1;
void vi(int a)
{
	for(int i=7;i>=0;--i)
	{
		cout<<((a & (1<<i))>>i);
	}
	cout<<endl;
}

char* hamming_encode(char* data) {
    cout << int(data[0]) << " " << data[0] << "   ";
    char ret[2];
    for(int j=0;j<2;++j) {
        int a=0;
        a= a | (data[0] & (1<<0));
        a= a | (data[0] & (1<<1));
        a= a | (data[0] & (1<<2));
        a= a | ((data[0] & (1<<3))<<1);
        a= a | (((((a&(1<<0))>>0) + ((a&(1<<2))>>2) + ((a&(1<<4))>>4))%2)<<6) ;
        a= a | (((((a&(1<<0))>>0) + ((a&(1<<1))>>1) + ((a&(1<<4))>>4))%2)<<5) ;
        a= a | (((((a&(1<<0))>>0) + ((a&(1<<2))>>2) + ((a&(1<<1))>>1))%2)<<3) ;
        ret[j]=a;
        cout << data[0] << " " << a << " ";
        data[0]=(data[0]>>4);
    }
    cout << endl;
    return ret;
}


char* hamming_decode(char* data) {
    char ret[1];
    for(int j=0;j<2;++j) {
        int a,b,c;
        a=((((data[j]&(1<<0))>>0) + ((data[j]&(1<<2))>>2) + ((data[j]&(1<<4))>>4))%2) ;
        b=((((data[j]&(1<<0))>>0) + ((data[j]&(1<<1))>>1) + ((data[j]&(1<<4))>>4))%2) ;
        c=((((data[j]&(1<<0))>>0) + ((data[j]&(1<<2))>>2) + ((data[j]&(1<<1))>>1))%2) ;
            int num=0,e=0;
            if(((data[j] & (1<<6))>>6) !=a) {num+=1;e=1;}
            if(((data[j] & (1<<5))>>5) !=b) {num+=2;e=1;}
            if(((data[j] & (1<<3))>>3) !=c) {num+=4;e=1;}
            num=7-num;
            if(e)
            {
                data[j]=(data[j] ^ (1<<num));
            }
        data[j]=(data[j] & 23);
        data[j]= (data[j]|((data[j]>>4)<<3));
        data[j] &= 15;
    }
    ret[0] = (data[1]<<4)| (data[0]);
    return ret;
}


int encoder(FILE* r_fifo, FILE* w_fifo)
{
    char buf[BLOCK_SIZE];
    char buf2[BLOCK_SIZE*2];
    long s;
    s= fread( buf, sizeof(char), BLOCK_SIZE, r_fifo);
    for(;s>0;)
    {
//        cout << buf << "   " << endl;
        auto result = hamming_encode(buf);
        cout << "!!" << result[0] << result[1] << endl;
        fwrite(result, sizeof(char), s*2, w_fifo);
        s= fread(buf, sizeof(char), BLOCK_SIZE, r_fifo);
    }
 return 0;
}

int decoder(FILE* r_fifo, FILE* w_fifo)
{
    char buf[BLOCK_SIZE*2];
    long s;
    int i;
    s= fread( buf, sizeof(char), BLOCK_SIZE*2, r_fifo);
    for(;s>0;)
    {
        cout << buf << "   " << hamming_decode(buf) << endl;
        if(s>1) fwrite(hamming_decode(buf), sizeof(char), s/2, w_fifo);
        s= fread(buf, sizeof(char), BLOCK_SIZE*2, r_fifo);
    }
    return 0;
}


int main()
{
    FILE * u = fopen ( "file.txt" , "rb" );
    FILE * f1 = fopen ( "buf-cpp.txt" , "wb" );
    encoder(u,f1);
    fclose (u);
    fclose (f1);
    cout << "\n\n\n\n\n";
    cin.get();
    FILE * f2 = fopen ( "rez-cpp.txt" , "wb" );
    FILE * f3 = fopen ( "buf2-cpp.txt" , "rb" );
    decoder(f3,f2);
    fclose (f2);
    fclose (f3);
    return 0;
}
