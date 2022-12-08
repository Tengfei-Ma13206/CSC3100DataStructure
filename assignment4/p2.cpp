#include<iostream>
#include<algorithm>
using namespace std;
class Median
{
    public:
    int *median;
    int medianSize = 0;
    int *maxHeap;
    int maxCurSize = 0;
    int *minHeap;
    int minCurSize = 0;
    void set(int k, int m)
    {
        median = new int[2*k];
        maxHeap = new int[m];
        minHeap = new int[m];
    }
    void fullMedian(int k)
    {
        int value;
        for (int i = 0; i < 2*k; i++)
        {
            cin >> value;
            median[i] = value;
        }
        sort(median, median+2*k);
        medianSize = 2*k;
    }
    void insert_maxHeap(int value)
    {
        maxHeap[maxCurSize] = value;
        int currentHole = maxCurSize;
        int parent;
        maxCurSize++;
        while (currentHole != 0)
        {
            parent = ((currentHole-1)/2);
            if (maxHeap[parent] < value) maxHeap[currentHole] = maxHeap[parent];
            else break;
            currentHole = parent;
        }
        maxHeap[currentHole] = value;
    }
    void insert_minHeap(int value)
    {
        minHeap[minCurSize] = value;
        int currentHole = minCurSize;
        int parent;
        minCurSize++;
        while(currentHole != 0)
        {
            parent = ((currentHole-1)/2);
            if (minHeap[parent] > value) minHeap[currentHole] = minHeap[parent];
            else break;
            currentHole = parent;
        }
        minHeap[currentHole] = value;
    }
    void delete_maxHeap()
    {
        if (maxCurSize == 0) return;
        int currentHole = 0;
        int child;
        maxHeap[0] = maxHeap[maxCurSize-1];
        maxCurSize--;
        int tmp = maxHeap[0];
        while((2*currentHole+1) <= maxCurSize)
        {
            child = 2*currentHole+1;
            if (child != maxCurSize && maxHeap[child+1] > maxHeap[child]) child++;
            if (maxHeap[child] > tmp) maxHeap[currentHole] = maxHeap[child];
            else break;
            currentHole = child;
        }
        maxHeap[currentHole] = tmp;
    }
    void delete_minHeap()
    {
        if (minCurSize == 0) return;
        int currentHole = 0;
        int child;
        minHeap[0] = minHeap[minCurSize-1];
        minCurSize--;
        int tmp = minHeap[0];
        while ((2*currentHole+1) <= minCurSize)
        {
            child = 2*currentHole+1;
            if (child != minCurSize && minHeap[child+1] < minHeap[child]) child++;
            if (minHeap[child] < tmp) minHeap[currentHole] = minHeap[child];
            else break;
            currentHole = child;
        }
        minHeap[currentHole] = tmp;
    }
    void output(int k)
    {
        for (int i = 0; i < 2*k-1; i++)
        {
            cout << median[i] << " ";
        }
        cout << median[2*k-1] << endl;
    }
    void insert(int w, int k)
    {
        if (medianSize < 2*k)
        {
            for (int i = medianSize-1; i >= 0; i++)
            {
                if (median[i] > w)
                {
                    median[i+1] = median[i];
                }
                else
                {
                    median[i+1] = w;
                    return;
                }
            }
        }
        else
        {

            if (maxCurSize == minCurSize)
            {
                if (w <= median[0]) {
                    insert_maxHeap(w);
                }
                else if (w > median[2*k-1])
                {
                    insert_maxHeap(median[0]);
                    for (int i = 0; i < 2*k-1; i++)
                    {
                        median[i] = median[i+1];
                    }
                    if (minCurSize != 0) 
                    {
                        if (w <= minHeap[0])
                        {
                            median[2*k-1] = w;
                        }
                        else
                        {
                            median[2*k-1] = minHeap[0];
                            delete_minHeap();
                            insert_minHeap(w);
                        }                   
                    }
                    else
                    {
                        median[2*k-1] = w;
                    }
                }
                else
                {
                    insert_maxHeap(median[0]);
                    for (int i = 1; i <= 2*k-1; i++)
                    {
                        if (median[i] >= w)
                        {
                            median[i-1] = w;
                            break;
                        }
                        else
                        {
                            median[i-1] = median[i];
                        }
                    }
                }
            }
            else
            {
                if (w >= median[2*k-1]) insert_minHeap(w);
                else if (w < median[0])
                {
                    insert_minHeap(median[2*k-1]);
                    for (int i = 2*k-1; i > 0; i--)
                    {
                        median[i] = median[i-1];
                    }
                    if (w >= maxHeap[0]) median[0] = w;
                    else
                    {
                        median[0] = maxHeap[0];
                        delete_maxHeap();
                        insert_maxHeap(w);
                    }
                }
                else
                {
                    insert_minHeap(median[2*k-1]);
                    for (int i = 2*k-2; i >= 0; i--)
                    {
                        if (median[i] <= w)
                        {
                            median[i+1] = w;
                            break;
                        }
                        else
                        {
                            median[i+1] = median[i];
                        }
                    }
                }
            }
        }
    }
    void remove(int p, int k)
    {
        if (maxCurSize == minCurSize)
        {
            if (maxCurSize == 0)
            {
                for (int i = p; i < medianSize; i++)
                {
                    median[i-1] = median[i];
                }
                medianSize--;
            }
            else
            {
                for (int i = p; i < 2*k; i++)
                {
                    median[i-1] = median[i];
                }
                median[2*k-1] = minHeap[0];
                delete_minHeap();
            }
        }
        else
        {
            for (int i = p-2; i >= 0; i--)
            {
                median[i+1] = median[i];
            }
            median[0] = maxHeap[0];
            delete_maxHeap();
        }
    }
};

int main()
{
    int k;
    int m;
    int w;
    int p;
    int id;
    Median med;
    cin >> m;
    cin >> k;
    med.set(k, m);
    med.fullMedian(k);
    for (int i = 0; i < m; i++)
    {
        cin >> id;
        if (id == 1)
        {
            cin >> w;
            med.insert(w, k);
        }
        else if (id == 2) med.output(k);
        else 
        {
            cin >> p;
            med.remove(p, k);
        }
    }
}
