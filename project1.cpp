#include <bits/stdc++.h>
#define s 4
int N;
int limit,c=0,input[100000],pInput[100000],pivotpoints[s],sublists[100000],indices[100000],counts[s],countsoffset[s],histbin[100000]={0}; 
int rowindex,maxcol,value,position;
void bucketcount()
{
	int i,j,index,jump;
	for(i=0;i<N;i++)
	{
		index=s/2-1;jump=s/4;
		int pivot=pivotpoints[index];
		int element=input[i];
		while(jump>=1)
		{
			index=(element<pivot)?(index-jump):(index+jump);
			pivot=pivotpoints[index];
			jump/=2;
			index=(element<pivot)? (index):(index+1);
			sublists[i]=index;
			indices[i]=counts[index];
			counts[index]++;
		}
	}
}
void refining()
{
	int elemsneeded=N/s,range;
	for(int i=0;i<s;i++)
	{
		range=N/s*(i+1);
		while(counts[i]>=elemsneeded)
		{
			pivotpoints[i+1]+=(elemsneeded/counts[i])*range;
			elemsneeded=N/s;
			counts[i]-=elemsneeded;			
		}
		elemsneeded-=counts[i];
		pivotpoints[i+1]+=range;
	}
}
void bucketsort()
{
	int newpos,i;
	for(i=0;i<N;i++)
	{
		newpos=countsoffset[sublists[i]]+indices[i];
		pInput[newpos]=input[i];
	}
}
void histogram_keys()
{
	for(int i=0;i<s;i++)
	{		
		rowindex=i;
		for(int j=0;j<counts[rowindex];j++)
		{
			histbin[pInput[countsoffset[rowindex]+j]]++;
		}
	}
}
void rank_and_permute()
{
	for(int i=0;i<s;i++)
	{
		rowindex=i;
		for(int j=0;j<counts[rowindex];j++)
		{
			value=pInput[countsoffset[rowindex]+j];
			position=histbin[value];
			histbin[value]++;
			input[position]=value;
		}
	}
}
int main(){
	clock_t seconds1,seconds2,t,start1,start2,end1,end2,timer1,timer2;
	int i,j,inde,jump,x=0,temp;
	printf("Enter limit\n");
	scanf("%d",&limit);
	//Maximum of elements in the input array
	printf("Enter the value of N\n");
	scanf("%d",&N);
	for(int i=0;i<N;i++)
			input[i]=rand()%limit;
	seconds1=clock();
	start1=clock();
	//Initial pivot points
	for(i=0;i<s;i++){
		c+=limit/s;
		pivotpoints[i]=c;
	}
	bucketcount();
	for(i=1;i<s;i++)
		countsoffset[i]=countsoffset[i-1]+counts[i-1];
	bucketsort();
	/*printf("Pinput\n ");
	for(i=0;i<N;i++)	
		printf("%d ",pInput[i]);
	printf("\n");*/
	end1=clock();
	start2=clock();
	histogram_keys();
	i=0;
	while(i<=limit)
	{
		temp=histbin[i];
		histbin[i]=x;
		x+=temp;
		i++;
	}
	rank_and_permute();
	end2=clock();
	for(i=0;i<N;i++)
		printf("%d ",input[i]);
	
	seconds2=clock();
	t=seconds2-seconds1;
	timer1=start1-end1;
	timer2=start2-end2;
	double time_taken=(double)t/CLOCKS_PER_SEC;
	double time_taken1=(double)timer1/CLOCKS_PER_SEC;
	double time_taken2=(double)timer2/CLOCKS_PER_SEC;
	printf("\ntime taken in seconds :%lf",time_taken);
	printf("\ntime taken in seconds for bucket partition:%lf",time_taken1);
	printf("\ntime taken in seconds for histogram:%lf",time_taken2);
}


