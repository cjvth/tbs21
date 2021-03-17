#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int BLOCK_SIZE= 1000;

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
	   	 	buf2[k]=a;
	   	 	++k;
		 	buf[i]=(buf[i]>>4);
	   	 }	   		
	   }
     fwrite(buf2, sizeof(char), k, w_fifo);
     s= fread(buf, sizeof(char), BLOCK_SIZE, r_fifo);
    }
 return 0;
}
