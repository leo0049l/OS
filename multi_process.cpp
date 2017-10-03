#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
using namespace std;
int main()
{
 int size; cin>>size;
 unsigned int sum;
 int ida,idb,idc; 
 unsigned int* addra,*addrb,*addrc;
 int counter=0;
 struct timeval start,end;
 int sec,usec;
 int singlesum;
 int c;
 int count;
 int last;
 int current;
 int end1;
 pid_t pid[17];
 unsigned int total;
 ida=shmget(IPC_PRIVATE,sizeof(unsigned int)*size*size,IPC_CREAT|0666);
 idb=shmget(IPC_PRIVATE,sizeof(unsigned int)*size*size,IPC_CREAT|0666);
 idc=shmget(IPC_PRIVATE,sizeof(unsigned int)*size*size,IPC_CREAT|0666);
 if(ida<0) cout<<"ida error"<<endl;
 if(idb<0) cout<<"idb error"<<endl;
 if(idc<0) cout<<"idc error"<<endl;
 for(int i=1;i<=16;i++)
 {
   //count time
   gettimeofday(&start,0);
   //
      addra=(unsigned int*)shmat(ida,NULL,0);
      addrb=(unsigned int*)shmat(idb,NULL,0);
      addrc=(unsigned int*)shmat(idc,NULL,0);
 for(int a=0;a<size;a++)
 {
   for(int b=0;b<size;b++)
   {
    addra[a*size+b]=counter;
    addrb[a*size+b]=counter;
    counter++;
   }
 }
  counter=0;
  
  count=size/i;
  last=size%i;
  current=-count;
  end1=0;
  //fork//
  for(c=1;c<=i;c++)
  {
     if(last>0 && c==i)
    end1=end1+count+last;
    else
    end1+=count;
    current+=count;
    if((pid[c]=fork())==0)
     break;
  }
   for(c=1;c<=i;c++)
  {
   if(pid[c]==0)
   {  
      //different work//
    for(int k=current;k<end1;k++)
    {
        for(int r=0;r<size;r++)
        {
         singlesum=0;
         for(int m=0;m<size;m++)
         {
          singlesum+=addra[k*size+m]*addrb[m*size+r];
         }
         addrc[k*size+r]=singlesum; singlesum=0;
        }
    }
    shmdt(addra);
    shmdt(addrb);
    exit(0);
    //different work//
   }

    for(int d=1;d<=i;d++)
   {
    wait(NULL);
   }
}
   total=0;
  for(int a=0;a<size;a++)
  {
    for(int b=0;b<size;b++)
    {
     total+=addrc[a*size+b];
     addrc[a*size+b]=0;
    }
  }
  shmdt(addrc);
     gettimeofday(&end,0);
     sec=end.tv_sec-start.tv_sec;
     usec=end.tv_usec-start.tv_usec;
   printf("Multiplying matrices using %d process\n",i);
   printf("Elapsed time: %f s ", (sec*1000+(usec/1000.0))/1000);
   printf("Check: %u\n",total);
  //fork//

 }  shmctl(ida,IPC_RMID,NULL);
  shmctl(idb,IPC_RMID,NULL);
  shmctl(idc,IPC_RMID,NULL);
return 0;
}
