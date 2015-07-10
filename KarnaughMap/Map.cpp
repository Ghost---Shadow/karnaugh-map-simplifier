#include"Map.h"
#include<iostream>

using namespace std;
Map::Map():
	isSOP(false){	
}

void Map::parseLine(string line){
	// Store the numbers in the input string as an array
	int numbers[16];

	// Convert the line to an array of numbers
	int length = parseToArray(line,numbers);	

	// Initialize the matrix with 0
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			matrix[i][j] = 0;

	// Change the specific indices to 1
	for(int i = 0; i < length; i++){
		// Convert indices to greycode
		int rowIndex = (numbers[i]/4) ^ ((numbers[i]/4)>>1);
		int columnIndex = (numbers[i]%4) ^ ((numbers[i]%4)>>1);		
		matrix[rowIndex][columnIndex] = 1;
	}
}

void Map::drawMap(){
	cout<<endl;

	int bit = isSOP?1:0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(matrix[i][j])
				cout<<bit;
			else 
				cout<<!bit;
			cout<<" ";
		}
		cout<<endl;
	}
}

int Map::parseToArray(string line, int numbers[16]){
	line+=" ";
	int count = 0,lastSpace = 0;
	for(unsigned int i = 0; i < line.length(); i++){
		// Search for the next space
		if(line[i] == ' '){
			// Parse the next number
			int temp = stoi(line.substr(lastSpace,i-lastSpace),nullptr);
			// Store the location of this space
			lastSpace = i;
			// Check boundary conditions
			if(temp < 0 || temp > 15) continue;
			numbers[count++] = temp;			
		}
	}
	return count;
}

void Map::getMatrix(int m[4][4]){
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			m[i][j] = matrix[i][j];
}
