#include <iostream>
#include <string>
using namespace std;
// Check character is an Alphabet
bool isAlpha(char ch){
	if ((ch>='A' && ch<='Z') || (ch>='a' && ch<='z'))
		return true;
	return false;
}
// Check character is a Digit
bool isDigit(char ch){
	if ((ch>='0' && ch<='9'))
		return true;
	return false;
}
// Check character is an Underscore
bool isUnderscore(char ch){
	if (ch=='_')
		return true;
	return false;
}
// Check character is special character
bool isError(char ch){
	if (!isAlpha(ch) && !isDigit(ch) && !isUnderscore(ch))
		return true;
	return false;
}
// Check character is point
bool isPoint(char ch){
	if (ch=='.')
		return true;
	return false;
}
int NumberNFA(string str,int i1=0){
	// W shows transition of 0-9
	// X shows transition of . (point)
	// Y shows transition of power element (e|E)
	// Z shows transition of all remaining character on keyboard
	char AcceptingState='A';
	int returnIndex;
	char NFA[9][5]={{' ','W','X','Y','Z'},
					{'A','B','D','H','H'},
					{'B','B','C','F','H'},
					{'C','C','H','F','H'},
					{'D','E','H','H','H'},
					{'E','E','H','F','H'},
					{'F','G','H','H','H'},
					{'G','G','H','H','H'},
					{'H','H','H','H','H'}};
	char currentState='A';
	int i;
	for (i=i1;i<str.length();i++){
		if (isDigit(str[i]))
			currentState=NFA[(int)currentState-64][1];
		else if (isPoint(str[i]))
			currentState=NFA[(int)currentState-64][2];
		else if (str[i]=='E' || str[i]=='e')
			currentState=NFA[(int)currentState-64][3];
		else
			currentState=NFA[(int)currentState-64][4];
		if (currentState=='B' || currentState=='C' || currentState=='E' || currentState=='G'){
			AcceptingState=currentState;
			returnIndex=i;
		}
		if (currentState=='H'){
			if (AcceptingState=='A')
				return i1;
			else
				return returnIndex+1;
		}
	}
	if (AcceptingState=='A')
		return i1;
	else
		return returnIndex+1;
}
int IdentifierNFA(string str,int i1=0){
	// X shows transition of A-Z or a-z or _
	// Y shows transition of 0-9
	// Z shows transition of all remaining character on keyboard
	char NFA[5][4]={{' ','X','Y','Z'},
					{'A','B','D','D'},
					{'B','C','C','D'},
					{'C','B','B','D'},
					{'D','D','D','D'}};
	char currentState='A';
	int i;
	for (i=i1;i<str.length();i++){
		if (isAlpha(str[i]) || isUnderscore(str[i]))
			currentState=NFA[(int)currentState-64][1];
		else if (isDigit(str[i]))
			currentState=NFA[(int)currentState-64][2];
		else
			currentState=NFA[(int)currentState-64][3];
		if (currentState=='D')
			return i;
	}
	return i;
}
// Process on error
int errorCounter(string str,int i1=0){
	int i;
	for (i=i1;i<str.length();i++){
		if ((i+1)<str.length())
			if (str[i]=='.' && isDigit(str[i+1]))
				return i;
		if (!isError(str[i]))
			return i;
	}
	return i;
}
// Print Identifier or Number pointed by signal
void Printer(string str,int start,int end,char signal){
	if (signal=='I'){
		cout << " < Identifier , ";
		for (int i=start;i<end;i++)
			cout << str[i];
		cout << " >" << endl << endl;
	}
	else if (signal=='N'){
		cout << " < Number , ";
		for (int i=start;i<end;i++)
			cout << str[i];
		cout << " >" << endl << endl;
	}
	else if (signal=='E'){
		cout << " < Error , ";
		for (int i=start;i<end;i++)
			cout << str[i];
		cout << " >" << endl << endl;
	}	
}
// Main Function
int main(){
	string str;
	cout << "\n Program like a Lexical Analyzer (Differenciate Identifier and Number)\n";
	cout << "\n Enter a mix String : ";
	getline(cin,str);
	cout << endl << endl;
	int checker;
	for (int i=0;i<str.length();i++){
		checker=IdentifierNFA(str,i);
		if (checker!=i){
			Printer(str,i,checker,'I');
			i=checker-1;
		}
		else{
			checker=NumberNFA(str,i);
			if (checker!=i){
				Printer(str,i,checker,'N');
				i=checker-1;
			}
			else{
				checker=errorCounter(str,i);
				Printer(str,i,checker,'E');
				i=checker-1;
			}
		}
	}
	return 0;
}
