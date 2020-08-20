#include <iostream>																		// Libraries Required in Code
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>
#define EMPTY -9909																		// Specified -9909 as sentinal
using namespace std;
void fill_value(int *array, int base, int end, int value){								// FIll ARRAY WITH SPECIFIC VALUE IN RANGE
	for (int i = base; i <= end; i++)
		array[i] = value;
}
void maintain_Hash(fstream &file, int *array, int columns){								// Maintain Hash table for Retreival of Data in O(1)
	int reader, count = 0;
	for (int i = 0; i<columns; i++){
		file >> reader;
		if (reader <= 128)
			array[reader] = count++;
		else{
			cerr << "Maintain-Hash Read a character out of range" << endl;
			system("pause");
			exit(0);
		}
	}
}
void UpdateHash(int *hashTable, int hashSize, int key, int change){							// Update Hash
	for (int i = 0; i<hashSize; i++)
		if (hashTable[i] == key)
			hashTable[i] = change;
}
bool columnComparison(int **TT, int rows, int col1, int col2){								// Column Comparison
	for (int i = 0; i<rows; i++)
		if (TT[i][col1] != TT[i][col2])
			return false;
	return true;
}
void MakeCompactedFile(int **CompactedTT,int *hashTable,int hashSize,int rows,int CompactedColumns,bool CompactionOccur){		// Make Informative Compacted File
	ofstream newFile("CompactedTable.txt");
	if(CompactionOccur)
		newFile << endl << " Compacted Table" << endl << endl << ' ';
	else
		newFile << endl << " No Compaction Occurs" << endl << endl << ' ';
	for (int i = 0; i<rows; i++){
		for (int j = 0; j<CompactedColumns; j++)
			newFile << CompactedTT[i][j] << '\t';
		newFile << endl << ' ';
	}
	newFile << endl << " Character ASCII assigned to which column of Compacted Table" << endl;
	int comma;
	for (int i = 0; i<CompactedColumns; i++){
		comma = 0;
		newFile << endl << ' ' << i << ' ' << ':' << ' ';
		for (int j = 0; j<hashSize; j++){
			if (hashTable[j] == i && comma == 0){
				newFile << j;
				comma = 1;
			}
			else if (hashTable[j] == i)
				newFile << ',' << j;
		}
	}
	newFile << endl << endl << ' ' << "Not Specified : ";;
	for (int i = 0; i<hashSize; i++){
		if (hashTable[i] == -1 && comma<2){
			newFile << i;
			comma = 2;
		}
		else if (hashTable[i] == -1)
			newFile << ',' << i;
	}
	newFile.close();
}
int compaction(int **TT, int *hashTable, int hashSize, int rows, int columns){				// Compaction performed on Table
	int LocalColumns = columns, count = 0;
	for (int i = 0; i<columns; i++){
		for (int j = i + 1; j<columns; j++){
			if (columnComparison(TT, rows, i, j) && TT[0][i] != EMPTY && TT[0][j] != EMPTY){
				LocalColumns = LocalColumns - 1;
				TT[0][j] = EMPTY;
				UpdateHash(hashTable, hashSize, j, i);
			}
		}
		if (TT[0][i] != EMPTY){
			UpdateHash(hashTable, hashSize, i, count);
			count = count + 1;
		}
	}
	return LocalColumns;
}
void fill_TT(fstream &file, int **TT, int rows, int columns){								// Fill 2-D Array from given Data in File
	for (int i = 0; i<rows; i++)
	for (int j = 0; j<columns; j++)
		file >> TT[i][j];
}
void generateToken(string str, int start, int end, int type,int Forward){								// Generate Tokens
	if (type==-1)
		cout << endl << endl << " < " << setw(3) << "Error" << setw(3) << " , ";
	else
		cout << endl << endl << " < " << setw(3) << type << setw(5) << " , ";
	for (int i = start; i <= end; i++)
		cout << str[i];
	cout << " >";
	if (type==-1)
		cout << " at index " << Forward;
}
void Lexical_Analyzer(string str, int **TT, int *hash_Table){								// Lexical Analyzer Specification Independent
	int CurrentState, LexemeStart, Remember, Forward, LineNo, columnNumber;
	CurrentState = LexemeStart = Remember = Forward = LineNo = 0;
	int LSFV = -1;
	str = str + (char)150;
	for (Forward = 0; Forward<str.length();){
//		if (Forward<str.length() && Forward+1<str.length())	--> if (str[Forward]=='\\' && str[Forward+1]=='n') --> LineNo=LineNo+1;
		if (str[Forward] == (char)150 && str.length() - 1 == Forward){
			if (Forward == LexemeStart)
				break;
			generateToken(str, LexemeStart, Remember, LSFV,Forward);
			CurrentState = 0;
			Forward = LexemeStart = Remember = Remember + 1;
			LSFV = -1;
		}
		else{
			columnNumber = ((str[Forward] != (char)150) ? hash_Table[(int)str[Forward]] : -1);
			CurrentState = ((columnNumber != -1) ? TT[CurrentState][columnNumber] : -1);
			if (hash_Table[128] != -1 && CurrentState != -1){
				if (TT[CurrentState][hash_Table[128]] >= 0){
					LSFV = TT[CurrentState][hash_Table[128]];
					Remember = Forward;
				}
			}
			if (CurrentState == -1 && LSFV != -1){
				generateToken(str, LexemeStart, Remember, LSFV,Forward);
				CurrentState = 0;
				Forward = LexemeStart = Remember = Remember + 1;
				LSFV = -1;
			}
			else if (CurrentState == -1){
				generateToken(str, LexemeStart, Remember, LSFV,Forward);
				CurrentState = 0;
				Forward = LexemeStart = Remember = Remember + 1;
				LSFV = -1;
			}
			else
				Forward++;
		}
	}
}
void CompactedFilling(int **TT, int **CompactedTT, int rows, int columns){			// Fill new array with Compacted Data
	int count = 0;
	for (int i = 0; i<columns; i++){
		if (TT[0][i] != EMPTY){
			for (int j = 0; j<rows; j++)
				CompactedTT[j][count] = TT[j][i];
			count = count + 1;
		}
	}
}
void readInputFile(int **CompactedTT, int *hash_Table){								// Read Input File
	string reader;
	ifstream file("input.txt");
	if (file){
		while (!file.eof()){
			getline(file, reader);
			cout << endl << ' ' << reader << endl;
			Lexical_Analyzer(reader, CompactedTT, hash_Table);						// Lexical Analyzer Calling
			reader.clear();
			cout << endl;
		}
		file.close();
	}
	else{
		cerr << "File not Open !!!" << endl;
		system("pause");
		exit(0);
	}
}
int main(){																					// Main Function
	int **TT, **CompactedTT, rows, columns, CompactedColumns, count, hash_Size = 129;		// Major Variables including Tables	
	int *hash_Table = new int[hash_Size];
	fstream file;																			// File Stream for reading from Specification
	file.open("Specs.txt", ios::in);
	if (file){																				// If File opened Successfully
		file >> rows >> columns;
		TT = new int*[rows];																// Creation of Dynamically 2-D array
		for (int i = 0; i<rows; i++)
			TT[i] = new int[columns];
		fill_value(hash_Table, 0, hash_Size - 1, -1);									// File hash Table 1-D from range 0 to 128 with -1
		maintain_Hash(file, hash_Table, columns);										// Maintain 1-D hash Table by reading 1st row of Table specifies the characters
		fill_TT(file, TT, rows, columns);												// File 2-D array with all specified data given in Specs.txt and then close
		file.close();
		CompactedColumns = compaction(TT, hash_Table, hash_Size, rows, columns);		// Comparison of Columns and make empty of duplcation of columns
		CompactedTT = new int*[rows];													// Create new 2-D array dynamically with compacted Number of Columns
		for (int i = 0; i<rows; i++)
			CompactedTT[i] = new int[CompactedColumns];
		CompactedFilling(TT, CompactedTT, rows, columns);								// Fill new Compacted Table with Compacted Data from Old Table
		for (int i = 0; i<rows; i++)													// Delete Useless old Transistion Table
			delete TT[i];
		delete TT;
		bool CompactionOccur=true;
		if (CompactedColumns==columns)
			CompactionOccur=false;
		MakeCompactedFile(CompactedTT, hash_Table, hash_Size, rows, CompactedColumns,CompactionOccur);
	}
	else{																				// If Specs.txt file not Exists or problem while opening 
		cerr << "File not Open !!!" << endl;
		system("pause");
		return 0;
	}
	readInputFile(CompactedTT, hash_Table);												// Reading From another File named Input.txt containg string, Run on Lexical Analyzer using Compacted Table
	cout << endl << ' ';
	system("pause");
	return 0;
}
