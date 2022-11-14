#include<iostream>
#include<stdio.h>
#include"Simplifier.cpp"

using namespace std;

int main(){	

	string line;
	Map map;
	Simplifier simplifier(&map);
	
	int choice;
	cout<<"1) SOP\n2) POS\n";
	cin>>choice;
	
	map.setIsSop(choice-1?false:true);

	// Read the line from the user
	cout<<"Enter the indices: ";
	cin.ignore();getline(cin,line);

	// Generate the Karnaugh's Map
	map.parseLine(line);

	// Draw the map on screen
	map.drawMap();

	// Print the input expression
	printf("\nInput Expression: %s\n",simplifier.getParsedExpression().c_str());

	// Simplify the input expression using Karnaugh Map and print it
	printf("\nSimplified Expression: %s\n",simplifier.getSimplifiedExpression().c_str());	

	// Wait for the user to press enter to exit
	getline(cin,line);
	return 0;
}
