/*
Creator: Thomas Opolski
Task: Use the hash-join algorithm to implement a join (equijoin) of R1 and R2. Assume that the
hash function is f(k) = k mod N, where N is the number of buckets allowed in your hash
structure/table.
Date Created: 12/9/19
Date Modified: 12/10/19
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

using db_table = vector<vector<int>>;
static int MIN_SIZE = 1;
static int MAX_BUCKETS = 5; //aka N

/*	
--Tables for testing purposes--

db_table table1 = {
	{2, 3, 5},
	{4, 5, 6},
	{3, 3, 7}
};

db_table table2 = {
	{4, 5, 6, 1},
	{2, 4, 5, 3},
	{4, 2, 3, 2},
	{1, 2, 2, 3}
};
*/

void printTable(db_table table) {
	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

db_table getTableFromFile(string fname) {
	//put content of file from fname into table (vector vector int)
	db_table table;
	int cNum;
	string cLine;

	//input file stream
	ifstream ifs;
	ifs.open(fname);
	int i=0;
	while (getline(ifs,cLine)) {
		istringstream ss(cLine);
		table.push_back({});	//create empty for pushing into
		
		//parse through string stream
		while (ss >> cNum) {
			table[i].push_back(cNum);
		}
		i++;
	}

	return table;
}

db_table hashJoin(db_table tableA, db_table tableB, int a1, int a2) {
	//First create the result table
	db_table result = tableA;

	//For each attribute in tableA at a1 hash into an array
	multimap<int, int> m;
	pair<int, int> p;
	int hashValue;
	int selectivity = 0; //increment for each tuple satisfying F

	//Creating the hash table for table 2 to search for elements in table 1
	for (int i = 0; i < tableA.size(); i++) {
		hashValue = tableA[i][a1] % MAX_BUCKETS;
		p = { hashValue, i };
		m.insert(p);
	}

	//For each attribute in tableB at a2, if the value exists as key in the hash table, 
		//search for identical value in that key. Then place row into result
	for (int i = 0; i < tableB.size(); i++) {
		hashValue = tableB[i][a2] % MAX_BUCKETS;
		//if bucket not empty
		if (m.count(hashValue) > 0) {
			auto range = m.equal_range(hashValue);
			//iterate through range and add this row to result row
			for (auto r = range.first; r != range.second; r++) {
				int currRow = (*r).second;
				result[currRow].insert(result[currRow].end(), tableB[i].begin(), tableB[i].end());
				selectivity++; //for each tuple satifying condition
			}
		}	
	}

	cout << "The selectivity is " << selectivity << "/" << (tableA.size() * tableB.size()) << endl;

	return result;
}


int main() {

	int atrbA, atrbB;
	string filenameA, filenameB;
	db_table tableA, tableB;
	db_table result;

	//User filename inputs
	cout << "Enter the first file name to join." << endl;
	cin >> filenameA;
	cout << "Enter the second file name to join." << endl;
	cin >> filenameB;

	//Getting tables from files
	tableA = getTableFromFile(filenameA);
	tableB = getTableFromFile(filenameB);

	//Getting join attributes from user
	cout << "Enter the first attribute as an int from table 1 to join with table 2:" << endl;
	printf("(min: %d, max: %d)\n", MIN_SIZE, tableA.size());
	cin >> atrbA;

	cout << "Enter the first attribute as an int from table 2 to join with table 1:" << endl;
	printf("(min: %d, max: %d)\n", MIN_SIZE, tableB.size());
	cin >> atrbB;

	//Printing tables
	cout << endl << "Joining R1 at attribute " << atrbA << endl;
	printTable(tableA);
	cout << "with R2 at attribute " << atrbB << endl;
	printTable(tableB);

	cout << "Tables joining..."<< endl;
	//Hash join tables
	result = hashJoin(tableA, tableB, atrbA-1, atrbB-1);

	//Print final table
	printTable(result);

	system("pause");
	return 0;
}