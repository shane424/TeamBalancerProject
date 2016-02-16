#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>

using namespace std;

typedef struct{
	int id;
	int attack;
	int defence;
	int team;
	double worth;
	bool isUsed;
}unit;

class builder{
	public:
		builder();
		~builder();
		void build();
	private:
		string teams;
		int unitsPerTeam;
		int totalNumberOfUnits;
		int numOfTeams;
		string info;
		int unitNumber;
		int commaLocation;
		unit temp;
		vector<unit> unitList;
		vector<unit> endList;
		void parseCSV();
		void assignUnits();
		void outputTeams();
};

builder::builder(){}
builder::~builder(){}

void builder::build(){
	cout << "starting build" << endl;
	parseCSV();
	cout << "done parsing" << endl;
	assignUnits();
	cout << "done assigning teams" << endl;
	outputTeams();
	cout << "done outputting" << endl;
}

void builder::parseCSV(){
	unitNumber = 0;
	getline(cin, teams);
	numOfTeams = atoi(teams.c_str());
	while(getline(cin, info)){
		if(info.empty())
			break;
		commaLocation = info.find(',');
		temp.id = unitNumber;
		temp.attack = atoi(info.substr(0,commaLocation).c_str());
		temp.defence = atoi(info.substr(commaLocation+1,info.length()).c_str());
		unitList.push_back(temp);
		unitNumber++;
	}
	cout << "!" << endl;
	cout << numOfTeams << endl;
	totalNumberOfUnits = unitList.size();
	cout << unitList.size() << endl;
}

void builder::assignUnits(){
	unitsPerTeam = unitList.size()/numOfTeams;	
	double totalAttack = 0;			// Overall total attack between all units.
	double totalDefence = 0;		// Overall total defence between all units.
//----------------------------------------------------------------/ 
	double averageTeamAttack = 0;		// average teams attack.
	double averageTeamDefence = 0;		// average teams defence.
	double averageTeamTotal = 0;
	double averageUnitsAttack = 0;		// average units attack.
	double averageUnitsDefence = 0;		// average units defence.
//----------------------------------------------------------------/	
	double curAttackStat = 0;		// Current unit's attack.
	double curDefenceStat = 0;		// Current unit's attack.
	double realAttackDifference = 0;		// The actual attack difference. (ideal)
	double realDefenceDifference = 0;		// The actual defence difference.
	double curAttackDifference = 0;		// Current attack difference from the incremental average.
	double curDefenceDifference = 0;	// Current defence difference from the incremental average	.
	double curTotalDifference = 0;		// Current units total difference between the average attack&defence.
	double curTeamAttack = 0;		// Current teams attack.
	double curTeamDefence = 0;		// Current teams defence.
	double curTeamTotal = 0;
	int curSpotInVector = 0;		// What position it is at currently.
	bool isDone = false;
	int count = 0;
//----------------------------------------------------------------/	
	cout << "before first for" << endl;
	for(int i = 0;i < unitList.size(); i++){
		unitList[i].worth = 0;
		unitList[i].team = -1;
		totalAttack += unitList[i].attack;
		totalDefence += unitList[i].defence;
		unitList[i].isUsed = false;
		cout << unitList[i].id << endl;
	}
	
	averageTeamAttack = totalAttack/numOfTeams;
	averageTeamDefence = totalDefence/numOfTeams;
	averageUnitsAttack = averageTeamAttack/unitsPerTeam;
	averageUnitsDefence = averageTeamDefence/unitsPerTeam;
	cout << "before big for" << endl;
/* 	for(int o = 0; o < numOfTeams; o++){
		cout << "beginning outer loop for num of teams" << endl;
		curTeamAttack = 0;
		curTeamDefence = 0;
		for(int i = 0; i < unitsPerTeam; i++){
			if(unitList.size() == 1){
				cout << "size is 1" << endl;
				unitList[i].team = o;
				cout << i << " " << unitList[i].id << " " << unitList[i].team << endl;
				break;
			}
			realAttackDifference = (averageUnitsAttack * (i + 1)) - curTeamAttack;
			curAttackDifference = realAttackDifference;
			cout << "curTeamAttack: " << curTeamAttack << endl;
			cout << "curAttackDifference: " << curAttackDifference << endl;
			realDefenceDifference = (averageUnitsDefence * (i + 1)) - curTeamDefence;
			curDefenceDifference = realDefenceDifference;
			cout << "curTeamDefence: " << curTeamDefence << endl;
			cout << "curDefenceDifference: " << curDefenceDifference << endl;
			// Statistical Approach //
 			for(int j = 0; j < totalNumberOfUnits; j++){
					curAttackStat = unitList[j].attack;
					curDefenceStat = unitList[j].defence;
					curAttackDifference = curAttackDifference - curAttackStat;
					curDefenceDifference = (curDefenceDifference - curDefenceStat);
					curTotalDifference = curAttackDifference + curDefenceDifference;
					cout << "Unit: " << unitList[j].id << endl;
					cout << "curAttackStat: " << curAttackStat << endl;
					cout << "curDefenceStat: " << curDefenceStat << endl;
					cout << "curAttackDifference: " << curAttackDifference << endl;
					cout << "curDefenceDifference: " << curDefenceDifference << endl;
					unitList[j].worth = curTotalDifference;
					cout << "unitsWorth: " << unitList[j].worth << endl;
					curAttackDifference = realAttackDifference;
					curDefenceDifference = realDefenceDifference;
			} 
			// End Statistical Approach //
			for(int j = 0; j < totalNumberOfUnits; j++){
				
			}
			cout << "after calculationg differences" << endl;
			double best = unitList[0].worth;
			placementID = unitList[0].id;
			int position = 0;
			bool isBest = false;
			count = i;
			cout << "before abs" << endl;
			for(int k = 1; k < unitList.size(); k++){
			 		if(abs(unitList[k].worth) < abs(best)){
						if(k!=unitList.size() - 1){
							best = abs(unitList[k].worth);
							position = k;
						}
						else{
							best = unitList[k].worth;
							position = k;
						}
					}
					else{
						best = best;
						position = position;
					} 
					if(unitList[k].worth > 0 && unitList[k].worth < best){
						if(k!=unitList.size() - 1){
							best = unitList[k].worth;
							position = k;
						}
						else{
							best = unitList[k].worth;
							position = k;
						}
					}
					else{
						best = best;
						position = position;
					}  
					cout << "Abs: " << abs(unitList[k].worth) << endl;
					cout << "Best Abs: " << abs(best) << endl;
					cout << "Position: " << position << endl;
					cout << "ID: " << unitList[position].id << endl;
				}
			cout << "after abs" << endl;
			unitList[position].team = o;
			curTeamAttack += unitList[position].attack;
			curTeamDefence += unitList[position].defence;
			cout << "TeamNumber: " << unitList[position].team << endl;
			cout << "Position: " << position << endl;
			cout << "ID: " << unitList[position].id << endl;
			cout << "UnitListSize: " << unitList.size() << endl;
			for(int mm = 0; mm < unitList.size(); mm++){
				cout << unitList[mm].id;
			}
			cout << endl;
			endList.push_back(unitList[position]);
			unitList.erase(unitList.begin() + (position));
			for(int m = 0; m < unitList.size(); m++){
				cout << unitList[m].id;
			}
			cout << endl;
			cout << "end of function" << endl;
			totalNumberOfUnits--;
		}
	} */

	for(int o = 0; o < numOfTeams; o++){
		curTeamAttack = 0;
		curTeamDefence = 0;
		curTotalDifference = 0;
		isDone = false;
		cout << "beginning of outer loop" << endl;
		while(unitList.size() > 0){
			cout << "While loop for the " << o << "th time" << endl;
			for(int i = 0; i < totalNumberOfUnits; i++){
				cout << "In For Loop. # of Units: " << totalNumberOfUnits << endl;
				realAttackDifference = (averageUnitsAttack * (i + 1)) - curTeamAttack;
				curAttackDifference = realAttackDifference;
				//cout << "curTeamAttack: " << curTeamAttack << endl;
				//cout << "curAttackDifference: " << curAttackDifference << endl;
				realDefenceDifference = (averageUnitsDefence * (i + 1)) - curTeamDefence;
				curDefenceDifference = realDefenceDifference;
				averageTeamTotal = averageTeamAttack + averageTeamDefence;
				//cout << "curTeamDefence: " << curTeamDefence << endl;
				//cout << "curDefenceDifference: " << curDefenceDifference << endl;
				// Statistical Approach //
				for(int j = 0; j < totalNumberOfUnits; j++){
						curAttackStat = unitList[j].attack;
						curDefenceStat = unitList[j].defence;
						curAttackDifference = curAttackDifference - curAttackStat;
						curDefenceDifference = (curDefenceDifference - curDefenceStat);
						curTotalDifference = curAttackDifference + curDefenceDifference;
						/* cout << "Unit: " << unitList[j].id << endl;
						cout << "curAttackStat: " << curAttackStat << endl;
						cout << "curDefenceStat: " << curDefenceStat << endl;
						cout << "curAttackDifference: " << curAttackDifference << endl;
						cout << "curDefenceDifference: " << curDefenceDifference << endl;
						 */unitList[j].worth = curTotalDifference;
						cout << "unitsWorth: " << unitList[j].worth << endl;
						curAttackDifference = realAttackDifference;
						curDefenceDifference = realDefenceDifference;
				} 
				// End Statistical Approach //
				cout << "after calculationg differences" << endl;
				double best = unitList[0].worth;
				int position = 0;
				bool isBest = false;
				cout << "before abs" << endl;
				for(int k = 1; k < unitList.size(); k++){
						if(abs(unitList[k].worth) < abs(best)){
							if(k!=unitList.size() - 1){
								best = abs(unitList[k].worth);
								position = k;
							}
							else{
								best = unitList[k].worth;
								position = k;
							}
						}
						else{
							best = best;
							position = position;
						} 
						if(unitList[k].worth > 0 && unitList[k].worth < best){
							if(k!=unitList.size() - 1){
								best = unitList[k].worth;
								position = k;
							}
							else{
								best = unitList[k].worth;
								position = k;
							}
						}
						else{
							best = best;
							position = position;
						}  
/* 						cout << "Abs: " << abs(unitList[k].worth) << endl;
						cout << "Best Abs: " << abs(best) << endl;
						cout << "Position: " << position << endl;
						cout << "ID: " << unitList[position].id << endl; */
					}
				cout << "after abs" << endl;
				unitList[position].team = o;
				curTeamAttack += unitList[position].attack;
				curTeamDefence += unitList[position].defence;
				curTeamTotal = curTeamAttack + curTeamDefence;
/* 				cout << "TeamNumber: " << unitList[position].team << endl;
				cout << "Position: " << position << endl;
				cout << "ID: " << unitList[position].id << endl;
				cout << "UnitListSize: " << unitList.size() << endl; */
				for(int mm = 0; mm < unitList.size(); mm++){
					cout << unitList[mm].id;
				}
				cout << endl;
				cout << "PUSHED: " << unitList[position].id << endl;
				endList.push_back(unitList[position]);
				cout << "After end list push" << endl;
				unitList.erase(unitList.begin() + (position));
				cout << "After erase, before for loop" << endl;
				for(int m = 0; m < unitList.size(); m++){
					cout << unitList[m].id;
				}
				cout << endl;
				totalNumberOfUnits--;
				if(unitList.size() == 1){
					cout << "size is 1" << endl;
					cout << position << endl;
					unitList[i].team = o;
					cout << i << " " << unitList[i].id << " " << unitList[i].team << endl;
					cout << "PUSHED BACK THE LAST ONE" << unitList[position].team << endl;
					endList.push_back(unitList[position]);
					cout << "after end" << endl;
					unitList.erase(unitList.begin());
					cout << "Before isDone" << endl;
					isDone = true;
					break;
				}
				double theDifference = averageTeamTotal - curTeamTotal;
				cout << "DIFFERENCE: " << theDifference << endl;
				if(theDifference == 0 || (theDifference >= 0 && theDifference <= 2) || (theDifference <= 0 && theDifference >= -2)){
					cout << " BROKE OUT OF THE CAGE " << endl;
					isDone = true;
					break;
				} 
				cout << endl;
				cout << "end of function" << endl;
				break;
				//isDone = true;
				//totalNumberOfUnits--;
			}
		}
	}
}

void builder::outputTeams(){
	bool comma = false;
	//////cout << "beginning output" << endl;
	for(int i = 0; i < numOfTeams; i++){
		double curTeamAttack = 0;
		double curTeamDefence = 0;
		//cout << "in first for" << endl;
		cout << "Team Number: " << i << endl;
		for(int j = 0; j < endList.size(); j++){
			//cout << "ID: " << endList[j].id << " + " <<  endl;
			//cout << "TEAM: " << endList[j].team << endl;
			//cout << j << endl;
			//cout << "hi" << endl;
			if(endList[j].team == i){
				//cout << "in if state" << endl;
				/* if(comma){
					cout << ",";
				}
				else{
					comma = true;
				}
				cout << unitList[j].id;*/
				curTeamAttack += endList[j].attack;
				curTeamDefence += endList[j].defence;
				cout << "in Team: " << endList[j].id << endl;
			}
		}
		cout << "Teams Attack: " << curTeamAttack << endl;
		cout << "Teams Defence: " << curTeamDefence << endl;
		comma = false;
		cout << endl;
	}
}

int main(){
	builder *start = new builder();
	start->build();
	
	//delete(start);
	
	return 0;
}