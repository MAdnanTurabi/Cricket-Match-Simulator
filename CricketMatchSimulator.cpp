#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

//function for total overs
int TotalOvers(int balls)
{
return balls/6;
}

//this function draws the final scorecard
void FinalScoreBoard()
{
cout<<"Press enter to view score board!"<<endl;
cin.get();

//reading from file to display final scoreboard


ifstream indata2;
string num;
indata2.open("Myfile.txt");
if(!indata2)
{
cout<<"Error"<<endl;
}

indata2 >>num;
while(!indata2.eof())
{
cout<<num<<endl;
indata2 >>num;
}
indata2.close();

cout<<"\n\n---------------------------------------------------\n\n";

ifstream in;

in.open("Myfile2.txt");
if(!in)
{
cout<<"Error"<<endl;
}

in >>num;
while(!in.eof())
{
cout<<num<<endl;
in >>num;
}
in.close();
EXIT_SUCCESS;
}





//function to draw scoreboard repeatedly
void ScoreBoard(int score,int total_score,string Batter,string Runner,int totalwickets,string Baller,int balls,float runrate)
{
cout<<"--------------------------------------------------------------------------------------"<<endl;
cout<<"Batter: "<<Batter<<"  Scored "<<"\t"<<score<<"\t\t"<<"Score/Wickets: "<<total_score<<"/"<<totalwickets<<endl;
cout<<"Runner: "<<Runner<<"\t\t\t\t"<<"TotalOvers: "<<TotalOvers(balls)<<endl<<endl;
cout<<"RunRate:"<<runrate<<endl;
cout<<"\nBaller:"<<Baller<<endl;
cout<<"--------------------------------------------------------------------------------------"<<endl;
}

//function made to start the next innings
int secondinn(bool bat)
{
if(bat==true)
{
bat=false;
return bat;
}
else if(bat==false)
{
bat=true;
return bat;
}
return bat;
}

//function for batting board
void BattingBoard(int score,int batter)
{
int RunsScored[11][1]={0};
RunsScored[batter][1]=score;
}
//function for bowling board
void BowlingBoard(int baller)
{
int WicketsTaken[11][1]={0};
WicketsTaken[baller][1] +=1;
}
//function for total wickets
int TotalWickets(int totalwickets)
{
totalwickets +=1;
return totalwickets;
}


//function for run rate
float RunRate(float score,float overs)
{
float r = score/overs;
return r;
}

//function for total score
int TotalScore(string BattingTeam[11],string BallingTeam[11],int x,bool bat,int n,int target)
{
int total_score=0;
int score=0;
int RunsScored[11][2]={0};
int WicketsTaken[11][2]={0};
int totalwickets=0;
int balls=0;
int overs;
int batter=0;
int runner=1;
float runrate=0.0;
int baller=10;



//main loop for simulating match


for(int i=0;i<x;i++)
{
for(int i=0;i<6;i++)
{
score = (rand()%7) - 1;
if(score == -1)
{
WicketsTaken[baller][1] +=1;
BowlingBoard(baller);
cout<<"Press enter to bowl!"<<endl;
cin.get();
system("clear");
totalwickets=TotalWickets(totalwickets);
cout<<"-----------------------------------------------------------------"<<endl;
cout<<BattingTeam[batter]<<" bowled out by: "<<BallingTeam[baller]<<endl;
cout<<"-----------------------------------------------------------------"<<endl;

//bringing in new batter after out

if(runner>batter)
{
batter=runner+1;
}
else if(runner<batter)
{
batter=batter+1;
}


}
else if(score !=-1)
{
BattingBoard(score,batter);
RunsScored[batter][1] +=score;
total_score +=score;

cout<<"Press enter to bowl!"<<endl;
cin.get();
system("clear");

ScoreBoard(score,total_score,BattingTeam[batter],BattingTeam[runner],totalwickets,BallingTeam[baller],balls,runrate);

//ending the match if target score is achieved in second innings
if(total_score>target && bat == true)
{
cout<<"Match Ended, Team 1 has won!"<<endl;
ofstream fout2("Myfile2.txt");
if(fout2.is_open())
{
fout2<<"---------------------------------------------------"<<endl;
fout2<<"Second_Innings"<<endl;
fout2<<"---------------------------------------------------"<<endl<<endl<<endl;

fout2<<"---------------------------------------------------"<<endl;
fout2<<"Batters||Runs"<<endl;
fout2<<"---------------------------------------------------"<<endl;


//storing second inning details into a file
for(int i = 0; i<11 ; i++)
{
fout2 << BattingTeam[i] <<"||"<< RunsScored[i][1]<<endl;
}
}

if(fout2.is_open())
{
fout2<<"---------------------------------------------------"<<endl;
fout2<<"Ballers||Wickets"<<endl;
fout2<<"---------------------------------------------------"<<endl;
for(int i = 0; i<11 ; i++)
{
fout2 << BallingTeam[i] <<"||"<< WicketsTaken[i][1]<<endl;
}
}
FinalScoreBoard();
return 0;
}



else if(total_score>target && bat == false)
{
cout<<"Match Ended, Team 2 has won!"<<endl;
ofstream fout2("Myfile2.txt");
if(fout2.is_open())
{
fout2<<"---------------------------------------------------"<<endl;
fout2<<"Second_Innings"<<endl;
fout2<<"---------------------------------------------------"<<endl<<endl<<endl;

fout2<<"---------------------------------------------------"<<endl;
fout2<<"Batters||Runs"<<endl;
fout2<<"---------------------------------------------------"<<endl<<endl;

for(int i = 0; i<11 ; i++)
{
fout2 << BattingTeam[i] <<"||"<< RunsScored[i][1]<<endl;
}
}

if(fout2.is_open())
{
fout2<<"---------------------------------------------------"<<endl;
fout2<<"Ballers||Wickets"<<endl;
fout2<<"---------------------------------------------------"<<endl;
for(int i = 0; i<11 ; i++)
{
fout2 << BallingTeam[i] <<"||"<< WicketsTaken[i][1]<<endl;
}
}

FinalScoreBoard();
return 0;
}

//if statement to change batter at odd score

if(score ==1 || score==3 ||score==5 )
{
int temp;
temp=batter;
batter=runner;
runner=temp;
}

}
balls++;
cout<<"\n\nTotal Balls:"<<balls<<endl;

}
runrate=RunRate(total_score,TotalOvers(balls));

baller -=1;
int temp2;
temp2=batter;
batter=runner;
runner=temp2;
overs=TotalOvers(balls);
cout<<"\n\nOver Up! New Baller: "<<BallingTeam[baller]<<endl;

}




//storing data of first innings in a file

if(n==1)
{

ofstream fout("Myfile.txt");
if(fout.is_open())
{
fout<<"---------------------------------------------------"<<endl;
fout<<"First_Innings"<<endl;
fout<<"---------------------------------------------------"<<endl<<endl<<endl;
fout<<"---------------------------------------------------"<<endl;
fout<<"Batters||Runs"<<endl;
fout<<"---------------------------------------------------"<<endl;
for(int i = 0; i<11 ; i++)
{
fout << BattingTeam[i] <<"||"<< RunsScored[i][1]<<endl;
}
}

if(fout.is_open())
{
fout<<"---------------------------------------------------"<<endl;
fout<<"Ballers||Wickets"<<endl;
fout<<"---------------------------------------------------"<<endl;
for(int i = 0; i<11 ; i++)
{
fout << BallingTeam[i] <<"||"<< WicketsTaken[i][1]<<endl;
}
}
}


if(n==2)
{
ofstream fout2("Myfile2.txt");
if(fout2.is_open())
{
fout2<<"---------------------------------------------------"<<endl;
fout2<<"Second_Innings"<<endl;
fout2<<"---------------------------------------------------"<<endl<<endl<<endl;
fout2<<"---------------------------------------------------"<<endl;
fout2<<"Batters||Runs"<<endl;
fout2<<"---------------------------------------------------"<<endl;
for(int i = 0; i<11 ; i++)
{
fout2 << BattingTeam[i] <<"||"<< RunsScored[i][1]<<endl;
}
}

if(fout2.is_open())
{
fout2<<"---------------------------------------------------"<<endl;
fout2<<"Ballers||Wickets"<<endl;
fout2<<"---------------------------------------------------"<<endl;
for(int i = 0; i<11 ; i++)
{
fout2 << BallingTeam[i] <<"||"<< WicketsTaken[i][1]<<endl;
}
}
}

//determining which team wins if target score not reached in second innings
if(n==2&&bat==true)
{
cout<<"Team 2 has won the match!"<<endl;
FinalScoreBoard();
}

if(n==2&&bat==false)
{
cout<<"Team 1 has won the match!"<<endl;
FinalScoreBoard();
}

return total_score;
}







int main()
{

//Taking number of overs as input from user
int N;
cout<<"Enter number of overs:"<<endl;  
cin>>N;



//configuration file created and number of overs 'N' stored in it.
ofstream MyFile("configuration.txt");
MyFile<<N;
MyFile.close();
system("clear");

int overs;
//Reading overs from file
ifstream obj("configuration.txt");
obj>>overs;
obj.close();
cout<<"The match will be played for "<<overs<<" overs as read from the configuration file!"<<endl;


//Initializing teams and their players
string Team1Names[11]={"amir","hamza","adnan","qureshi","ahmed","turabi","muhammad","ruhail","attique","abdullah","khan"};
string Team2Names[11]={"fizzie","mark","tom","hardy","joe","sugg","tufail","illinois","max","matt","payne"};




//for toss
int toss;
srand(time(0));
toss = rand()%2+1;
bool bat;


if(toss==1)
{
bat=true;
}
else if(toss==2)
{
bat=false;
}


int target=0;

if(bat==true)
{
cout<<"Team 1 has won the toss and will bat first!"<<endl;
cout<<"Press enter to continue and play the first ball"<<endl;
cin.get();
cin.get();
target=TotalScore(Team1Names,Team2Names,overs,bat,1,99999999);
}

if(bat==false)
{
cout<<"Team 2 has won the toss and will bat first!"<<endl;
cout<<"Press enter to continue and play the first ball"<<endl;
cin.get();
cin.get();
target=TotalScore(Team2Names,Team1Names,overs,bat,1,999999999);
}

bat=secondinn(bat);
//calling score function again for second innings
if(bat==true)
{
cout<<"Team 1 will now bat in the second innings"<<endl;
cout<<"Press enter to continue and play the first ball"<<endl;
cin.get();
cin.get();
TotalScore(Team1Names,Team2Names,overs,bat,2,target);
}

if(bat==false)
{
cout<<"Team 2 will now bat in the second innings"<<endl;
cout<<"Press enter to continue and play the first ball"<<endl;
cin.get();
cin.get();
TotalScore(Team2Names,Team1Names,overs,bat,2,target);
}
     



}





