#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int power(int a1,int a2){
	int ans=1;
	for (int i=1;i<=a2;i++)
		ans=ans*a1;
	return ans;
}
void PowerSet(string **NFA_Array,string **DFA_Array,int NFA_rows,int DFA_rows){
	string *A=new string[NFA_rows-1];
	for (int i=0;i<NFA_rows-1;i++)
		A[i]=NFA_Array[i+1][0];
	string str;
	for (int i=1;i<DFA_rows;i++){
 		for (int j=0;j<NFA_rows-1;j++){
  			if ((i>>j) & 1)
     			str=str+A[j];
    	}
   	DFA_Array[i][0]=str;
   	str.clear();
	}
}
bool compare(string a1,string a2){
	int val1=0,val2=0;
	for (int i=0;i<a1.length();i++)
		val1=val1+(int)a1[i];
	for (int i=0;i<a2.length();i++)
		val2=val2+(int)a2[i];
	if (val1<val2)
		return true;
	return false;
}
void SortElement(string &str){
	char temp;
	for (int i=0;i<str.length();i++){
		for (int j=0;j<str.length();j++){
			if (str[i]<str[j]){
				temp=str[i];
				str[i]=str[j];
				str[j]=temp;
			}
		}
	}
}
void RemoveFi(string &str){
	if (str.length()<=1)
		return;
	string str1;
	if (str[0]=='*'){
		for (int i=1;i<str.length();i++)
			str1=str1+str[i];
		str=str1;
	}
}
void RemoveDuplication(string &str){
	string str1=str;
	for (int i=0;i<str1.length();i++){
		for (int j=i+1;j<str1.length();j++)
			if (str1[i]==str1[j])
				str1[j]='+';
	}
	string str2;
	for (int i=0;i<str1.length();i++)
		if (str1[i]!='+')
			str2=str2+str1[i];
	str.clear();
	str=str2;
}
void SortArray(string **DFA_Array,int DFA_rows){
	string temp;
	for(int i=1;i<DFA_rows;i++){
		for (int j=1;j<DFA_rows;j++){
			if (compare(DFA_Array[i][0],DFA_Array[j][0])){
				temp=DFA_Array[i][0];
				DFA_Array[i][0]=DFA_Array[j][0];
				DFA_Array[j][0]=temp;
			}
			temp.clear();
		}
	}
}
void RemoveUnused(string **DFA_Array,int DFA_rows){
	DFA_Array[2][0]="$"+DFA_Array[2][0];
	bool flag=false;
	while (true){
		flag=true;
		for (int i=1;i<DFA_rows && flag;i++){
			if (DFA_Array[i][0][0]=='$'){
				flag=false;
				for (int j=1;j<DFA_rows;j++){
					if (DFA_Array[i][1]==DFA_Array[j][0]){
						DFA_Array[j][0]="$"+DFA_Array[j][0];
						break;
					}
				}
				for (int j=1;j<DFA_rows;j++){
					if (DFA_Array[i][2]==DFA_Array[j][0]){
						DFA_Array[j][0]="$"+DFA_Array[j][0];
						break;
					}
				}
				DFA_Array[i][0][0]=' ';
				break;
			}
		}
		if (flag)
			break;
	}
}
void DFA_Printing(string **DFA_Array,int DFA_rows,int columns){
	fstream DFA;
	DFA.open("DFA.txt",ios::out);
	DFA << endl << " Note : * shows the dead state and At End of file used states are Mentioned" << endl;
	DFA << endl << " All Possible States " << endl << endl;
	for (int i=0;i<columns;i++)
		DFA << ' ' << DFA_Array[0][i] << '\t' << '\t';
	DFA << endl << endl;
	for (int i=2;i<DFA_rows;i++){
		for (int j=0;j<columns;j++){
			DFA << ' ' << DFA_Array[i][j] << '\t' << '\t';
		}
		DFA << endl;
	}
	for (int i=0;i<columns;i++)
		DFA << ' ' << DFA_Array[1][i] << '\t' << '\t';
	DFA << endl;
	RemoveUnused(DFA_Array,DFA_rows);
	DFA << endl << " States which are in used" << endl << endl;
	for (int i=2;i<DFA_rows;i++){
		if (DFA_Array[i][0][0]==' '){
			for (int j=0;j<columns;j++){
				DFA << DFA_Array[i][j] << '\t' << '\t';
			}
			DFA << endl;
		}
	}
	if (DFA_Array[1][0][0]==' '){
		for (int i=0;i<columns;i++)
			DFA << DFA_Array[1][i] << '\t' << '\t';
		DFA << endl;
	}
	DFA.close();
}
int main(){
	fstream NFA;
	NFA.open("NFA.txt",ios::in);
	if (!NFA){
		cout << "\n Input file NFA.txt not Found\n" << endl << ' ';
		system("pause");
		return 0;
	}
	int rows,columns;
	NFA >> rows;
	rows++;
	string **NFA_Array;
	NFA_Array=new string*[rows];
	NFA >> columns;
	columns++;
	string value;
	for (int i=0;i<rows;i++){
		NFA_Array[i]=new string[columns];
		for (int j=0;j<columns;j++){
			NFA >> value;
			NFA_Array[i][j]=value;
		}
	}
	NFA.close();
	string **DFA_Array;
	int DFA_rows=power(2,rows-1)+1;
	DFA_Array=new string*[DFA_rows];
	for (int i=0;i<DFA_rows;i++)
		DFA_Array[i]=new string[columns];
	for (int i=0;i<columns;i++)
		DFA_Array[0][i]=NFA_Array[0][i];
	PowerSet(NFA_Array,DFA_Array,rows,DFA_rows);
	SortArray(DFA_Array,DFA_rows);
	for (int i=0;i<columns;i++)
		DFA_Array[1][i]="*";
	string ch;
	for (int i=1;i<DFA_rows;i++){
		for (int j=0;j<DFA_Array[i][0].length();j++){
			ch=DFA_Array[i][0][j];
			for (int k=1;k<rows;k++){
				if (ch==NFA_Array[k][0]){
					for (int x=1;x<columns;x++)
						DFA_Array[i][x]=DFA_Array[i][x]+NFA_Array[k][x];
				}
			}
		}
		for (int j=1;j<columns;j++){
			RemoveDuplication(DFA_Array[i][j]);
			SortElement(DFA_Array[i][j]);
			RemoveFi(DFA_Array[i][j]);
		}
	}
	DFA_Printing(DFA_Array,DFA_rows,columns);
	cout << "\n Open text file named 'DFA.txt'\n" << endl << ' ';
	system("pause");
	return 0;
}
