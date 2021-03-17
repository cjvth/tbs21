#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

const int BLOCK_SIZE= 1000;

int decoder(FILE* r_fifo, FILE* w_fifo,FILE* tracklog)
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
    			for(int j=0;j<2;++j)
    			{
    				int a,b,c;
	    			int el=0;
	    			a=((((buf[k]&(1<<0))>>0) + ((buf[k]&(1<<2))>>2) + ((buf[k]&(1<<4))>>4))%2);
	    			b=((((buf[k]&(1<<0))>>0) + ((buf[k]&(1<<1))>>1) + ((buf[k]&(1<<4))>>4))%2);
	    			c=((((buf[k]&(1<<0))>>0) + ((buf[k]&(1<<2))>>2) + ((buf[k]&(1<<1))>>1))%2);
	    			if((a+b+c)%2)
	    			{
	    				int num=0;
	    				if((buf[k]>>6) !=a) num+=1;
	    				if(((buf[k] & (1<<5))>>5) !=b) num+=2;
	    				if(((buf[k] & (1<<3))>>3) !=c) num+=4;
	    				num=7-num;
	    				buf[k]=(buf[k] ^ (1<<num));
	    			}
	    			buf[k]=(buf[k] & 23);
	    			buf[k]= (buf[k]|((buf[k]>>4)<<3));
	    			buf[k] &= 15;
	    			++k;
    			}
    			buf2[i]=((buf[k-1]<<4)| (buf[k-2]));		
   		 }
     if(s>1) fwrite(buf2, sizeof(char), s/2, w_fifo);
     s= fread(buf, sizeof(char), BLOCK_SIZE*2, r_fifo);     
	}

 return 0;
}
