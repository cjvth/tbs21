#include <stdio.h>
#include <stdlib.h>

main(int argn,char* argv[])
{
 long l;
 char buf[1024];
 FILE* streamin;
 FILE* streamout;
 
 streamin=fopen(argv[1],"rb");
 streamout=fopen(argv[2],"wb");
 for(;!feof(streamin);)
  {
   l=fread(buf,1,1000,streamin);
   if(l>0)
    fwrite(buf,1,l,streamout);
  }
 fclose(streamin);
 fclose(streamout);

}