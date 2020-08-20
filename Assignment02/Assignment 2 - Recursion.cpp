#include <iostream>
#include <string>
using namespace std;
char Print(string str,char ch='A',int i=0){
	cout << ((i==0)?"\n -> ":" ");
	cout << ch;
	if (ch!='D' && i<str.length()){
		if (str[i]=='0' && ch=='A')
			return Print(str,ch,++i);
		else
			return Print(str,++ch,++i);
	}
	return '0';
}
int main(){
	string str;
	cout << "\n NFA 3rd last is '1' and character set = [0,1]\n\n Enter String : ";
	cin >> str;
	for (int i=0;i<str.length();i++)
		if (str[i]!='0' && str[i]!='1'){
			cout << "\n Invalid String\n\n ";
			system("pause");
			return 0;	
		}
	cout << "\n Possible Paths\n";
	for (int i=0;i<str.length();i++)
		str[i]=((str[i]=='1')?Print(str):'0');
	Print(str);
	cout << endl << endl << ' ';
	system("pause");
}
