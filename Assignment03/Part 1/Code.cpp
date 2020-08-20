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
int NumberNFA(string str,int i1=0){
	// X shows transition of 0-9
	// Y shows transition of A-Z or a-z or _
	// Z shows transition of all remaining character on keyboard
	char NFA[4][4]={{' ','X','Y','Z'},
					{'A','B','C','C'},
					{'B','B','C','C'},
					{'C','C','C','C'}};
	char currentState='A';
	int i;
	for (i=i1;i<str.length();i++){
		if (isDigit(str[i]))
			currentState=NFA[(int)currentState-64][1];
		else
			currentState=NFA[(int)currentState-64][2];
		if (currentState=='C')
			return i;
	}
	return i;
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
	cout << "\n Program like a Lexical Analyzer (Differentiate Identifier and Number)\n";
	cout << "\n Enter a mix String : ";
	cin >> str;
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
