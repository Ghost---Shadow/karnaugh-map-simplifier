#include "Simplifier.h"
#include<iostream>
#include<ctype.h>


Simplifier::Simplifier(Map *map):
	map(map)
{	
}


Simplifier::~Simplifier(void)
{
}

string Simplifier::getParsedExpression(){
	map->getMatrix(matrix);
	string rows[] = {"cd","cD","CD","Cd"};
	string columns[] = {"ab","aB","AB","Ab"};

	string result = "";

	// The connectives in SOP and POS are opposite
	string connective1 = map->getIsSop()?" + ": ")(";
	string connective2 = map->getIsSop()?"":" + ";

	// No connectives are needed before the first expression
	bool firstExpression = true;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){			
			if(matrix[i][j] == 1){
				if(!firstExpression)
					result += connective1;	
				else 
					firstExpression = false;
				if(!map->getIsSop())
					result += toggleCase(columns[j][0]) + connective2 + toggleCase(columns[j][1]) + connective2 + 
					toggleCase(rows[i][0]) + connective2 + toggleCase(rows[i][1]);
				else
					result += columns[j][0] + connective2 + columns[j][1] + connective2 + 
					rows[i][0] + connective2 + rows[i][1];
			}
		}
	}
	// If POS then wrap everything around with brackets
	if(!map-> getIsSop()) result = "(" + result + ")";
	return result;
}
string Simplifier::getSimplifiedExpression(){
	map->getMatrix(matrix);
	string result = "";

	// A linked list where all the groups will be stored
	vector<vector <Pairs>> groups;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){	
			if(matrix[i][j] == 1)
				pushUnsortedGroups(groups,i,j);			
		}
	}
	for(int i = 0; i < groups.size(); i++) 
		sortUnsortedGroup(groups[i]);

	removeDuplicateGroups(groups);
	printGroups(groups);

	// Insert appropriate connectives between groups of expressions
	for(int i = 0; i < groups.size(); i++) 
		result += (i?(map-> getIsSop()?" + ":")("): "") + generateStringFromGroup(groups[i]);

	if(!map-> getIsSop()) result = "(" + result + ")";
	return result;
}

void Simplifier::pushUnsortedGroups(vector<vector <Pairs>> &groups,int i, int j){
	vector<Pairs> group;
	Pairs temp;
	bool foundGroups = false;
	int d[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

	temp.i = i; temp.j = j;
	group.push_back(temp);

	// Search for pairs in four cardinal directions
	for(int k = 0; k < 4; k++){
		// Check for pairs
		if(matrix[(i+d[k][0]+4)%4][(j+d[k][1]+4)%4] == 1){
			temp.i = (i+d[k][0]+4)%4; temp.j = (j+d[k][1]+4)%4;
			group.push_back(temp);

			// Check for long quad
			if(matrix[(i+2*d[k][0]+4)%4][(j+2*d[k][1]+4)%4] == 1 && 
				matrix[(i+3*d[k][0+4])%4][(j+3*d[k][1]+4)%4] == 1){
					temp.i = (i+2*d[k][0]+4)%4; temp.j =(j+2*d[k][1]+4)%4;
					group.push_back(temp);

					temp.i = (i+3*d[k][0]+4)%4; temp.j =(j+3*d[k][1]+4)%4;
					group.push_back(temp);			

					// Check for Octant
					if(matrix[(i+0*d[k][0]+d[(k+1)%4][0]+4)%4][(j+0*d[k][1]+d[(k+1)%4][1]+4)%4] == 1 && 
						matrix[(i+1*d[k][0]+d[(k+1)%4][0]+4)%4][(j+1*d[k][1]+d[(k+1)%4][1]+4)%4] == 1 && 
						matrix[(i+2*d[k][0]+d[(k+1)%4][0]+4)%4][(j+2*d[k][1]+d[(k+1)%4][1]+4)%4] == 1 && 
						matrix[(i+3*d[k][0]+d[(k+1)%4][0]+4)%4][(j+3*d[k][1]+d[(k+1)%4][1]+4)%4] == 1){

							temp.i = (i+0*d[k][0]+d[(k+1)%4][0]+4)%4; temp.j =(j+0*d[k][1]+d[(k+1)%4][1]+4)%4;
							group.push_back(temp);

							temp.i = (i+1*d[k][0]+d[(k+1)%4][0]+4)%4; temp.j =(j+1*d[k][1]+d[(k+1)%4][1]+4)%4;
							group.push_back(temp);	

							temp.i = (i+2*d[k][0]+d[(k+1)%4][0]+4)%4; temp.j =(j+2*d[k][1]+d[(k+1)%4][1]+4)%4;
							group.push_back(temp);

							temp.i = (i+3*d[k][0]+d[(k+1)%4][0]+4)%4; temp.j =(j+3*d[k][1]+d[(k+1)%4][1]+4)%4;
							group.push_back(temp);	
					}

					groups.push_back(group);
					group.clear();
					foundGroups = true;
					break;
			}

			// Check for square quad
			if(matrix[(i+0*d[k][0]+d[(k+1)%4][0]+4)%4][(j+0*d[k][1]+d[(k+1)%4][1]+4)%4] == 1 && 
				matrix[(i+1*d[k][0]+d[(k+1)%4][0]+4)%4][(j+1*d[k][1]+d[(k+1)%4][1]+4)%4] == 1){
					temp.i = (i+0*d[k][0]+d[(k+1)%4][0]+4)%4; temp.j =(j+0*d[k][1]+d[(k+1)%4][1]+4)%4;
					group.push_back(temp);

					temp.i = (i+1*d[k][0]+d[(k+1)%4][0]+4)%4; temp.j =(j+1*d[k][1]+d[(k+1)%4][1]+4)%4;
					group.push_back(temp);	
			}
			groups.push_back(group);
			group.clear();
			temp.i = i; temp.j = j;
			group.push_back(temp);
			foundGroups = true;
		} 
	}	
	// If no pairs, quads or octants were found, push the unit group
	if(!foundGroups)
		groups.push_back(group);
}
void Simplifier::sortUnsortedGroup(vector <Pairs> &group){

	// Bubble sort
	for(int i = 0; i < group.size(); i++){		
		for(int j = 0; j < group.size()-i-1; j++){
			if(group[j].i*4+group[j].j > group[j+1].i*4+group[j+1].j){				
				Pairs temp = group[j];
				group[j] = group[j+1];
				group[j+1] = temp;					
			}
		}
	}	

}
void Simplifier::removeDuplicateGroups(vector<vector <Pairs>> &groups){
	vector<string> temp;

	// Generate a string list from the groups
	for(int i = 0; i < groups.size(); i++){
		temp.push_back("");
		for(int j = 0; j < groups[i].size(); j++){			
			temp[i] += to_string(groups[i][j].i*4 + groups[i][j].j) + " ";			
		}		
	}

	// Remove duplicate entries
	for(int i = 0; i < temp.size(); i++){
		for(int j = i+1; j < temp.size(); j++){
			if (temp[i].compare(temp[j]) == 0) {
				temp.erase(temp.begin()+j);
				groups.erase(groups.begin()+j);				
			}			
		}
	}		

	// Remove subset entries
	for(int i = 0; i < groups.size(); i++){
		vector<Pairs> group = groups[i];
		for(int j = 0; j < groups.size(); j++){
			if(i == j) continue; 
			if(isSubsetOf(groups[j],group)){				
				groups.erase(groups.begin()+j);			
				j--;
			}
		}
	}
	// Remove redundant entries
	bool allCommon;
	for(int i = 0; i < groups.size(); i++){		
		vector<Pairs> group = groups[i];
		allCommon = true;
		for(int j = 0; j < group.size(); j++){
			if(!hasCommonPair(group[j],groups,i)){
				allCommon = false;
				break;
			}
		}
		if(allCommon){ 
			groups.erase(groups.begin() + i);
			i--;
		}
	}
}
bool Simplifier::hasCommonPair(Pairs pair,vector <vector <Pairs>> &groups, int skip){
	for(int i = 0; i < groups.size(); i++){
		// Do not compare with self
		if(i == skip) continue;
		for(int j = 0; j < groups[i].size(); j++){
			if(groups[i][j].i*4 + groups[i][j].j == pair.i * 4 + pair.j)
				return true;
		}
	}
	return false;
}


bool Simplifier::isSubsetOf(vector <Pairs> &group1,vector <Pairs> &group2){
	bool found;

	// Check if all members of group1 are in group2
	for(int i = 0; i < group1.size(); i++){
		found = false;
		for(int j = 0; j < group2.size(); j++){
			if(group1[i].i*4 + group1[i].j == group2[j].i*4 + group2[j].j){
				found = true;
				break;
			}
		}
		if(!found) return false;
	}
	return true;
}

void Simplifier::printGroups(vector<vector <Pairs>> &groups){
	cout<<endl;
	for(int i = 0; i < groups.size(); i++){		
		switch(groups[i].size()){
		case 1: cout<<"Unit:   "; break;
		case 2: cout<<"Pair:   "; break;
		case 4: cout<<"Quad:   "; break;
		case 8: cout<<"Octant: "; break;
		}
		for(int j = 0; j < groups[i].size(); j++){
			int greyI = groups[i][j].i ^ (groups[i][j].i >> 1);
			int greyJ = groups[i][j].j ^ (groups[i][j].j >> 1);
			cout<<greyI * 4 + greyJ<<" ";
			//cout<<groups[i][j].i*4 + groups[i][j].j<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

string Simplifier::generateStringFromGroup(vector <Pairs> &group){
	string result;
	string rows[] = {"cd","cD","CD","Cd"};
	string columns[] = {"ab","aB","AB","Ab"};

	string temp2 = columns[group[0].j] + rows[group[0].i];

	// If the group is a unit group, no processing is necessary
	if(group.size() == 1){
		result = temp2;
	} else {
		// Store only the common terms
		for(int i = 1; i < group.size(); i++){
			result = "";
			string temp1 = columns[group[i].j] + rows[group[i].i];

			for(int j = 0; j < temp2.size(); j++){
				if(temp1.find(temp2[j]) != string::npos){
					result += temp2[j];
				}
			}
			temp2 = result;		
		}
	}

	// If POS then use suitable connectives
	if(!map->getIsSop()){
		temp2 = result;
		result = "";
		for(int i = 0; i < temp2.length(); i++){
			result += (i?" + ":"");  			
			result.push_back(toggleCase(temp2[i]));
		}
	}

	return result;
}

char Simplifier::toggleCase(char c){
	if(islower(c))
		return toupper(c);
	else
		return tolower(c);
}