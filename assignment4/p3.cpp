#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class MaxSpanningTree
{
    public:
        struct edge
        {
            int vertex;
            int length;

            edge(int v, int len)
            {
                vertex = v;
                length =len;
            }
            bool operator<(const edge &e) const
            {
                return this->length < e.length;
            }
        };

        bool isNoCycleEdge(edge e, vector<int> &availableVertices)
        {
            for (int i = 0; i < availableVertices.size(); i++)
            {
                if (e.vertex == availableVertices[i])
                {
                    return true;
                }
            }
            return false;
        }

        edge findNoCycleMaxEdge(priority_queue<edge> &availableEdges, vector<int> &availableVertices)
        {
            edge NoCycleMaxEdge = availableEdges.top();
            availableEdges.pop();
            while (!isNoCycleEdge(NoCycleMaxEdge, availableVertices))
            {
                NoCycleMaxEdge = availableEdges.top();
                availableEdges.pop();
            }
            return NoCycleMaxEdge;
        }

        void removeVertex(int vertex, vector<int> &availableVertices)
        {
            for (int i = 0; i < availableVertices.size(); i++)
            {
                if (vertex == availableVertices[i])
                {
                    availableVertices[i] = availableVertices[availableVertices.size()-1];
                    availableVertices.pop_back();
                    return;
                }
            }
        }
        void prim(int n, int M, long long a[])
        {
            long long maxAttractions = 0;
            bool productLessThanM = true;//

            long long weightTable[n][n];
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (a[i]*a[j] >=  M) productLessThanM = false;
                    if (i == j) weightTable[i][j] = -1;
                    else weightTable[i][j] = (a[i]%M)*(a[j]%M)%M;
                }
            }

            if (productLessThanM)//
            {
                int maxIndex = 0;

                for (int i = 1; i < n; i++)
                {
                    if (a[maxIndex] < a[i]) maxIndex = i;
                }
                for (int i = 0; i < n; i++)
                {
                    if (i != maxIndex)
                    {
                        maxAttractions += a[maxIndex]*a[i];
                    }
                }
                cout << maxAttractions << endl;
                return;
            }

            vector<int> availableVertices;
            for (int i = 1; i < n; i++) availableVertices.push_back(i);

            priority_queue<edge> availableEdges;
            for (int i = 1; i < n; i++)
            {
                availableEdges.push(edge(i, weightTable[0][i]));
            }
            
            while (!availableVertices.empty())
            {
                edge NoCycleMaxEdge = findNoCycleMaxEdge(availableEdges, availableVertices);
                maxAttractions += NoCycleMaxEdge.length;
                for (int i = 0; i < n; i++)
                {
                    availableEdges.push(edge(i, weightTable[i][NoCycleMaxEdge.vertex]));
                }
                removeVertex(NoCycleMaxEdge.vertex, availableVertices);
            }

            cout << maxAttractions << endl;
        }
};
int main()
{
    MaxSpanningTree t;
    int n;
    int M;
    cin >> n;
    cin >> M;
    long long a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    t.prim(n, M, a);
}
