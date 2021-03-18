#include<iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int BLOCK_SIZE= 1000;

int resize(char * buf,int * arx)
{
	int l,t=0,k=1;
	l=buf[0];
	for(int i=1;buf[i]!='\0';++i)
	{
		if(buf[i]==l && k<255)
		{
			++k;
			
		}
		else
		{
			arx[t]=l;
			arx[t+1]=k;
			t+=2;
			l=buf[i];
			k=1;	
		}
	}
	arx[t]=l;
	arx[t+1]=k;
	t+=2;
	return t;
}
int main()
{
	char buf[BLOCK_SIZE];
	int arx[BLOCK_SIZE];
		cin>>buf;
	int t =resize(buf,arx);
	for(int i=0;i<t;i+=2)
	{
		cout<<arx[i]<<" "<<arx[i+1]<<endl;	
	}

}
