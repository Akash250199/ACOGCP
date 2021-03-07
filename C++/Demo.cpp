#include<iostream>
#include<vector>
#include<fstream>
#include<numeric>
using namespace std;
class Graph
{
public:
    string filename;
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
    inData>>nvertex>>nedges;
    cout<<"\nFile name:"<<filename<<endl;
    cout<<"Vertex:"<<nvertex<<endl;
    cout<<"Edges:"<<nedges<<endl;
    adjmat.resize(nvertex,vector<bool>(nvertex,0));
    for (int i=0; i<nedges; i++)
    {    
    	inData >>e>> x >> y;
        adjmat[x-1][y-1]=1;  
        adjmat[y-1][x-1]=1;
    }
    int sum,max=0,max_degree;
    for (int i = 0; i < nvertex; i++)
    {
        sum=accumulate(adjmat[i].begin(),adjmat[i].end(),0);
        if(max<sum)
            max=sum;
    }
    max_degree=max;
    cout<<"Max Degree: "<<max_degree<<endl;  
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
