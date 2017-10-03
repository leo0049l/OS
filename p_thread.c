#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
int* number;
int size;
sem_t mutex[16];
sem_t done[9];
sem_t mas;
int queue[16]={0};
struct pointer
{
 int left;
 int right;
}ptr[16];
//struct pointer ptr[16];
void partition1()
{
 int l=ptr[1].left;
 int r=ptr[1].right;
 int pivot=l;
 int i=l-1,j=r+1;
 while(1)
 {
  for(;number[l]>number[++i] && i!=size;);
  for(;number[l]<number[--j] && j!=0;);
  if(i>=j) break;
  else
  {
   int temp;
   temp=number[j];
   number[j]=number[i];
   number[i]=temp;   
  }
 }	 
 ptr[2].left=l;
 ptr[2].right=i-1;
 ptr[3].left=j+1;
 ptr[3].right=r;
 sem_post(&mutex[2]);
 sem_post(&mutex[3]);
}
void partition2()
{	
 sem_wait(&mutex[2]);
 int l=ptr[2].left;
 int r=ptr[2].right;
 int pivot=l;
 int i=l-1,j=r+1;
 while(1)
 {
  for(;number[l]>number[++i] && i!=size;);
  for(;number[l]<number[--j] && j!=0;);
  if(i>=j) break;
  else
  {
   int temp;
   temp=number[j];
   number[j]=number[i];
   number[i]=temp;   
  }
 }	 
 ptr[4].left=l;
 ptr[4].right=i-1;
 ptr[5].left=j+1;
 ptr[5].right=r;
 sem_post(&mutex[4]);
 sem_post(&mutex[5]);
}
void partition3()
{	
 sem_wait(&mutex[3]);	
 int l=ptr[3].left;
 int r=ptr[3].right;
 int pivot=l;
 int i=l-1,j=r+1;
 while(1)
 {
  for(;number[l]>number[++i] && i!=size;);
  for(;number[l]<number[--j] && j!=0;);
  if(i>=j) break;
  else
  {
   int temp;
   temp=number[j];
   number[j]=number[i];
   number[i]=temp;   
  }
 }	 
 ptr[6].left=l;
 ptr[6].right=i-1;
 ptr[7].left=j+1;
 ptr[7].right=r;
 sem_post(&mutex[6]);
 sem_post(&mutex[7]);
}
void partition4()
{	
 sem_wait(&mutex[4]);
 int l=ptr[4].left;
 int r=ptr[4].right;
 int pivot=l;
 int i=l-1,j=r+1;
 while(1)
 {
  for(;number[l]>number[++i] && i!=size;);
  for(;number[l]<number[--j] && j!=0;);
  if(i>=j) break;
  else
  {
   int temp;
   temp=number[j];
   number[j]=number[i];
   number[i]=temp;   
  }
 }	 
 ptr[8].left=l;
 ptr[8].right=i-1;
 ptr[9].left=j+1;
 ptr[9].right=r;
 sem_post(&mutex[8]);
 sem_post(&mutex[9]);
}
void partition5()
{	
 sem_wait(&mutex[5]);	
 int l=ptr[5].left;
 int r=ptr[5].right;
 int pivot=l;
 int i=l-1,j=r+1;
 while(1)
 {
  for(;number[l]>number[++i] && i!=size;);
  for(;number[l]<number[--j] && j!=0;);
  if(i>=j) break;
  else
  {
   int temp;
   temp=number[j];
   number[j]=number[i];
   number[i]=temp;   
  }
 }	 
 ptr[10].left=l;
 ptr[10].right=i-1;
 ptr[11].left=j+1;
 ptr[11].right=r;
 sem_post(&mutex[10]);
 sem_post(&mutex[11]); 
}
void partition6()
{	
 sem_wait(&mutex[6]);	
 int l=ptr[6].left;
 int r=ptr[6].right;
 int pivot=l;
 int i=l-1,j=r+1;
 while(1)
 {
  for(;number[l]>number[++i] && i!=size;);
  for(;number[l]<number[--j] && j!=0;);
  if(i>=j) break;
  else
  {
   int temp;
   temp=number[j];
   number[j]=number[i];
   number[i]=temp;   
  }
 }	 
 ptr[12].left=l;
 ptr[12].right=i-1;
 ptr[13].left=j+1;
 ptr[13].right=r;
 sem_post(&mutex[12]);
 sem_post(&mutex[13]);
}
void partition7()
{ 
 sem_wait(&mutex[7]);	
 int l=ptr[7].left;
 int r=ptr[7].right;
 int pivot=l;
 int i=l-1,j=r+1;
 while(1)
 {
  for(;number[l]>number[++i] && i!=size;);
  for(;number[l]<number[--j] && j!=0;);
  if(i>=j) break;
  else
  {
   int temp;
   temp=number[j];
   number[j]=number[i];
   number[i]=temp;   
  }
 }	 
 ptr[14].left=l;
 ptr[14].right=i-1;
 ptr[15].left=j+1;
 ptr[15].right=r;
 sem_post(&mutex[14]);
 sem_post(&mutex[15]); 
}	
void sort8()
{	
  sem_wait(&mutex[8]);	
  int l=ptr[8].left;
  int r=ptr[8].right;
  int i,j;
  for(i=l;i<=r;i++)
  {
   for(j=l;j<r;j++)
   {
   	if(number[j]>number[j+1])
   	{
   		int temp=number[j];
   		number[j]=number[j+1];
   		number[j+1]=temp;
   	}
   }
  }	
  sem_post(&done[1]);
}
void sort9()
{	
  sem_wait(&mutex[9]);		
  int l=ptr[9].left;
  int r=ptr[9].right;
  int i,j;
  for(i=l;i<=r;i++)
  {
   for(j=l;j<r;j++)
   {
   	if(number[j]>number[j+1])
   	{
   		int temp=number[j];
   		number[j]=number[j+1];
   		number[j+1]=temp;
   	}
   }
  }
  sem_post(&done[2]);	
}
void sort10()
{	
  sem_wait(&mutex[10]);		
  int l=ptr[10].left;
  int r=ptr[10].right;
  int i,j;
  for(i=l;i<=r;i++)
  {
   for(j=l;j<r;j++)
   {
   	if(number[j]>number[j+1])
   	{
   		int temp=number[j];
   		number[j]=number[j+1];
   		number[j+1]=temp;
   	}
   }
  }
  sem_post(&done[3]);	
}
void sort11()
{
  sem_wait(&mutex[11]);		
  int l=ptr[11].left;
  int r=ptr[11].right;
  int i,j;
  for(i=l;i<=r;i++)
  {
   for(j=l;j<r;j++)
   {
   	if(number[j]>number[j+1])
   	{
   		int temp=number[j];
   		number[j]=number[j+1];
   		number[j+1]=temp;
   	}
   }
  }	
  sem_post(&done[4]);
}
void sort12()
{
  sem_wait(&mutex[12]);		
  int l=ptr[12].left;
  int r=ptr[12].right;
  int i,j;
  for(i=l;i<=r;i++)
  {
   for(j=l;j<r;j++)
   {
   	if(number[j]>number[j+1])
   	{
   		int temp=number[j];
   		number[j]=number[j+1];
   		number[j+1]=temp;
   	}
   }
  }
  sem_post(&done[5]);	
}
void sort13()
{
  sem_wait(&mutex[13]);		
  int l=ptr[13].left;
  int r=ptr[13].right;
  int i,j;
  for(i=l;i<=r;i++)
  {
   for(j=l;j<r;j++)
   {
   	if(number[j]>number[j+1])
   	{
   		int temp=number[j];
   		number[j]=number[j+1];
   		number[j+1]=temp;
   	}
   }
  }	
 sem_post(&done[6]); 
}
void sort14()
{
  sem_wait(&mutex[14]);		
  int l=ptr[14].left;
  int r=ptr[14].right;
  int i,j;
  for(i=l;i<=r;i++)
  {
   for(j=l;j<r;j++)
   {
   	if(number[j]>number[j+1])
   	{
   		int temp=number[j];
   		number[j]=number[j+1];
   		number[j+1]=temp;
   	}
   }
  }	
 sem_post(&done[7]); 
}
void sort15()
{
  sem_wait(&mutex[15]);		
  int l=ptr[15].left;
  int r=ptr[15].right;
  int i,j;
  for(i=l;i<=r;i++)
  {
   for(j=l;j<r;j++)
   {
   	if(number[j]>number[j+1])
   	{
   		int temp=number[j];
   		number[j]=number[j+1];
   		number[j+1]=temp;
   	}
   }
  }	
  sem_post(&done[8]);
}
void master()
{
	while(1)
	{
	sem_wait(&mas);	
	int i,j=0;
	for(i=1;i<16;i++)
	{
	  if(queue[i]==0)
	  {
	  queue[i]=1;
	  break;
      }
      else
      {
       j++;	
	   
      }
	}
    if(j==15) break;
	sem_post(&mas);
	if(i==1)
	partition1();
	else if(i==2)
	partition2();
	else if(i==3)
	partition3();
	else if(i==4)
	partition4();
	else if(i==5)
	partition5();
	else if(i==6)
	partition6();
	else if(i==7)
	partition7();
	else if(i==8)
	sort8();
	else if(i==9)
	sort9();
	else if(i==10)
	sort10();
	else if(i==11)
	sort11();
	else if(i==12)
	sort12();
	else if(i==13)
	sort13();
	else if(i==14)
	sort14();
	else if(i==15)
	sort15();
    }
	
	
}
int main()
{	
 struct timeval start,end;
 int sec,usec;
 int sec1,usec1;
 int s;
 for(s=1;s<=8;s++)
 {
  ///////////////////////////////////
   FILE* input;
 input=fopen("input.txt","r");
 int size;
 fscanf(input,"%d ",&size);
 number=malloc(sizeof(int)*size);
 int i;
  for(i=0;i<=15;i++)
 {
 	queue[i]=0;
 }
 for(i=0;i<size;i++)
 {
 fscanf(input,"%d ",&number[i]);	 
 }
 for(i=0;i<=15;i++)
 {
 	sem_init(&mutex[i],0,0);
 	
 }
 sem_init(&mas,0,1);
 for(i=0;i<=8;i++)
 {
 	sem_init(&done[i],0,0);
 } 
 ptr[1].left=0;
 ptr[1].right=size-1;

 gettimeofday(&start,0);
 ////////////////////////////	
  pthread_t tid[i];
  int j;
  for(j=0;j<s;j++)
  {	
   pthread_create(&tid[j],NULL,(void*)master,NULL);
  }
  ///////////////////////////
 sem_wait(&done[1]);
 sem_wait(&done[2]);
 sem_wait(&done[3]);
 sem_wait(&done[4]);
 sem_wait(&done[5]);
 sem_wait(&done[6]);
 sem_wait(&done[7]);
 sem_wait(&done[8]); 
 gettimeofday(&end,0);
 fclose(input);
 FILE* output;
 char buffer[12]="output1.txt";
 buffer[6]=s+'0';
 output=fopen(buffer,"w");
 for(i=0;i<size;i++)
 {
  fprintf(output,"%d ",number[i]);	
 } 
 fclose(output); 
 sec=end.tv_sec-start.tv_sec;
 usec=end.tv_usec-start.tv_usec;
 
 printf("%d threads\n",s);
 printf("Elapsed time: %f ms \n", (sec*1000+(usec/1000.0)));
 ///////////////////////////
 }
 return 0;	
}
