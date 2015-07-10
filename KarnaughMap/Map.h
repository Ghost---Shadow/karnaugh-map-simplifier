#pragma once

#include<string>

class Map{
	private:
		// Store the map as a matrix
		int matrix[4][4];

		// Convert the line into an array
		int parseToArray(std::string line, int numbers[16]);

		// Are we solving SOP or POS
		bool isSOP;
	public:
		Map();

		// SOP or POS
		inline void setIsSop(bool isSOP) {this->isSOP = isSOP; }
		inline bool getIsSop() { return isSOP; }

		// Sum of products
		void parseLine(std::string line);
		
		// The simplifier will request the map for simplification
		void getMatrix(int m[4][4]); 
		
		// Draws the map
		void drawMap();
};
