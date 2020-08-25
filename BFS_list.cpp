#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

// Map class
class Map {
public:
    const static int mapWidth = 6;
    const static int mapHeight = 5;
    vector<vector<int> > grid = {
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0 }
    };
};

// Planner class
class Planner : Map {
public:
    int start[2] = { 0, 0 };
    int goal[2] = { mapHeight - 1, mapWidth - 1 };
    int cost = 1;

    string movements_arrows[4] = { "^", "<", "v", ">" };

    vector<vector<int> > movements{
        { -1, 0 },
        { 0, -1 },
        { 1, 0 },
        { 0, 1 }
    };
};

// Template function to print 2D vectors of any type
template <typename T>
void print2DVector(T Vec)
{
    for (int i = 0; i < Vec.size(); ++i) {
        cout<<"[";
        for (int j = 0; j < Vec[0].size(); ++j) {
            cout << Vec[i][j] << ' ';
        }
        cout << "]";
        if(i<Vec.size()-1) cout<<",";
    }
    cout<<endl;
}

// Search function which will generate the expansion list ####*/
void search(Map map, Planner planner)
{

vector<vector <int> > frontiers = { {0, planner.start[0], planner.start[1]} };
map.grid[planner.start[0]][planner.start[1]] = 1;
int  expansion = 0;
int findTarget =  false;
while(frontiers.size()>0)
{
sort(frontiers.begin(),frontiers.end()); 
reverse(frontiers.begin(),frontiers.end());   
cout<< "Expansion #: "<< expansion << endl;

// Note  list
cout<< "Open List:" ;
print2DVector(frontiers);

// Selected  note for BFS
vector<int> frontier = frontiers.back();
frontiers.pop_back();
cout<< "Cell Picked:["<<frontier[0]<<" "<<frontier[1]<<" "<<frontier[2] << "]" <<endl;
cout<<endl;
if(frontier[1]==planner.goal[0] && frontier[2]==planner.goal[1])
{
findTarget = true;
break;
}

//
for(int i=0;i<planner.movements.size();i++)
{
int new_weight = frontier[0]+1;
int new_y = frontier[1] + planner.movements[i][0];
int new_x = frontier[2] + planner.movements[i][1];
if(new_y>=0 && new_y<map.mapHeight  && \
    new_x>=0 && new_x<map.mapWidth  && \
    map.grid[new_y][new_x]==0 ){
    frontiers.push_back({new_weight,new_y,new_x});
    map.grid[new_y][new_x] = 1;
}
}
expansion +=  1;
}
if(!findTarget) cout<<"Blocked!";

}

int main()
{
    // Instantiate map and planner objects
    Map map;
    Planner planner;

    // Search for the expansions
    search(map, planner);

    return 0;
}
