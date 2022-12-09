#include <iostream>
#include <vector>
#include<list>
#include<queue>
#include<utility>
using namespace std;
typedef pair<long long, double> ver;// energyCost vertex

class Graph
{
    public:
        const long long INF = 2000000000;
        long long totalVertexNumber;
        long long originalVertexNumber;
        list<pair<long long, double> > *vertexList;
        
        Graph(long long vertexNumber, long long edgeNumber)
        {
            originalVertexNumber = vertexNumber;
            totalVertexNumber = vertexNumber + 2*edgeNumber;
            vertexList = new list<ver> [totalVertexNumber];
        }

        void buildEdge(long long u, long long v,double length)
        {
            vertexList[u].push_back(make_pair(v, length));
        }

        void createEdge(long long u, long long v, long long length, long long k, long long i)
        {
            double halfLength = length / 2.0;
            
            vertexList[u].push_back(make_pair(i + originalVertexNumber, halfLength));
            vertexList[i+originalVertexNumber].push_back(make_pair(v, halfLength));
            vertexList[v].push_back(make_pair(totalVertexNumber-1-i, halfLength));
            vertexList[totalVertexNumber-1-i].push_back(make_pair(u, halfLength));
            list<pair<long long, double> >::iterator j;
            for (j = vertexList[v].begin(); j != vertexList[v].end(); ++j)
            {
                if (i+originalVertexNumber != j->first && j->second == k*halfLength)
                {
                    this->buildEdge(i+originalVertexNumber, j->first, (k-1)*halfLength);
                }
                if (totalVertexNumber - 1 - j->first + originalVertexNumber != totalVertexNumber - 1 - i && k*j->second == halfLength)
                {
                    this->buildEdge(totalVertexNumber - 1 - j->first + originalVertexNumber, totalVertexNumber - 1 - i, (k - 1)*j->second);
                }

            }
            for (j = vertexList[u].begin(); j != vertexList[u].end(); ++j)
            {
                if (totalVertexNumber - 1 - i != j->first && j->second == k*halfLength)
                {
                    this->buildEdge(totalVertexNumber - 1 - i, j->first, (k-1)*halfLength);
                }
                if (totalVertexNumber - 1 - j->first + originalVertexNumber != originalVertexNumber + i && k*j->second == halfLength)
                {
                    this->buildEdge(totalVertexNumber - 1 - j->first + originalVertexNumber, originalVertexNumber + i, (k-1)*j->second);
                }
            }
        }

        void dijkstra()
        {
            priority_queue<ver, vector<ver>, greater<ver> > vertexHeap;
            vector<double> energy(totalVertexNumber, INF);
            vertexHeap.push(make_pair(0, 0));
            energy[0] = 0;
            while (!vertexHeap.empty())
            {
                long long minVertex = vertexHeap.top().second;
                vertexHeap.pop();
                list<pair<long long, double> >::iterator i;
                for (i = vertexList[minVertex].begin(); i != vertexList[minVertex].end(); ++i)
                {
                    long long adjV = i->first;
                    double weight = i->second;
                    if (energy[adjV] > energy[minVertex]+weight)
                    {
                        energy[adjV] = energy[minVertex] + weight;
                        vertexHeap.push(make_pair(energy[adjV], adjV));
                        
                    }
                }
            }
            for (long long i = 0; i < originalVertexNumber; i++)
            {
                if (energy[i] != INF) cout << energy[i] << " ";
                else cout << -1 << " ";
            }
            cout << endl;
        }
};

int main()
{
    long long n, m, k;
    cin >> n >> m >> k;
    Graph graph(n, m);
    for (long long i_th_edge = 0; i_th_edge < m; i_th_edge++)
    {
        long long u, v, w;
        cin >> u >> v >> w;
        graph.createEdge(u-1, v-1, w, k, i_th_edge);
    }
    graph.dijkstra();
}
