#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include<unordered_set>
using namespace std;
class Graph
{
public:
    string filename;
    vector<vector<bool>> adjmatrix;
    int no_vertex, no_edges,max_degree;
    Graph(string str);
    void AdjMatrix();
};

Graph ::Graph(string str)
{
    filename = str;
    ifstream inData(str);
    if (inData.fail())
    {
        cout << "\nFilename doesn't exist\n";
        exit(1);
    }
    int x, y;
    char e;
    string s;
    inData >> no_vertex >> no_edges;
    cout << "\nFile name:" << filename << endl;
    cout << "Vertex:" << no_vertex << endl;
    cout << "Edges:" << no_edges << endl;
    adjmatrix.resize(no_vertex, vector<bool>(no_vertex, 0));
    for (int i = 0; i < no_edges; i++)
    {
        inData >> e >> x >> y;
        adjmatrix[x - 1][y - 1] = 1;
        adjmatrix[y - 1][x - 1] = 1;
    }
    int sum, max = 0, max_degree;
    for (int i = 0; i < no_vertex; i++)
    {
        sum = accumulate(adjmatrix[i].begin(), adjmatrix[i].end(), 0);
        if (max < sum)
            max = sum;
    }
    max_degree = max;
    cout << "Max Degree: " << max_degree << endl;
}
void Graph::AdjMatrix()
{
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < no_vertex; i++)
    {
        for (int j = 0; j < no_vertex; j++)
        {
            cout << adjmatrix[i][j] << "\t";
        }
        cout << endl;
    }
}
class ANTCOL
{
public:
    string filename1;
    vector<vector<bool>> adjmatrix1;
    vector<int> color;
    int max_degree1, vertex, edges, varcolor;
    ANTCOL(const Graph &g1);
    bool check();
    int countDistinct();
};
ANTCOL::ANTCOL(const Graph &g1)
{
    filename1 = g1.filename;
    max_degree1 = g1.max_degree+1;
    vertex = g1.no_vertex;
    edges = g1.no_edges;
    adjmatrix1.resize(vertex, vector<bool>(vertex));
    color.resize(vertex, 1);
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            adjmatrix1[i][j] = g1.adjmatrix[i][j];
        }
    }
}
bool ANTCOL::check()
{
    int i, j, conflict = 0;
    for (i = 0; i < vertex; i++)
    {
        for (j = 0; j < vertex; j++)
        {
            if ((color[i] == color[j]) && (adjmatrix1[i][j]))
            {
                conflict = 1;
                cout << "Conflict Between Vertex " << i+1 << " " << j+1 << endl;
            }
        }
    }
    if(conflict==1){
        return 0;
    }
    return 1; 
}
int ANTCOL::countDistinct()
{
    unordered_set<int> A;
    for(int i=0;i<vertex;i++)
    {
        if(A.find(color[i])==A.end())
        {
            A.insert(color[i]);
        }
    }
    cout<<A.size();
    return A.size();
}

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        string file = argv[1];
        Graph g(file);
        g.AdjMatrix();
        ANTCOL a(g);
        a.check();
        a.countDistinct();
    }

    return 0;
}
