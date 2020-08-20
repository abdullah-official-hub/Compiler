#include <iostream>
#include <math.h>
#include <string>
using namespace std;
// Transition Table returns a new state by matching current state and a character
char TransitionTable(char value,char currentState='A'){
	if (currentState=='-')
		return '-';
	char TT[5][3]={{'X','0','1'},{'A','A','B'},{'B','C','C'},{'C','D','D'},{'D','-','-'}};
	int val=((value=='0')?1:2);
	for (int i=1;i<5;i++)
		if (currentState==TT[i][0])
			return TT[i][val];
}
// returns accepted if atleast one path ends on 1 else rejected
string isAccepted(string *array,int size){
	for (int i=0;i<size && !array[i].empty();i++)
		if (array[i][array[i].length()-1]=='D')
			return "ACCEPTED";
	return "REJECTED";
}
// return true if string contains only 0 and 1
bool isValid(string str){
	for (int i=0;i<str.length();i++)
		if (str[i]!='0' && str[i]!='1')
			return false;
	return true;
}
// Print all possible paths
void print(string *array,int size){
	for (int i=0;i<size && !array[i].empty();i++){
		cout << " -> ";
		for (int j=0;j<array[i].length();j++)
			cout << array[i][j] << ' ';
		cout << endl;
	}
}
// Main Function
int main(){
	string *array,str;
	cout << "\n Rule : 3rd last is One - Character Set = 0,1" << endl;
	cout << "\n Enter String : ";
	cin >> str;
	// In worst case size=pow(4,str.length())
	// Due to only when 1 cames a new state generates from A
	int arraySize=str.length()+2;
	array=new string[arraySize];
	array[0]="A";
	bool flag=true;
	if (isValid(str)){
		for (int i=0;i<str.length();i++){
			flag=true;
			for (int j=0;j<arraySize;j++)
				if (!array[j].empty()){
					if (str[i]=='0')
						array[j]=array[j]+TransitionTable(str[i],array[j][array[j].length()-1]);
					else
						if (flag){
							for (int k=j;k<arraySize;k++)
								if (array[k].empty()){
									array[k]=array[0];
									break;
								}
							flag=false;
							array[0]=array[0]+'A';
						}
						else
							array[j]=array[j]+TransitionTable(str[i],array[j][array[j].length()-1]);
				}
				else
					break;
		}
		cout << endl;
		print(array,arraySize);
		cout << endl << ' ' << isAccepted(array,arraySize) << endl;
	}
	else
		cout << "\n Invalid String" << endl;
	cout << endl << ' ';
	system("pause");
}
