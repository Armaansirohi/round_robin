#include<iostream>
#include<conio.h>
using namespace std;

class job{
public:
	int program_id,
	arrivle_time,
	brust_time,
   	completion_time,
   	remaining_brust_time;
}faculty[100], student[100], merge[200];

int n, faculty_counter=0, student_counter=0, merge_counter=0;
int quantum_time;

void welcome()
{
	cout<<"________________________________________________________________________\n";
	cout<<"------------------------------------------------------------------------\n";
	cout<<"WELCOME TO QUERY CENTER\n";
	cout<<"------------------------------------------------------------------------\n";
	cout<<"\n **INSTRUCTION TO BE FOLLOWED**";
	cout<<"\n1.Enter time in 24 hours format.For instance,10:30 am equal to 1030\n";
	cout<<"2.Enter query arrival time in ascending order, i.e., in real time arrival manner\n ";
	cout<<"----All Time units are in minutes.---- \n\n";
};

void input(){
	int map,  i, t;
	cout<<"Enter total no of queries: ";
	cin>>n;
	if(n==0)
	{ 
		cout<<"\n No queries\n";
	}
	else{
		cout<<"\nEnter Quanta for each Process: ";
		cin>>quantum_time;
		cout<<"\nEnter 1 for faculty and 2 for student\n";
		for(i=0; i<n; i++)
			{
			cout<<"\nJob Type (1/2): ";
			cin>>map;
			if(map==1){
				cout<<"Query Id: ";
				cin>>faculty[faculty_counter].program_id;
				cout<<"Arrival Time: ";
				cin>>t;
				if(t<1000 || t>1200)
				{
					cout<<"\nEnter Correct time";
					input();
				}
				else
				{
					faculty[faculty_counter].arrivle_time= t-1000;
				}
				cout<<"Resolving Time: ";
				cin>>faculty[faculty_counter].brust_time;
				faculty[faculty_counter].remaining_brust_time= faculty[faculty_counter].brust_time; 
				faculty_counter++;
			} else{
				cout<<"Query Id: ";
				cin>>student[student_counter].program_id;
				cout<<"Arrival Time: ";
				 cin>>t; 
				if(t<1000 || t>1200)
				{
					cout<<"\nEnter Correct time\n";
					input();
				}
				else 
				{
					student[student_counter].arrivle_time= t-1000;
				}
				cout<<"Resolving Time: ";
				cin>>student[student_counter].brust_time;
				student[student_counter].remaining_brust_time= student[student_counter].brust_time;
				student_counter++;
			}
		}
	}
}


void mergering()
{
	int isc=0, ifc= 0, min, flag;
	if( faculty_counter!=0  && student_counter!=0)
	{
		while(isc<student_counter && ifc<faculty_counter)
		{
			if(faculty[ifc].arrivle_time == student[isc].arrivle_time)
			{
				merge[merge_counter] = faculty[ifc];
				merge_counter++;
				ifc++;
				merge[merge_counter]= student[isc];
				merge_counter++;
				isc++;
			}
			else if(faculty[ifc].arrivle_time < student[isc].arrivle_time){
				merge[merge_counter]= faculty[ifc];
				merge_counter++;
				ifc++;
			}
			else if(faculty[ifc].arrivle_time > student[isc].arrivle_time){
				merge[merge_counter]= student[isc];
				merge_counter++;
				isc++;
			}
			else;
		}
		if(merge_counter != (faculty_counter+student_counter))
		{
			if(faculty_counter!=ifc)
			{
				while(ifc!=faculty_counter)
				{
					merge[merge_counter]= faculty[ifc];
					merge_counter++;
					ifc++;
				}
			}
			else if(student_counter!=isc)
			{
				while(isc!=student_counter)
				{
					merge[merge_counter]= student[isc];
					merge_counter++;
					isc++;
				}
			}
		}
	}
	else if(faculty_counter==0)
	{
		while(isc!=student_counter)
		{
			merge[merge_counter]= student[isc];
			merge_counter++;
			isc++;
		}
	}
	else if(student_counter==0)
	{
		while(ifc!=faculty_counter)
		{
			merge[merge_counter]= faculty[ifc];
			merge_counter++;
			ifc++;
		}
	}
	else 
	{
		cout<<"\n No valid Jobs available\n";
	}
}


void roundRobin(){
	int time= merge[0].arrivle_time, mark=0, cc=0, i, rc; //cc-completion counter
	while(time!=120 && cc!=merge_counter)
	{
		for(i=0; i<=mark; i++)
		{
			if(merge[i].remaining_brust_time > quantum_time)
			{
				time += quantum_time;
				merge[i].remaining_brust_time -= quantum_time;
			}
			else if(merge[i].remaining_brust_time <=quantum_time && merge[i].remaining_brust_time !=0)
			{
				time += merge[i].remaining_brust_time;
				merge[i].remaining_brust_time =0;
				merge[i].completion_time = time;
				cc++;
			}
			
		}
		int start = mark+1;
		for(rc= start; rc<merge_counter; rc++){
			if(merge[rc].arrivle_time <= time){
				mark++;
			}
		}
	}	
}


void print_val(){
	int i=0, total=0;
	float sum=0; 
	float avg;
	cout<<"\nSummary for the Execution\n";
	cout<<"\nQuery ID\tArrival Time\tRessolving Time\tCompletion Time\tTurn Around Time\tWaiting Time";
	for(i; i<merge_counter; i++)
	{
		cout<<"\n"
			<<merge[i].program_id
			<<"\t\t"<<(merge[i].arrivle_time+1000)
			<<"\t\t"<<merge[i].brust_time
			<<"\t\t"<<(merge[i].completion_time+1000)
			<<"\t\t"<<(merge[i].completion_time-merge[i].arrivle_time)
			<<"\t\t\t"
			<<((merge[i].completion_time-merge[i].arrivle_time)- merge[i].brust_time);
		
		total= merge[i].completion_time;
		sum+= (merge[i].completion_time-merge[i].arrivle_time);
	}
	avg = sum/merge_counter;
	cout<<"\n\nTotal time Spent for all queries: "<< total;
	cout<<"\nAverage query time:  "<<avg;
	cout<<"\nProcess Execution Complete";
}


int main()
{
	welcome();
	cout<<"********Press any key to continue************\n\n";
	getch();
	input();
	mergering();
	roundRobin();
	print_val();
}
