/*  Implementation of Kruskal's algorithm
*   Lab 4 - CPS616
*   Ryan Woodworth - 500752821
*   21/03/19
*/
#include <iostream>

using namespace std;

//Alias for edge and respective weight <<src, dest>, weight>
typedef pair<pair<int, int>, int> Edge;

//Disjoint set structure <node id, subset id>
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

int main() {
    //Making default test graph
    Graph g;

    //Running Kruskal's Algorithm
    mst(g);


    cout<<"----------------------------"<<endl; //Split from given and my own test
    //My Own Graph
    Graph x = Graph(9, 14);
    x.addEdge(0,1,4);
    x.addEdge(0,7,8);
    x.addEdge(1,7,11);
    x.addEdge(1,2,8);
    x.addEdge(7,8,7);
    x.addEdge(6,7,1);
    x.addEdge(2,8,2);
    x.addEdge(6,8,6);
    x.addEdge(2,3,7);
    x.addEdge(2,5,4);
    x.addEdge(5,6,2);
    x.addEdge(3,5,14);
    x.addEdge(3,4,9);
    x.addEdge(4,5,10);
    mst(x);

    //Cleaning memory used by graphs
    g.clean();
    x.clean();
}

// Kruskal's Algorithm
void mst(Graph g){
    //Sorting by weight first
    g.sort(g.numEdg, g.edges);

    //MST and index
    int treeEdge = 0;
    Edge *tree = new Edge[g.verts];

    //Making trees and checking cycles
    int count = 0;
    while(count < g.numEdg){
        int sourceSet, destinationSet;

        //Find if vertex subset has been merged from original subset
        sourceSet = g.inSet(g.edges[count].first.first);
        destinationSet = g.inSet(g.edges[count].first.second);

        //If not in same subset (no cycle)
        if(sourceSet != destinationSet){
            //Add edge to minimum spanning tree
            tree[treeEdge++] = g.edges[count];

            //Merge subsets
            g.sets[destinationSet].second = g.sets[sourceSet].second;
        }
        count++;
    }

    //Print MST
    int totalW = 0;
    cout<<"The edges in the minimum spanning tree are:"<<endl;
    for(int i = 0; i < g.verts - 1; i++){
        cout<<"{"<<tree[i].first.first<<" "<<tree[i].first.second<<"} W: "<< tree[i].second<<endl;
        totalW += tree[i].second;
    }
    cout<<"Total weight of tree is : "<<totalW<<endl;

}

//Determine subset location of vertex
int Graph::inSet(int setI){
    if(setI == sets[setI].second){
        return setI;
    } else{
        return inSet(sets[setI].second);
    }
}
