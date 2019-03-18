/*  Implementation of Kruskal's algorithm
*   Lab 4 - CPS616
*   Ryan Woodworth - 500752821
*   18/03/19
*/
#include <iostream>

using namespace std;

//Alias for edge and respective weight
typedef pair<pair<int, int>, int> vect;


//Function Declarations
void print(vect edg);

/*Creating Graph Struct
 *
 * *IF BEING USED: clean() FUNCTION MUST BE USED WHEN DONE*
 *
 */
struct Graph {
    int verts, numEdg;
    vect *edges;
    int n = 0;

    //Default constructor set to default test values
    Graph(){
        this->verts = 4;
        this->numEdg = 5;
        this->edges = new vect[5];

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
        this->edges = new vect[edges];
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

    //Utilizing selection sort to sort graph edges by weight
    void sort(int size, vect* edge){
        int min;

        for(int i = 0; i < size -1; i++){
            min = i;
            for(int j = i+1; j < size; j++){
                if(edge[j].second < edge[min].second){
                    min = j;
                }
            }
            vect t = edge[i];
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


int main() {
    //Making default test graph
    Graph g = Graph();

    //Sorting graph
    g.sort(g.numEdg, g.edges);

    //Printing graph to show sorted
    for_each(g.edges, g.edges + g.numEdg, print);

    //Cleaning memory used by graphs
    g.clean();
}

//Print function for for_each loop
void print(vect edg){
    cout<<edg.first.first<<" "<<edg.first.second<<endl;
}