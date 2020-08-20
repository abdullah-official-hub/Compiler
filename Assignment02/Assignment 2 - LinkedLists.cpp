#include <iostream>
#include <math.h>
#include <string>
using namespace std;
// Node class with next pointer and a character
class Node{
	public:
		char ch;
		Node *next;
		Node(char ch=' ',Node *next=NULL){
			this->ch=ch;
			this->next=next;
		}
};
// Singly Linked List class
class SLList{
	private:
		Node *head,*tail;
	public:
		SLList(){
			head=tail=NULL;
		}
		void AddAtTail(char ch){
			if (tail){
				tail->next=new Node(ch,tail->next);
				tail=tail->next;
			}
			else
				head=tail=new Node(ch,head);
		}
		void Display(){
			for (Node *temp=head;temp;temp=temp->next)
				cout << temp->ch << ' ';
			cout << endl;
		}
		void setTail(char ch){
			tail->ch=ch;
		}
		char getTail(){
			if (tail)
				return tail->ch;
			return '-';
		}
		void CopyInto(SLList &list1){
			for (Node *temp=head;temp;temp=temp->next)
				list1.AddAtTail(temp->ch);
		}
		bool hasData(){
			if (head)
				return true;
			return false;
		}
};
// Transition Table returns a new state by matching current state and a character
char TransitionTable(char value,char currentState='A'){
	char TT[5][3]={{'X','0','1'},{'A','A','B'},{'B','C','C'},{'C','D','D'},{'D','-','-'}};
	int val=((value=='0')?1:2);
	for (int i=1;i<5;i++)
		if (currentState==TT[i][0])
			return TT[i][val];
}
// Important Function works on NFA
void Check1(SLList *arr,string str,int arr_size,int cur_size=1){
	int a=0;
	char state;
	arr[0].AddAtTail('A');
	while (a<str.length()){
		arr[0].AddAtTail('A');
		for (int i=1;i<arr_size && i<=cur_size;i++){
			if (arr[i].hasData()){
				state=arr[i].getTail();
				if (state=='-')
					arr[i].AddAtTail(state);
				else{
					state=TransitionTable(str[a],state);
					arr[i].AddAtTail(state);					
				}
			}
			else
				break;
		}
		if (str[a]=='1'){
			arr[0].CopyInto(arr[cur_size]);
			arr[cur_size].setTail('B');
			cur_size++;
		}
		a++;
	}
}
// returns accepted if atleast one path ends on 1 else rejected
string isAccepted(SLList *list,int size){
	for (int i=0;i<size && list[i].hasData();i++)
		if (list[i].getTail()=='D')
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
// Main Function
int main(){
	SLList *list;
	cout << "\n Rule : 3rd last is One - Character Set = 0,1" << endl;
	cout << "\n Enter String : ";
	string str;
	cin >> str;
	if (isValid(str)){
		// In worst case size=pow(4,str.length())
		// Due to only when 1 cames a new state generates from A
		int size=str.length()+2;
		list=new SLList[size];
		Check1(list,str,size);
		cout << endl;
		for (int i=0;i<size && list[i].hasData();i++){
			cout << " -> ";
			list[i].Display();
		}
		cout << "\n String " << isAccepted(list,size) << endl;
	}
	else
		cout << "\n Invalid String" << endl;
	cout << endl << ' ';
	system("pause");
}
