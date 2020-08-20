This file contains the criteria of working of BCSF16A508.cpp

Program simulates and accept the strings having same count of 01 and 10 otherwise rejected

Character Set = {0.1}
Rule : Same amount of 01 and 10 in string
Starting State : A
Final State(s) : A,B,D,E,G
Transition Table :

	    0    1
	A   B    E
	B   B    C
	C   D    C
	D   D    C
	E   F    E
	F   F    G
	G   F    G

Logic :
Read character from string and check it is 0 or 1. If none of these then rejected.
If 0 or 1 then check curent state and push new state (corresponding to character) into current state.
Repeat steps until string is completed.
After completion, If current state is in final states then accepted otherwise rejected.
Note : Empty string is accepted in this Finite Automaton.

* Coded by Abdullah Zafar (BCSF16A508) 