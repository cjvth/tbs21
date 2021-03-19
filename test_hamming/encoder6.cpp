#include<iostream>
#include <map>
#include <vector>
using namespace std;
#include <stdio.h>

const int PORTION_SIZE= 2048;
const int REPEATS = 3;
const int BATCH_SIZE = 256;
const int BATCH_2_SIZE = (BATCH_SIZE * 8 + 6) / 7;

void vi(int a)
{
	for(int i=7;i>=0;--i)
	{
		cout<<((a & (1<<i))>>i);
	}
	cout<<endl;
}

void hamming_encode(char data[], char ret[], long len) {
    for (long i = 0; i < len; i++) {
        char byte = data[i];
        for(int j=0;j<2;++j) {
            int a=0;
            a= a | (byte & (1<<0));
            a= a | (byte & (1<<1));
            a= a | (byte & (1<<2));
            a= a | ((byte & (1<<3))<<1);
            a= a | (((((a&(1<<0))>>0) + ((a&(1<<2))>>2) + ((a&(1<<4))>>4))%2)<<6) ;
            a= a | (((((a&(1<<0))>>0) + ((a&(1<<1))>>1) + ((a&(1<<4))>>4))%2)<<5) ;
            a= a | (((((a&(1<<0))>>0) + ((a&(1<<2))>>2) + ((a&(1<<1))>>1))%2)<<3) ;
            ret[2 * i + j]=a;
            byte=(byte>>4);
        }
    }
}


int encoder(FILE* r_fifo, FILE* w_fifo)
{
    char portion[PORTION_SIZE];
    long s;
    long n_batch_ = 0;
    long n_batch = 0;
    while (s = fread(portion, sizeof(char), PORTION_SIZE, r_fifo)) {
        for (int _ = 0; _ < REPEATS; ++_) {
            long n_batch = n_batch_;
            for (int i = 0; i < s; i += BATCH_SIZE) {
                char n_batch_c[2] = {192 | (n_batch / 64), 128 | (n_batch % 64)};
                char n_batch_h[4];
                hamming_encode(n_batch_c, n_batch_h, 2);
                fwrite(n_batch_h, sizeof(char), 4, w_fifo);
                char * curr = portion + i;
                char data_c[BATCH_2_SIZE];
                int j=7,m=0,n,k;
                for(n=0;n<BATCH_2_SIZE;++n)
                {
                    data_c[n]=0;
                    for (k = 6; k>=0; --k) {
                        data_c[n] |= (((curr[m] & (1<<j))>>j)<<k);
                        --j;
                        if(j<0)
                        {
                            j=7;
                            ++m;
                        }
                    }
                }
                char data_h[BATCH_2_SIZE*2];
                hamming_encode(data_c, data_h, BATCH_2_SIZE);
                fwrite(data_h, sizeof(char), BATCH_2_SIZE*2, w_fifo);
                n_batch++;
            }
        }
        n_batch_ = n_batch;
    }
 return 0;
}