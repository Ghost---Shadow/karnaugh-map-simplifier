#pragma once
#include"Map.h"
#include<vector>

using namespace std;

// Store index values as pairs
struct Pairs{
	int i,j;
};

class Simplifier
{
private:
	int matrix[4][4];
	Map* map;

	string rows[4]; 
	string columns[4]; 

	// Find all possible pairs, quads and octants and store them
	void pushUnsortedGroups(vector<vector <Pairs>> &groups,int i, int j);

	// Sort a given group
	void sortUnsortedGroup(vector <Pairs> &group);

	// Remove all duplicate and redundant groups
	void removeDuplicateGroups(vector<vector <Pairs>> &groups);

	// Get the final expression for a group
	string generateStringFromGroup(vector <Pairs> &group);

	// Print all the groups
	void printGroups(vector<vector <Pairs>> &groups);

	// Check if group1 is subset of group2
	bool isSubsetOf(vector <Pairs> &group1,vector <Pairs> &group2);

	// Check if pair exists in any other group
	bool hasCommonPair(Pairs pair,vector <vector <Pairs>> &groups, int skip);

	// Inverse Case
	char toggleCase(char c);

public:
	Simplifier(Map *map);
	~Simplifier(void);

	// Generate the expression for the input
	string getParsedExpression();

	// Generate the final result
	string getSimplifiedExpression();
};

