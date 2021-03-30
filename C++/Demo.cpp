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
        const string dir="assets/";
    
};

Graph ::Graph(string str)
{
    filename = str;
    string file_with_dir= dir+filename;
    ifstream inData(file_with_dir);
    if (inData.fail())
    {
        cout << "\nFilename doesn't exist\n";
        exit(1);
    }
    int x, y;
    char e;
    string s;
    inData >> no_vertex >> no_edges;
    cout<<"\n\n Graph Coloring Using Ant Colony Optimization :"<<endl;
    cout<<"<---------------------------------------------->"<<endl;
    cout<<"File name:"<<filename<<endl;
    cout<<"Vertex:"<<no_vertex<<endl;
    cout<<"Edges:"<<no_edges<<endl;
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
        long int iterations=0;
        string filename1;
        vector<vector<bool>> adjmatrix1;
        vector<int> color;
        int max_degree1, vertex, edges, varcolor;
        ANTCOL(const Graph &g1);
        bool globalcheck();
        void finalcheck();
        int countDistinct();
        void compute();
        void printcolor();
};
ANTCOL::ANTCOL(const Graph &g1)
{
    filename1 = g1.filename;
    max_degree1 = g1.max_degree;
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
bool ANTCOL::globalcheck()
{
    int i, j;
    for (i = 0; i < vertex; i++)
    {
        for (j = 0; j < vertex; j++)
        {
            if ((color[i] == color[j]) && (adjmatrix1[i][j]))
            {
                return 0;
                
            }
        }
    }
    return 1; 
}
void ANTCOL::compute()
{
    int j,k;
    bool result;
    for(j=1;j<vertex;j++)
    {
        varcolor=countDistinct();
        result=globalcheck();
        if(result==1)
        {
            return;
        }
        for(k=0;k<vertex;k++)
        {
            if(j!=k)
            {
                if((color[j]==color[k]) && (adjmatrix1[j][k]))
                {
                    if(color[k]<=max_degree1)
                    {
                        color[k]=color[k]+1;
                    }
                    else{
                        color[k]=color[k]%(max_degree1+1)+1;
                    }
                    j=1;
                    k=0;
                }
                // cout<<"Color: ";
                // for (int i : color) 
                //     cout << i << " "; 
                // cout<<endl;
            }
        }
        iterations++;
    }
}
void ANTCOL::finalcheck()
{   
    int i,j;
    for(i=0;i<vertex;i++)
    {   
        for(j=0;j<vertex;j++)
        {
            if((color[i]==color[j]) && (adjmatrix1[i][j]))
            {
                cout << "Conflict Between Vertex : " << i+1 << " " << j+1 << endl;
            }
        }
    }
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
    return A.size();
}
void ANTCOL::printcolor()
{
    for (int j = 0; j < vertex; j++)
    {
        cout<<color[j]<<"\t";
    }
    cout<<endl;
}
int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        string file = argv[1];
        Graph g(file);
        //g.AdjMatrix();
        ANTCOL a(g);
        a.compute();
        int Chromatic_Number=a.countDistinct();
        cout<<"\nChromatic Number: "<<Chromatic_Number<< " | " <<"iterations: "<<a.iterations<<endl;
        a.printcolor();
        a.finalcheck();
        if(a.globalcheck()==1)
        {
            cout<<endl<<"This graph is properly Colored ";
        }
        else{
            cout<<endl<<"This graph is not properly colored ";
        }

    }
    return 0;
}