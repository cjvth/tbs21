#include<iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int BLOCK_SIZE= 1;
int vi(int a)
{
	for(int i=7;i>=0;--i)
	{
		cout<<((a & (1<<i))>>i);
	}
	cout<<endl;
}
int encoder(FILE* r_fifo, FILE* w_fifo)
{
   char buf[BLOCK_SIZE];
   char buf2[BLOCK_SIZE*2];

   long s;
   s= fread( buf, sizeof(char), BLOCK_SIZE, r_fifo);
    for(;s>0;)
    {
	   int k=0;

	   for(int i=0;i<s;++i)
	   {
	   /*	if(((int)buf[i]==9 && (int)buf[i+1]==9) && ((int)buf[i+2]==9 && (int)buf[i+3]==9))
	   	{
	   		cout<<"EEEEEEEEE";
	   	}*/
	   	// cout<<i<<": "<<buf[i]<<" s="<<s<<" ";
	   	 for(int j=0;j<2;++j)
	   	 {
	   	    int a=0;
	   	 	a= a | (buf[i] & (1<<0));
	   	 	a= a | (buf[i] & (1<<1));
	   	 	a= a | (buf[i] & (1<<2));
	   	 	a= a | ((buf[i] & (1<<3))<<1);
	   	 	a= a | (((((a&(1<<0))>>0) + ((a&(1<<2))>>2) + ((a&(1<<4))>>4))%2)<<6) ;
	   	 	a= a | (((((a&(1<<0))>>0) + ((a&(1<<1))>>1) + ((a&(1<<4))>>4))%2)<<5) ;
	   	 	a= a | (((((a&(1<<0))>>0) + ((a&(1<<2))>>2) + ((a&(1<<1))>>1))%2)<<3) ;
	  	 //	cout<<(int)buf[i]<<" "<<a<<" ";
	   //	 vi(a);
	   	 	buf2[k]=a;
		 //		cout<<buf2[k]<<" ";
	   	 	++k;
	  	 //cout<<(int)buf[i]<<" ";
	   	 	buf[i]=(buf[i]>>4);
	   	 //	cout<<(int)buf[i]<<" ";
	   	 }
	   	// cout<<endl;

	   }
	//   cout<<"s"<<endl;
//  buf[BLOCK_SIZE*2]='\0';
     fwrite(buf2, sizeof(char), s*2, w_fifo);
     s= fread(buf, sizeof(char), BLOCK_SIZE, r_fifo);
    // cout<<endl;
    }
 return 0;
}
int decoder(FILE* r_fifo, FILE* w_fifo)
{
   char buf[BLOCK_SIZE*2];
	char buf2[BLOCK_SIZE];
   long s;
int i;
   s= fread( buf, sizeof(char), BLOCK_SIZE*2, r_fifo);
   for(;s>0;)
    {
    	int k=0;

    	for(i=0;i<s/2;++i)
    	{
  	//cout<<s<<" "<<i<<" ";
    			for(int j=0;j<2;++j)
    			{
    			//	cout<<buf[k]<<endl;
    			//	vi(buf[k]);
    				int a,b,c;
	    			int el=0;
	    			a=((((buf[k]&(1<<0))>>0) + ((buf[k]&(1<<2))>>2) + ((buf[k]&(1<<4))>>4))%2) ;
	    			b=((((buf[k]&(1<<0))>>0) + ((buf[k]&(1<<1))>>1) + ((buf[k]&(1<<4))>>4))%2) ;
	    			c=((((buf[k]&(1<<0))>>0) + ((buf[k]&(1<<2))>>2) + ((buf[k]&(1<<1))>>1))%2) ;
	    		/*	cout<<"a= "<<a<<": "<<((buf[k]&(1<<0))>>0)<<" "<<((buf[k]&(1<<2))>>2)<<" "<<((buf[k]&(1<<4))>>4)<<endl;
	    			cout<<"b= "<<b<<": "<<((buf[k]&(1<<0))>>0)<<" "<<((buf[k]&(1<<1))>>1)<<" "<<((buf[k]&(1<<4))>>4)<<endl;
	    			cout<<"c= "<<c<<": "<<((buf[k]&(1<<0))>>0)<<" "<<((buf[k]&(1<<2))>>2)<<" "<<((buf[k]&(1<<1))>>1)<<endl;*/
	    		/*	if((a+b+c)%2)
	    			{*/
	    		//	vi(buf[k]);
	    				int num=0,e=0;
	    				if(((buf[k] & (1<<6))>>6) !=a) {num+=1;e=1;}
	    				if(((buf[k] & (1<<5))>>5) !=b) {num+=2;e=1;}
	    				if(((buf[k] & (1<<3))>>3) !=c) {num+=4;e=1;}
	    			//	cout<<((buf[k] & (1<<6))>>6)<<" "<<((buf[k] & (1<<5))>>5)<<" "<<((buf[k] & (1<<3))>>3);
	    				num=7-num;
	    				if(e)
	    				{
	    			//		cout<<"error "<<num<<endl;
	    					buf[k]=(buf[k] ^ (1<<num));
	    				}
	    		//	}
	    			buf[k]=(buf[k] & 23);
	    			buf[k]= (buf[k]|((buf[k]>>4)<<3));
	    			buf[k] &= 15;
	    			++k;
    			}
    			buf2[i]=((buf[k-1]<<4)| (buf[k-2]));
				buf[k-1]=0;
				buf[k-2]=0;
    			//cout<<(int)buf[k-1]<<" "<<(int)buf[k-2]<<" "<<buf2[i]<<" h "<<endl;
			//	cout<<buf2[i]<<" <- "<<endl;
   		 }
     if(s>1) fwrite(buf2, sizeof(char), s/2, w_fifo);
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
