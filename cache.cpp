#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <map>
#include <queue>
using namespace std;
int main()
{
 FILE* f;
 int mode;
 /*
 First In First Out                     
 */
 cout<<"FIFO: "<<endl;
 cout<<"Size:               ";
 cout<<"Miss:               ";
 cout<<"Hit:               ";
 cout<<"Page Fault Ratio:               "<<endl;
 for(mode=64;mode<=512;mode*=2)
 {
    f=fopen("trace.txt","r");
 	char* input=new char[20];
 	int miss=0;
	int hit=0;
 	float ratio;
 	map<string,int> page;
 	queue<string>  replace;
 	int size=0;
 	while(fgets(input,20,f)!=NULL)
 	{
 	 char temp[5];	
 	 strncpy(temp,input+3,5);
 	 map<string, int>::iterator it=page.find(temp);
     if(it==page.end()) //not found
     {
     	miss++; size++;
     	if(size>mode)
     	{ 
		 page.erase(replace.front());
		 replace.pop();	
     	}
         page[temp]=0;
     	 replace.push(temp);
     }
     else
     {
     	hit++;
     }
 	}
 	ratio=(float)miss/(float)(hit+miss);
 	cout<<mode<<"                  "<<miss<<"                "<<hit<<"                "<<ratio<<endl;
 	fclose(f);
 }
/*
Least Recently Used
*/ 
 cout<<"LRU: "<<endl;
 cout<<"Size:               ";
 cout<<"Miss:               ";
 cout<<"Hit:               ";
 cout<<"Page Fault Ratio:               "<<endl;
 for(mode=64;mode<=512;mode*=2)
 {
    f=fopen("trace.txt","r");
 	char* input=new char[20];
 	int miss=0;
	int hit=0;
 	float ratio=0;
 	map<string,int> page;
 	map<int,string>  replace;
 	int size=0;
 	int id=0;
 	int re=0;
 	while(fgets(input,20,f)!=NULL)
 	{
 	 char temp[5];	
 	 strncpy(temp,input+3,5);
     if(page.find(temp)==page.end()) //not found
     {
     	miss++; size++; id++;
     	if(id>mode)
     	{ 
     	 while(replace.find(++re)==replace.end())
     	 {;}
     	 page.erase(replace[re]);
		 replace.erase(re);
     	}
         page[temp]=size;
     	 replace[size]=temp;
     }
     else
     {
     	hit++;
     	size++;
     	int num=page.find(temp)->second;
     	page.find(temp)->second=size;
		replace.erase(num);
     	replace[size]=temp;
     }
 	}
 	ratio=(float)miss/(float)(hit+miss);
 	cout<<mode<<"                  "<<miss<<"                "<<hit<<"                "<<ratio<<endl;
 	fclose(f);
 }
 return 0;	
}
