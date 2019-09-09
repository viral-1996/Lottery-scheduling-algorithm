#include<stdio.h>
#include<math.h>
#include<string.h>
#include<limits.h>
#include<stdlib.h>
#include<time.h>
typedef struct process
{
int number,priority,tickets,burst_time;
int available,rt;
}process;
process jobs[10];
int n,total_tickets,remaining,out[10],total_burst_time=0;

void input()
{
int i;
printf("Enter the number of process:");
scanf("%d",&n);
for(i=1;i<=n;i++)
{
printf("Enter the priority of process %d:",i);
scanf("%d",&jobs[i-1].priority);
printf("Enter the burst time of process %d:",i);
scanf("%d",&jobs[i-1].burst_time);
jobs[i-1].number=i;
jobs[i-1].available=1;
total_burst_time+=jobs[i-1].burst_time;
}
}
void assign_tickets()
{
int i,total_priority=0;
for(i=0;i<n;i++)
{
total_priority+=jobs[i].priority;
}
total_tickets=total_priority*10;
for(i=0;i<n;i++)
{
jobs[i].tickets=jobs[i].priority*10;
}
}

void conduct_lottery()
{
int winner,total=0,i;
srand(time(NULL));
do
{
winner=rand();
}while(winner>total_tickets);
i=0;
while(winner>total)
{
if(jobs[i].available)
{
total+=jobs[i].tickets;
}
i++;
}
i--;
out[n-remaining]=jobs[i].number;
remaining--;
jobs[i].available=0;
total_tickets=jobs[i].tickets;
}

void output()
{
int i,time=0;
float atat=0.0,awt=0.0;
printf("Time Slot\tJob No.\n");
for(i=0;i<n;i++)
{
printf("%3d-%d\t\t%d\n",time,time+jobs[out[i]-1].burst_time,out[i]);
jobs[out[i]-1].rt=time;
time+=jobs[out[i]-1].burst_time;
}
for(i=0;i<n;i++)
{
atat+=jobs[i].rt;
awt+=jobs[i].burst_time;
}
printf("\Average waiting time=%f",atat/n);
awt+=atat;
printf("\nAverage turnaround time=%f",awt/n);
}

void main()
{
input();
remaining=n;
assign_tickets();
while(remaining)
{
conduct_lottery();
}
output();
getch();
}
