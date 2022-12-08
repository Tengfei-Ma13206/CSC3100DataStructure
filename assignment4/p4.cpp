#include<iostream>
#include<vector>
using namespace std;
class Node
{
    public:
        vector<Node*> children;
        int freq;
        char ch;
        Node()
        {
            freq = 0;
        }
        Node(char letter)
        {
            freq = 1;
            ch = letter;
        }

};
class Trie
{
    public:
    Node* root = new Node();
    void insert(string str)
    {
        Node* currentNode = root;
        bool isLetterIn;
        for (char letter : str)
        {
            isLetterIn = false;
            for (Node* ptr : currentNode->children)
            {
                if (ptr->ch == letter)
                {
                    currentNode = ptr;
                    currentNode->freq++;
                    isLetterIn = true;
                    break;
                }
            }
            if (isLetterIn == false)
            {
                Node* newNode = new Node(letter);
                currentNode->children.push_back(newNode);
                currentNode = currentNode->children.back();
            }
            
        }
    }
    void count(string str)
    {
        Node* currentNode = root;
        bool isLetterIn;
        for (char letter : str)
        {
            isLetterIn = false;
            for (Node* ptr : currentNode->children)
            {
                if (ptr->ch == letter)
                {
                    currentNode = ptr;
                    isLetterIn = true;
                    break;
                }
            }
            if (isLetterIn == false)
            {
                cout << 0 << '\n';
                return;
            }
        }
        cout << currentNode->freq << '\n';
    }
    
};
int main()
{
    Trie t;
    int numStrings;
    int numPrefix;
    string s;
    cin >> numStrings;
    for (int i = 0; i < numStrings; i++)
    {
        cin >> s;
        t.insert(s);
    }
    cin >> numPrefix;
    for (int j = 0; j < numPrefix; j++)
    {
        cin >> s;
        t.count(s);
    }
    cout << endl;
}
