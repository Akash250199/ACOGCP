#include<iostream>
#include<vector>
#include<fstream>

using namespace std;
class Graph
{
public:
    string filename;
    // vector<vector <int>> edges;
    vector<vector <bool>> adjmat;
    int nvertex,nedges;
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
    int x,y;
    char e;
    string s;
    // while (getline(inData , s))
    //     cout << s <<'\n';
    while(s != "edge")
            inData >> s >> nvertex >> nedges;
    cout<<"\nFile name:"<<filename<<endl;
    cout<<"Vertex:"<<nvertex<<endl;
    cout<<"Edges:"<<nedges<<endl;
    /adjmat.resize(nvertex,vector<bool>(nvertex,0));
    // edges.resize(nedges,vector<int>(2));
    for (int i=0; i<nedges; i++)
    {   
        
    	inData >>e>> x >> y;
        // edges[i][0]=x;
        // edges[i][1]=y;
        adjmat[x-1][y-1]=1;  //for indexing of matrix like at adjmat[0][1]=1 and vice versa for first input edge of input files test.txt i.e (e 1 2)
        adjmat[y-1][x-1]=1;
    }
}
void Graph::AdjMatrix()
{
    cout<<"Adjacency Matrix:"<<endl;
    for (int i = 0; i < nvertex+1; i++)
    {
        for (int j = 0; j < nvertex+1; j++)
        {
            if(i==0)
			{
				if(i==0 && j==0)
					cout<<" \t";
				else
					cout<<j<<"\t";
			}
			else
			{
				if(j==0)
					cout<<i<<"\t";
				else
                    cout<<adjmat[i-1][j-1]<<"\t";
             }
        }
		cout<<endl;      
    }
    
    
}

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        string file = argv[1];
        Graph g(file);
        g.AdjMatrix();
    }

    return 0;
}
