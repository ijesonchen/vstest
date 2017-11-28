/*
ANS:101100

In this assignment you will implement one or more algorithms for the 2SAT 
problem. Here are 6 different 2SAT instances:
2sat1.txt 2sat2.txt 2sat3.txt 2sat4.txt 2sat5.txt 2sat6.txt
The file format is as follows. In each instance, the number of variables 
and the number of clauses is the same, and this number is specified on 
the first line of the file. Each subsequent line specifies a clause via 
its two literals, with a number denoting the variable and a "-" sign 
denoting logical "not". For example, the second line of the first data file 
is "-16808 75250", which indicates the clause ~x16808∨x75250.
Your task is to determine which of the 6 instances are satisfiable, and 
which are unsatisfiable. In the box below, enter a 6-bit string, where the 
ith bit should be 1 if the ith instance is satisfiable, and 0 otherwise. 
For example, if you think that the first 3 instances are satisfiable and 
the last 3 are not, then you should enter the string 111000 in the box below.

DISCUSSION: This assignment is deliberately open-ended, and you can implement 
whichever 2SAT algorithm you want. For example, 2SAT reduces to computing 
the strongly connected components of a suitable graph (with two vertices per 
variable and two directed edges per clause, you should think through the 
details). This might be an especially attractive option for those of you who 
coded up an SCC algorithm in Part 2 of this specialization. Alternatively, 
you can use Papadimitriou's randomized local search algorithm. (The algorithm 
from lecture is probably too slow as stated, so you might want to make one or 
more simple modifications to it --- even if this means breaking the analysis 
given in lecture --- to ensure that it runs in a reasonable amount of time.) 
A third approach is via backtracking. In lecture we mentioned this approach 
only in passing; see Chapter 9 of the Dasgupta-Papadimitriou-Vazirani book, 
for example, for more details.

*NOTE*
SUBJECT: is 2-SAT instance satisfiable? -> 0/1
HINT:
	1. 2-SAT to SCC
	2. Papadimitriou's randomized local search algorithm. too slow, should improve
	3. backtracking, DPV chapter 9
*/

#include "common.h"
void Test2Sat(void);

using namespace std;



bool Test2Sat(const string& fn);

void Test2Sat(void)
{
	Test2Sat("data\\zwk16-prog_2sat1.txt");
	Test2Sat("data\\zwk16-prog_2sat2.txt");
	Test2Sat("data\\zwk16-prog_2sat3.txt");
	Test2Sat("data\\zwk16-prog_2sat4.txt");
	Test2Sat("data\\zwk16-prog_2sat5.txt");
	Test2Sat("data\\zwk16-prog_2sat6.txt");
	// 1 0 交替，除了15 16
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_1_2.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_2_2.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_3_4.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_4_4.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_5_8.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_6_8.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_7_10.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_8_10.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_9_20.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_10_20.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_11_40.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_12_40.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_13_80.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_14_80.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_15_100.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_16_100.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_17_200.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_18_200.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_19_400.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_20_400.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_21_800.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_22_800.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_23_1000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_24_1000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_25_2000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_26_2000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_27_4000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_28_4000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_29_8000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_30_8000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_31_10000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_32_10000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_33_20000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_34_20000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_35_40000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_36_40000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_37_80000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_38_80000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_39_100000.txt");
	Test2Sat("TestCase\\assignment4TwoSat\\input_beaunus_40_100000.txt");
}
