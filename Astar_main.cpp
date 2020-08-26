#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Map class
class Map {
public:
    const static int mapWidth = 6;
    const static int mapHeight = 5;
    vector<vector<double> > map = getMap();
    vector<vector<int> > grid = map_to_grid();
    vector<vector<int> > heuristic = generate_heuristic_map();

private:
    vector<vector<double> > getMap()
    {
        vector< vector<double> > map(mapHeight,vector<double>(mapWidth));
        ifstream ifs;
        ifs.open("map.txt");

        while(!ifs.eof()){
        for(int h=0; h< mapHeight; h++)
        {for(int w=0; w<mapWidth; w++)
        {
        ifs>>map[h][w];
        }
        }
        }
        return map;
    }

    vector<vector<int> > map_to_grid()
    {
        vector<vector<int> >  grid(mapHeight,vector<int>(mapWidth));
        for(int h=0; h<mapHeight; h++)
        {
        for(int w=0; w<mapWidth; w++){
            if(map[h][w]<0) grid[h][w] = 0;
            else grid[h][w] = 1;
        }
        }
        return grid;
    }

    vector<vector<int> > generate_heuristic_map()
    {
        int goal[2]={60,50};
        vector<vector <int> > heuristic(mapHeight,vector<int>(mapWidth));
        for(int h=0;h<mapHeight;h++)
        {
            for(int w=0;w<mapWidth;w++)
            {
                heuristic[h][w] = abs(h-goal[1])+abs(w-goal[0]);
            }
        }
        return heuristic;
    }

};

// Planner class
class Planner : Map {
public:
    int start[2] = { 60, 50 };
    int goal[2] = {230, 145 };
    int cost = 1;

    string movements_arrows[4] = { "^", "<", "v", ">" };

    vector<vector<int> > movements{
        { -1, 0 },
        { 0, -1 },
        { 1, 0 },
        { 0, 1 }
    };

    vector<vector<int> > path;
};

// Template function to print 2D vectors of any type
template <typename T>
void print2DVector(T Vec,bool lines=false)
{
    for (int i = 0; i < Vec.size(); ++i) {
        if(!lines) cout<<"[";
        for (int j = 0; j < Vec[0].size(); ++j) {
            cout << Vec[i][j] << ' ';
        }
        if(!lines) cout << "]";
       
        if(i<Vec.size()-1) 
        {
        if(lines) cout<<endl;    
        else cout<<",";
        }    
    }
    cout<<endl;
}

// Search function which will generate the expansion list ####*/
void search(Map map, Planner planner)
{
int expansion = 0;
int h_distance = 0;
int findTarget =  false;

h_distance = abs(planner.start[0]-planner.goal[0]) + abs(planner.start[1]-planner.goal[1]);
vector<vector <int> > frontiers = { {h_distance, 0, planner.start[0], planner.start[1]} };
map.grid[planner.start[0]][planner.start[1]] = 1;

vector<vector <int> > vector_map(map.mapHeight,vector<int>(map.mapWidth,-1));
vector<vector <int> > action_map(map.mapHeight,vector<int>(map.mapWidth,-1));
vector<vector <string> > path_map(map.mapHeight,vector<string>(map.mapWidth,"-"));
path_map[planner.goal[0]][planner.goal[1]] = "*";


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

vector_map[frontier[2]][frontier[3]] = frontier[1];

cout<< "Cell Picked:["<<frontier[0]<<" "<<frontier[1]<<" "<<frontier[2]<< " "<<frontier[3] << "]" <<endl;
cout<<endl;
if(frontier[2]==planner.goal[0] && frontier[3]==planner.goal[1])
{
findTarget = true;
break;
}

// Add node to frontiers and direction index to action_map
for(int i=0;i<planner.movements.size();i++)
{
int cost = frontier[1]+planner.cost;
int y = frontier[2] + planner.movements[i][0];
int x = frontier[3] + planner.movements[i][1];
//h_distance = abs(y-planner.goal[0]) + abs(x-planner.goal[1]);
h_distance = map.heuristic[y][x];
int f = h_distance + cost;

if(y>=0 && y<map.mapHeight  && \
    x>=0 && x<map.mapWidth  && \
    map.grid[y][x]==0 ){
    frontiers.push_back({f, cost, y, x});
    map.grid[y][x] = 1;
    action_map[y][x] = i;
}
}
expansion +=  1;
}

//Back propagation from goal to start
int y = planner.goal[0];
int x = planner.goal[1];
while(y != planner.start[0] || x != planner.start[1])
{
int index = action_map[y][x];
y = y - planner.movements[index][0];
x = x - planner.movements[index][1];
path_map[y][x] = planner.movements_arrows[index];
}

if(!findTarget) cout<<"Blocked!";
cout<<"action_map"<<endl;
print2DVector(action_map,true);
cout<<"path_map"<<endl;
print2DVector(path_map,true);
cout<<"vection_map"<<endl;
print2DVector(vector_map,true);

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