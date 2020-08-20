#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
using namespace std;
HANDLE hstdout=GetStdHandle( STD_OUTPUT_HANDLE );

// Deterministic Finite Automata which accept the string contains equal number of 01 and 10
void gotoxy(int Xaxis, int Yaxis){
	COORD coord;
	coord.X = Xaxis;
	coord.Y = Yaxis;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

void makeBox(int x,int y,int color,string alpha){
	SetConsoleTextAttribute( hstdout , color);
	gotoxy(x,y);
	cout << "     ";
	gotoxy(x,y+1);
	cout << "  " + alpha + "  ";
	gotoxy(x,y+2);
	cout << "     ";
	SetConsoleTextAttribute( hstdout , 496);
}

void makeFArrow(int x,int y,char num=' '){
	gotoxy(x,y);
	cout << "----->";
	gotoxy(x+2,y-1);
	cout << num;
}

void makeRArrow(int x,int y,char num=' '){
	gotoxy(x,y);
	cout << "<-----";
	gotoxy(x+3,y+1);
	cout << num;
}

void makeUpLoop(int x,int y,string num=" "){
	gotoxy(x,y);
	cout << "| " + num;
	gotoxy(x,y-1);
	cout << '|';
	gotoxy(x+1,y-2);
	cout << "___";
	gotoxy(x+4,y);
	cout << '|';
	gotoxy(x+4,y-1);
	cout << '|';
}

void makeDownLoop(int x,int y,string num=" "){
	gotoxy(x,y);
	cout << "| " + num;
	gotoxy(x,y+1);
	cout << '|';
	gotoxy(x+1,y+1);
	cout << "___";
	gotoxy(x+4,y);
	cout << '|';
	gotoxy(x+4,y+1);
	cout << '|';
}

void Rule(){
	gotoxy(0,17);
	cout << "    -> Rule Equal Count of 01 and 10 in a string.";
	cout << " F=[A,B,D,E,G] , Set=[0,1]";
}

void SmallBox(int color){
	SetConsoleTextAttribute( hstdout , color);		
	gotoxy(6,12);
	cout << "          ";
	gotoxy(6,13);
	cout << "          ";
	gotoxy(6,14);
	cout << "          ";
}

void UI(){
	SetConsoleTextAttribute( hstdout , 944);
	for (int i=2;i<16;i++){
		gotoxy(4,i);
		for (int j=4;j<75;j++){
			cout << ' ';
		}
	}
	SmallBox(1023);
	SetConsoleTextAttribute( hstdout , 944);
	int BoxColor=632;
	makeFArrow(13,6);
	makeFArrow(26,6,'0');
	makeFArrow(39,6,'1');
	makeFArrow(52,5,'0');
	makeFArrow(39,11,'0');
	makeFArrow(52,11,'1');
	
	makeRArrow(52,6,'1');
	makeRArrow(52,12,'0');
	
	makeUpLoop(33,4,"0");
	makeUpLoop(46,4,"1");
	makeUpLoop(59,4,"0");
	
	makeDownLoop(33,13,"1");
	makeDownLoop(46,13,"0");
	makeDownLoop(59,13,"1");
	
	gotoxy(22,8);
	for (int i=8;i<12;i++,gotoxy(22,i))
		cout << '|';
	gotoxy(22,11);
	cout << " -------->";
	gotoxy(26,12);
	cout << '1';

	makeBox(20,5,BoxColor,"A");
	makeBox(33,5,BoxColor,"B");
	makeBox(46,5,BoxColor,"C");
	makeBox(59,5,BoxColor,"D");
	makeBox(33,10,BoxColor,"E");
	makeBox(46,10,BoxColor,"F");
	makeBox(59,10,BoxColor,"G");
}

void UpdateBox(char previous,char latest,int tempColor=996){
	Sleep(270);
	int color=632;
	bool flag=true;
	char ZeroStart[4]={'A','B','C','D'};
	char OneStart[3]={'E','F','G'};
	string str;
	int a;
	char data=previous;
	for (int i=1;i<=2;i++){
		if (data>='A' && data<='D'){
			a=20;
			for (int i=0;i<sizeof(ZeroStart);i++,a+=13){
				if (ZeroStart[i]==data){
					str=data;
					makeBox(a,5,color,str);
					break;
				}
			}
		}
		else{
			a=33;
			for (int i=0;i<sizeof(OneStart) && flag;i++,a+=13){
				if (OneStart[i]==data){
					str=data;
					makeBox(a,10,color,str);
					break;
				}
			}
		}
		str.clear();
		color=tempColor;
		data=latest;
	}
}

bool isExist(char ch){
	if (ch=='A' || ch=='B' || ch=='E' || ch=='D' || ch=='G')
		return true;
	return false;
}

int main(){
	static int chooseUI=0;
	system("color f0");
	if(chooseUI==0){
			SetConsoleTitle("Compiler Construction - Assignment No.1");
			cout << "\n\n  Name         : Abdullah Zafar";
			cout << "\n\n  Roll No.     : BCSF16A508";
			cout << "\n\n  Submitted to : SIR Adnan-ul-Hassan";
			cout << "\n\n\n\n   1. Graphical User Interface";
			cout << "\n\n   2. Command Line Interface";
			cout << "\n\n\n   Choice : ";
			cin >> chooseUI;
	}
	system("cls");
	if (chooseUI!=2){
		Rule();
		UI();
	}
	else{
		cout << "\n -> Rule Equal Count of 01 and 10 in a string.";
		cout << "\n\n -> F=[A,B,D,E,G]\n\n -> Set=[0,1]\n\n";
	}
	int rows=8,columns=3;
	char FA[8][3]={{'X','0','1'},{'A','B','E'},{'B','B','C'},{'C','D','C'},{'D','D','C'},{'E','F','E'},{'F','F','G'},{'G','F','G'}};
	char element1='A',element2='A';	// start State
	int current;
	string input;
	if (chooseUI!=2)
		gotoxy(2,19);
	else
		cout << endl << endl;
	cout << "  Enter String : ";
	cin >> input;
	for (int i=0;i<input.length();i++){
		if (chooseUI!=2){
			gotoxy(i+4,21);
			cout << input[i];
		}
		if (input[i]!='0' && input[i]!='1'){
			element1='X';
			break;
		}
		current=((input[i]=='0')?1:2);	
		for (int j=1;j<rows;j++){
			if (element1==FA[j][0]){
				if (chooseUI!=2)
					UpdateBox(element2,element1);
				element2=element1;
				element1=FA[j][current];
			}
		}
	}
	if (chooseUI!=2)
		SmallBox(1006);
	if (isExist(element1)){
		if (chooseUI!=2){
			UpdateBox(element1,element1,934);
			gotoxy(7,13);
			cout << "Accepted" << endl;
		}
		else{
			cout << "\n\n  Answer : Accepted\n\n  ";
		}
	}
	else{
		if (chooseUI!=2){
			UpdateBox(element2,element1,967);
			gotoxy(7,13);
			cout << "Rejected" << endl;
		}
		else{
			cout << "\n\n  Answer : Rejected\n\n  ";
		}
	}
	if (chooseUI!=2)
		gotoxy(4,23);
	system("pause");
	main();
}
