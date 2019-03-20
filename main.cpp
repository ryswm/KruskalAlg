/*  Implementation of Kruskal's algorithm
*   Lab 4 - CPS616
*   Ryan Woodworth - 500752821
*   18/03/19
*/
#include <iostream>

using namespace std;

//Alias for edge and respective weight
typedef pair<pair<int, int>, int> Edge;

//Creating Graph Struct
/*
 * *IF BEING USED: clean() FUNCTION MUST BE USED WHEN DONE*
 *
 */
struct Graph {
    int verts, numEdg;
    Edge *edges;
    int n = 0;

    //Default constructor set to default test values
    Graph(){
        this->verts = 4;
        this->numEdg = 5;
        this->edges = new Edge[this->numEdg];

        addEdge(0, 1, 5);
        addEdge(0, 2, 3);
        addEdge(0, 3, 2);
        addEdge(1, 3, 7);
        addEdge(2, 3, 2);
    }

    //Constructor
    Graph(int verts, int edges) {
        this->verts = verts;
        this->numEdg = edges;
        this->edges = new Edge[edges];
    }

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

    //Helpers

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
struct Subset{
    Edge edge;
    Subset *next;
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
    int source, destination;
    int treeV = 0;

    //Sorting by weight first
    g.sort(g.numEdg, g.edges);

    //Make list of trees (initially individual nodes) && Populate with vertices
    Subset* sets = new Subset[g.numEdg];
    for(int i = 0; i < g.numEdg; i++){
        sets[i].edge = g.edges[i];
        //cout<<"Set "<<i+1<<": {"<<sets[i].edge.first.first<<" "<<sets[i].edge.first.second<<"}"<<endl;
    }

    int num = 0;
    int subCount = 0;
    while(treeV < g.verts - 1){
         Subset currEdge;
         currEdge.edge = g.edges[num];
        num++;

        //InProgress
        /*if(currEdge.first.first != currEdge.first.second){
            sets[subCount].next = currEdge
        }*/

    }



}


//Print function for for_each loop
void printGraph(Edge edg){
    cout<<"{"<<edg.first.first<<" "<<edg.first.second<<"} w: "<<edg.second<<endl;
}