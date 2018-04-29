#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>
#include <vector>

#include "QuadraticProbing.h"
#include "SeparateChaining.h"
#include "LinearProbing.h"

using std::string;
using std::cout;
using std::endl;
using std::ifstream;

// pardon my global varbarians, I promise I will keep them under control
QuadraticProbing<string> QuadraticProbingHT;
SeparateChaining<string> ChainingHT;
LinearProbing<string> LinearProbingHT;

double InsertionTimerChainingHT = 0.0;
double InsertionTimerLinearProbingHT = 0.0;
double InsertionTimerQuadraticProbingHT = 0.0;

double SearchTimerChainingHT = 0.0;
double SearchTimerLinearProbingHT = 0.0;
double SearchTimerQuadraticProbingHT = 0.0;

int CollisionsChainingHT = 0;
int CollisionsLinearProbingHT = 0;
int CollisionsQuadraticProbingHT = 0;

void printResults(int hType, int datArrSz, int querArrSz){
	string type;
	if (hType == 1)
		type = "simple";
	else if (hType == 2)
		type = "prefix";
	else if (hType == 3)
		type = "full-hash";
	
	cout << setw(0) << setfill(' ') << type
		<< " : " << (double)(InsertionTimerQuadraticProbingHT/CLOCKS_PER_SEC) 
		<< " : " << (double)(InsertionTimerQuadraticProbingHT/(CLOCKS_PER_SEC*datArrSz))
		<< " : " << CollisionsQuadraticProbingHT 
		<< " : " << (double)(SearchTimerQuadraticProbingHT/CLOCKS_PER_SEC)
		<< " : " << (double)(SearchTimerQuadraticProbingHT/(CLOCKS_PER_SEC*querArrSz)) << "\n";

		
}

void InsertIntoQuadraticProbingHT(vector<string> &DatArr)
{
	clock_t t1, t2;

	for(vector<string>::iterator i = DatArr.begin(); i != DatArr.end(); ++i)
	{
		t1 = clock();
		QuadraticProbingHT.insert(*i);
		t2 = clock();
		InsertionTimerQuadraticProbingHT += (t2 - t1);
	}
	CollisionsQuadraticProbingHT = QuadraticProbingHT.getCollisions();
}

void SearchQuadraticProbingHT(vector<string> &QuerArr)
{
	clock_t t1, t2;

	for(vector<string>::iterator i = QuerArr.begin(); i != QuerArr.end(); ++i)
	{
		t1 = clock();
		LinearProbingHT.contains(*i);
		t2 = clock();
		SearchTimerLinearProbingHT += (t2 - t1);
	}
}

int main(int argc, char* argv[])
{
	ifstream file;
	string datafilename = "OHenry.txt";
	string queryfilename = "queries.txt";
	vector<string> DataArray;
	vector<string> QueryArray;
	string buffer;

	// code for opening filenames passed as arguments 
	if (argc>1){
		file.open(argv[1]);
		if (file.good()){
			cout << "data file opened correctly" << endl;
			datafilename = argv[1];
			file.close();
		}
		else {
			cout << "data file not found" << endl;
		}
		if(argc>2){
			file.open(argv[2]);
			if(file.good()){
				cout << "query file open correctly" << endl;
				queryfilename = argv[2];
				file.close();
			}
			else{
				cout << "query file not found" << endl;
			}
		}
	}	

	// read files into vectors
	file.open(datafilename);
	while(file >> buffer){
		DataArray.push_back(buffer);
	}
	file.close();
	file.open(queryfilename);
	while(file >> buffer){
		QueryArray.push_back(buffer);
	}
	file.close();

	// print heading for data
	cout << setw(0) << "type" 
		<< " : " << "ins tot time" 
		<< " : " << "ins. avg time" 
		<< " : " << "# of collisions" 
		<< " : " << "search tot time"
		<< " : " << "search avg time" << "\n";
	
	// experiment with different hash functions
	QuadraticProbingHT.setHash(1);
	InsertIntoQuadraticProbingHT(DataArray);
	SearchQuadraticProbingHT(QueryArray);
	printResults(1, DataArray.size(), QueryArray.size());

	QuadraticProbingHT.setHash(2);
	InsertIntoQuadraticProbingHT(DataArray);
	SearchQuadraticProbingHT(QueryArray);
	printResults(2, DataArray.size(), QueryArray.size());

	QuadraticProbingHT.setHash(3);
	InsertIntoQuadraticProbingHT(DataArray);
	SearchQuadraticProbingHT(QueryArray);
	printResults(3, DataArray.size(), QueryArray.size());


	return 0;
}
