/*  Implementation of Kruskal's algorithm
*   Lab 4 - CPS616
*   Ryan Woodworth - 500752821
*   18/03/19
*/
#include <iostream>

using namespace std;

//Alias for edge and respective weight
typedef pair<pair<int, int>, int> Edge;

typedef pair<int, int> Disjoint;
//Creating Graph Struct
/*
 * *IF BEING USED: clean() FUNCTION MUST BE USED WHEN DONE*
 *
 */
struct Graph {
    int inSet(int setI);
    int verts, numEdg;
    Edge *edges;
    Disjoint *sets;

    int n = 0;

    //Constructors
    Graph(){
        this->verts = 4;
        this->numEdg = 5;
        this->edges = new Edge[this->numEdg];
        this->sets = new Disjoint[this->verts];
        for(int i = 0; i < this->verts; i++){
            this->sets[i].first = i;
            this->sets[i].second = i;
        }

        addEdge(0, 1, 5);
        addEdge(0, 2, 3);
        addEdge(0, 3, 2);
        addEdge(1, 3, 7);
        addEdge(2, 3, 2);
    }

    Graph(int verts, int edges) {
        this->verts = verts;
        this->numEdg = edges;
        this->edges = new Edge[edges];
        this->sets = new Disjoint[this->verts];
        for(int i = 0; i < this->verts; i++){
            this->sets[i].second = i;
        }
    }

    //*****Helpers*****//

    //Adds edge to graph, if attempting to add more edges than declared, edges wont be set
    void addEdge(int src, int dest, int w){
        //If more edges than declared on creation
        if(n >= numEdg) {
            cout<<"Can not add edge: {"<<src<<" "<<dest<<"}, too many edges"<<endl;
            return;
        }

        //Add edge and update
        this->edges[n] = {{src, dest}, w};
        n++;
    }

    //Utilizing selection sort to sort graph edges by weight
    void sort(int size, Edge* edge){
        int min;

        for(int i = 0; i < size -1; i++){
            min = i;
            for(int j = i+1; j < size; j++){
                if(edge[j].second < edge[min].second){
                    min = j;
                }
            }
            Edge t = edge[i];
            edge[i]= edge[min];
            edge[min] = t;
        }
    }

    //Cleans up memory of graph
    void clean(){
        delete [] edges;
        edges = NULL;
    }
};

//Function Declarations
void mst(Graph g);
void printGraph(Edge edg);

int main() {
    //Making default test graph
    Graph g = Graph();

    //Running Kruskal's Algorithm
    mst(g);

    //Cleaning memory used by graphs
    g.clean();
}

// Kruskal's Algorithm
void mst(Graph g){
    //Sorting by weight first
    g.sort(g.numEdg, g.edges);

    int treeEdge = 0;
    Edge *tree = new Edge[g.verts];

    //Making trees and checking cycles
    int count = 0;
    while(count < g.numEdg){
        int sourceSet, destinationSet;

        sourceSet = g.inSet(g.edges[count].first.first);
        destinationSet = g.inSet(g.edges[count].first.second);

        if(sourceSet != destinationSet){
            tree[treeEdge++] = g.edges[count];
            g.sets[destinationSet].second = g.sets[sourceSet].second;
        }
        count++;
    }

    for(int i = 0; i < g.verts - 1; i++){
        cout<<"{"<<tree[i].first.first<<" "<<tree[i].first.second<<"} W: "<< tree[i].second<<endl;
    }

}

int Graph::inSet(int setI){
    if(setI == sets[setI].second){
        return setI;
    } else{
        return inSet(sets[setI].second);
    }
}


//Print function for for_each loop
void printGraph(Edge edg){
    cout<<"{"<<edg.first.first<<" "<<edg.first.second<<"} w: "<<edg.second<<endl;
}