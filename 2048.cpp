#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cmath>
using namespace std;

char key=0;
int elm[4][4]={0};	//the matrix
bool Is_2048;
bool Will_Spawn[2];	//decide to spawn numbers

void Spawn()
{
	int x,y;
	bool P=false;
	srand(time(0));
	while(!P)
	{
		//spawn number 2 or 4 when there's a zero number
		//break the loop
		x=rand()%4;
		y=rand()%4;
		P=(elm[x][y]==0);
	}
	
	//only god know which number is it
	if (rand()%2==0)
		elm[x][y]=1;
	else
		elm[x][y]=2;
}

void Initialize()
{
	key=0;
	Is_2048=false;
	Will_Spawn[0]=true;
	Will_Spawn[1]=true;
	for(int y=0;y<4;++y)
	for(int x=0;x<4;++x)
		elm[x][y]=0;

	Spawn();
	Spawn();
}

void win()
{
	cout<<"You win.";
	Sleep(1000);
	system("pause");
	Initialize();
}

void output()
{
	//output the matrix
	for(int y=0;y<4;++y,cout<<'\n'<<'\n')
	for(int x=0;x<4;++x) {
		if (elm[y][x]>0)
			cout<<pow(2,elm[y][x])<<'\t';
		else 
			cout<<0<<'\t';
	}
}

void rotate(int times)
{
	//rotate the matrix
	//may be it can be improve
	for(int t=0;t<times;++t) {
		int tmp[4][4];
		for(int i=0;i<4;++i)
		for(int j=0;j<4;++j)
			tmp[i][j]=elm[i][j];
		for(int i=0;i<4;++i)
		for(int j=0;j<4;++j)
			elm[i][j]=tmp[3-j][i];
	}
}

bool MixUp(char direction='w')
{
	//add same numbers together
	//return true if mixup is succeed
	bool success=false;
	for(int j=0;j<4;++j)
	for(int i=1;i<4;++i)
		for (int k=1;k<=i&&elm[i][j]!=0;++k) {
			if (elm[i][j]==elm[i-k][j]) {
				if (direction!=key)
				//if the 'direction' is different to keyboard input
				//break the loop
					return true;
				elm[i][j]=0;
				++elm[i-k][j];
				//mixup succeed
				Will_Spawn[0]=true;
				success=true;
				break;
			}
			if (elm[i-k][j]!=0 && elm[i][j]!=elm[i-k][j])
				break;
		}
	return success;
}

//rotate it
//mixup
//and rotate back
bool MixDown()
{
	rotate(2);
	bool success=MixUp('s');
	rotate(2);
	return Is_2048;
}
bool MixLeft()
{
	rotate(1);
	bool success=MixUp('a');
	rotate(3);
	return Is_2048;
}
bool MixRight()
{
	rotate(3);
	bool success=MixUp('d');
	rotate(1);
	return Is_2048;
}

bool MoveUp(char direction='w')
{
	//move the number to the direction keyboard input
	bool success=false;
	for(int j=0;j<4;++j) {
	for(int i=0;i<4;++i)
		for(int k=1;k<4-i;++k)
			if(elm[i][j]==0 && elm[i+k][j]!=0) {
				if (direction!=key) 
				//if the 'direction' is different to keyboard input
				//break the loop
					return true;
				elm[i][j]=elm[i+k][j];
				elm[i+k][j]=0;
				if (elm[i][j]==10)
				//it is 2048!
					win();
				//moveup succeed
				Will_Spawn[1]=true;
				success=true;
				break;
			}
	}
	return success;
}

//rotate it
//moveup
//and rotate back
bool MoveDown()
{
	rotate(2);
	bool success=MoveUp('s');
	rotate(2);
	return success;
}
bool MoveLeft()
{
	rotate(1);
	bool success=MoveUp('a');
	rotate(3);
	return success;
}
bool MoveRight()
{
	rotate(3);
	bool success=MoveUp('d');
	rotate(1);
	return success;
}

bool NumberMix()
{
	//return true if there is a successful 'P'
	bool P1,P2,P3,P4;
	P1=MixUp();
	P2=MixRight();
	P3=MixDown();
	P4=MixLeft();
	return P1||P2||P3||P4;
}

bool NumberMove()
{
	//return 
	bool P1,P2,P3,P4;
	P1=MoveUp();
	P2=MoveRight();
	P3=MoveDown();
	P4=MoveLeft();
	return P1||P2||P3||P4;
}

void GAME_OVER()
{
	cout<<endl<<"you lose.";
	Sleep(1500);
	system("pause");
	Initialize();
}

int main()
{
	Initialize();
	bool P1=true;
	bool P2=true;
	while(1)
	{
		system("cls");
		output();
		key=getch();
		P1=NumberMix();
		P2=NumberMove();
		if (!(P1||P2))
			GAME_OVER();
		if (Will_Spawn[1]||Will_Spawn[0])
			Spawn();
		Will_Spawn[0]=false;
		Will_Spawn[1]=false;
	}
}
