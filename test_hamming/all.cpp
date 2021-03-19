#include<iostream>
#include <map>
#include <vector>
using namespace std;
#include <stdio.h>
#include "encoder6.cpp"
#include "decoder6.cpp"

//const int PORTION_SIZE= 2048;
//const int REPEATS = 2;
//const int BATCH_SIZE = 4;
//const int BATCH_2_SIZE = (BATCH_SIZE * 8 + 6) / 7;
//void vi(int a)
//{
//	for(int i=7;i>=0;--i)
//	{
//		cout<<((a & (1<<i))>>i);
//	}
//	cout<<endl;
//}
//
//void hamming_encode(char data[], char ret[], long len) {
//    for (long i = 0; i < len; i++) {
//        char byte = data[i];
//        for(int j=0;j<2;++j) {
//            int a=0;
//            a= a | (byte & (1<<0));
//            a= a | (byte & (1<<1));
//            a= a | (byte & (1<<2));
//            a= a | ((byte & (1<<3))<<1);
//            a= a | (((((a&(1<<0))>>0) + ((a&(1<<2))>>2) + ((a&(1<<4))>>4))%2)<<6) ;
//            a= a | (((((a&(1<<0))>>0) + ((a&(1<<1))>>1) + ((a&(1<<4))>>4))%2)<<5) ;
//            a= a | (((((a&(1<<0))>>0) + ((a&(1<<2))>>2) + ((a&(1<<1))>>1))%2)<<3) ;
//            ret[2 * i + j]=a;
//            byte=(byte>>4);
//        }
//    }
//}
//
//
//void hamming_decode(char data[], char ret[], long len) {
//    for (long i = 0; i < len; i++) {
//        char bytes[] = {data[i * 2], data[i * 2 + 1]};
//        for(int j=0;j<2;++j) {
//            int a,b,c;
//            a=((((bytes[j]&(1<<0))>>0) + ((bytes[j]&(1<<2))>>2) + ((bytes[j]&(1<<4))>>4))%2) ;
//            b=((((bytes[j]&(1<<0))>>0) + ((bytes[j]&(1<<1))>>1) + ((bytes[j]&(1<<4))>>4))%2) ;
//            c=((((bytes[j]&(1<<0))>>0) + ((bytes[j]&(1<<2))>>2) + ((bytes[j]&(1<<1))>>1))%2) ;
//                int num=0,e=0;
//                if(((bytes[j] & (1<<6))>>6) !=a) {num+=1;e=1;}
//                if(((bytes[j] & (1<<5))>>5) !=b) {num+=2;e=1;}
//                if(((bytes[j] & (1<<3))>>3) !=c) {num+=4;e=1;}
//                num=7-num;
//                if(e)
//                {
//                    bytes[j]=(bytes[j] ^ (1<<num));
//                }
//            bytes[j]=(bytes[j] & 23);
//            bytes[j]= (bytes[j]|((bytes[j]>>4)<<3));
//            bytes[j] &= 15;
//        }
//        ret[i] = (bytes[1]<<4)| (bytes[0]);
//    }
//}
//
//
//
//int encoder(FILE* r_fifo, FILE* w_fifo)
//{
//    char portion[PORTION_SIZE];
//    long s;
//    long n_batch_ = 0;
//    long n_batch = 0;
//    while (s = fread(portion, sizeof(char), PORTION_SIZE, r_fifo)) {
//        for (int _ = 0; _ < REPEATS; ++_) {
//            long n_batch = n_batch_;
//            for (int i = 0; i < s; i += BATCH_SIZE) {
//                char n_batch_c[2] = {192 | (n_batch / 64), 128 | (n_batch % 64)};
//                char n_batch_h[4];
//                hamming_encode(n_batch_c, n_batch_h, 2);
//                fwrite(n_batch_h, sizeof(char), 4, w_fifo);
//                char * curr = portion + i;
//                char data_c[BATCH_2_SIZE];
//                int j=7,m=0,n,k;
//                for(n=0;n<BATCH_2_SIZE;++n)
//                {
//                    data_c[n]=0;
//                    for (k = 6; k>=0; --k) {
//                        data_c[n] |= (((curr[m] & (1<<j))>>j)<<k);
//                        --j;
//                        if(j<0)
//                        {
//                            j=7;
//                            ++m;
//                        }
//                    }
//                }
//                char data_h[BATCH_2_SIZE*2];
//                hamming_encode(data_c, data_h, BATCH_2_SIZE);
//                fwrite(data_h, sizeof(char), BATCH_2_SIZE*2, w_fifo);
//                n_batch++;
//            }
//        }
//        n_batch_ = n_batch;
//    }
// return 0;
//}
//
//
//int decoder(FILE* r_fifo, FILE* w_fifo)
//{
//
//    map<long, vector<char>> data;
//    char byte_h[2];
//    long s;
//    long pos = 0;
//    long prevh_pos = -2;
//    long prevh_num = -2;
//    long prevh_cand_pos = -2;
//    char prevh_cand_num = 0;
//    vector<char> got_data;
//    bool getting_data = false;
//
//        while (s = fread(byte_h, sizeof(char), 2, r_fifo)) {
//            char byte[1];
//            hamming_decode(byte_h, byte, 1);
//            if ((byte[0] & 192) == 192) {
//                prevh_cand_num = byte[0];
//                prevh_cand_pos = pos;
//                getting_data = false;
//            } else if ((byte[0] & 192) == 128) {
//                if (prevh_cand_pos + 1 == pos) {
//                    long num = ((prevh_cand_num & 63) << 6) |  (byte[0] & 63);
//                    if (prevh_num + 1 == num && prevh_pos + BATCH_2_SIZE + 3 == pos) {
//                        if (!got_data.empty()) {
//                            int j,m,n=0,k=7;
//                            vector<char> res(BATCH_SIZE);
//                            for(m=0;m<BATCH_SIZE;++m)
//                            {
//                               res[m]=0;
//                                for (j = 7; j>=0; --j) {
//                                    if(k==7)
//                                    {
//                                        --k;
//                                    }
//                                    res[m] |= (((got_data[n] & (1<<k))>>k)<<j);
//                                    --k;
//                                    if(k<0)
//                                    {
//                                        k=7;
//                                        ++n;
//                                    }
//                                }
//                            }
//                            data[prevh_num] = res;
//                        }
//                    }
//                    if (data.find(num) == data.end()) {
//                        getting_data = true;
//                    } else {
//                    }
//                    got_data.clear();
//                    prevh_pos = pos - 1;
//                    prevh_num = num;
//                }
//            } else {
//                if (getting_data) {
//                    got_data.push_back(byte[0]);
//                }
//            }
//            ++pos;
//        }
//    for ( auto i: data){
//        for (auto j: i.second){
//            char data_h1[1];
//            data_h1[0] = j;
//            fwrite(data_h1, sizeof(char), 1, w_fifo);
//        }
//    }
//
//    return 0;
//}


int main()
{
    FILE * u = fopen ( "file2.txt" , "rb" );
    FILE * f1 = fopen ( "buf-cpp.txt" , "wb" );
    encoder(u,f1);
    fclose (u);
    fclose (f1);
    cout << "\n\n\n\n\n";
    cin.get();
    FILE * f2 = fopen ( "rez-cpp.txt" , "wb" );
    FILE * f3 = fopen ( "buf-cpp.txt" , "rb" );
    decoder(f3,f2,f3);
    fclose (f2);
    fclose (f3);
    return 0;
}
