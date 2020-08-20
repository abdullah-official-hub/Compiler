#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;
// Check Given Character is Alphabet
bool isAlpha(char ch){
	if ((ch>='A' && ch<='Z') || (ch>='a' && ch<='z'))
		return true;
	return false;
}
// Check Given Character is Numeric
bool isDigit(char ch){
	if (ch>='0' && ch<='9')
		return true;
	return false;
}
// Check Given Character represent a string
bool isSpace(char ch){
	if (ch==' ' || ch=='\n' || ch=='\t' || ch=='\b' || ch=='\r')
		return true;
	return false;
}
// Check Identifier is a Keyword
bool isKeyword(string str){
	string keywords[]={"asm","else","new","this","auto","enum","operator","throw","bool","explicit","private","true",
	"break","export","protected","try","case","extern","public","typedef","catch","false","register","typeid",
	"char","float","reinterpret_cast","typename","class","for","return","union","const","friend","short","unsigned",
	"const_cast","goto","signed","using","continue","if","sizeof","virtual","default","inline","static","void",
	"delete","int","static_cast","volatile","do","long","struct","wchar_t","double","mutable","switch","while",
	"dynamic_cast","namespace","template","bitor","not_eq","xor","and_eq","compl","or","xor_eq","bitand","not","or_eq"};
	for (int i=0;i<74;i++)
		if (str==keywords[i])
			return true;
	return false;
}
// Print Tokens of max-punch lexemes
void print(string str,int start,int end,char signal){
	cout << endl;
	if (signal=='P')
		cout << " < Partial String ~ Unknown , ";
	else if (signal=='X')
		cout << " < Error ~ ";
	else
		cout << " < Accepting String ~ ";
	if (signal=='1')
		cout << "Simple Number , ";
	else if (signal=='3')
		cout << "Fractional Number , ";
	else if (signal=='5')
		cout << "Exponential Number , ";
	else if (signal=='6')
		cout << "Space(s)";
	else if (signal=='7'){
		string str1;
		for (int i=start;i<=end;i++)
			str1=str1+str[i];
		if (isKeyword(str1))
			cout << "Keyword ";
		else
			cout << "Name ";
		cout << "Identifier , ";
	}
	for (int i=start;i<=end && signal!='6' ;i++)
		cout << str[i];
	cout << " >" << endl;
}
// Lexical Analyzer
void Lexical_Analyzer(string str){
	// A contains All Digits
	// B contain .
	// C contains e|E for Numbers
	// D contains Accepting states
	// E contains Alphabets
	// F contains All Other characters
	// G contains spaces
	// H contain _ (underscore)
	// I contains
	char Array[10][9]= {{'*','A','B','C','D','E','F','G','H'},
						{'0','1','2','7','N','7','8','6','7'},
						{'1','1','3','4','Y','8','8','8','8'},
						{'2','3','8','8','N','8','8','8','8'},
						{'3','3','8','4','Y','8','8','8','8'},
						{'4','5','8','8','N','8','8','8','8'},
						{'5','5','8','8','Y','8','8','8','8'},
						{'6','8','8','8','Y','8','8','6','8'},
						{'7','7','8','7','Y','7','8','8','7'},
						{'8','8','8','8','N','8','8','8','8'}};
	int i,startIndex=0,accepting_index=-2;
	char accepting_state,current_state='0';
	for (i=0;i<str.length();){
		if (str[i]=='e' || str[i]=='E')
			current_state=Array[current_state-47]['C'-64];
		else if (isAlpha(str[i]))
			current_state=Array[current_state-47]['E'-64];
		else if (str[i]=='_')
			current_state=Array[current_state-47]['H'-64];
		else if (isSpace(str[i]))
			current_state=Array[current_state-47]['G'-64];
		else if (isDigit(str[i]))
			current_state=Array[current_state-47]['A'-64];
		else if (str[i]=='.')
			current_state=Array[current_state-47]['B'-64];
		else
			current_state=Array[current_state-47]['F'-64];
			
		if (Array[current_state-47]['D'-64]=='Y'){
			accepting_index=i;
			accepting_state=current_state;
		}

		if (current_state=='8'){
				if (accepting_index==i-1){
					print(str,startIndex,accepting_index,accepting_state);
					i=startIndex=accepting_index+1;
				}
				else if(i==startIndex){
					print(str,startIndex,i,'X');
					i=(++startIndex);
				}
				else{
					print(str,startIndex,i-1,'P');
					startIndex=i;
				}
				current_state='0';
				accepting_index=-2;
		}
		else
			i=i+1;
	}
	if ((i-1)==accepting_index)
		print(str,startIndex,accepting_index,accepting_state);
	else if (current_state=='8')
		print(str,startIndex,i-1,'X');
	else if (startIndex<=i-1)
		print(str,startIndex,i-1,'P');
}
// Main Function
int main(){
	string str;
	cout << "\n Enter String : ";
	getline(cin,str);
	Lexical_Analyzer(str);
	cout << endl << ' ';
	system("pause");
	return 0;
}
