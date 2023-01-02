#include<iostream>
#include<string>
#include<sstream>
using namespace std;

int arr[100000];

long long inversions(int start, int end){
    int mid = (start + end) / 2;
    int sortedArr[end+1];
    int leftIndex = start;
    int rightIndex = mid + 1;
    int sortedArrIndex = 0;
    long long ans = 0;
    if ((end-start+1) <= 1){
        return 0;
    } 
    ans += inversions(start, mid)+inversions(mid + 1, end);
    while (leftIndex <= mid && rightIndex <= end){
        if (arr[leftIndex] >= arr[rightIndex]) sortedArr[sortedArrIndex++] = arr[rightIndex++];
        else{
            sortedArr[sortedArrIndex++] = arr[leftIndex++];
            ans += rightIndex - mid - 1;
        }
    }
    while (leftIndex <= mid){
        sortedArr[sortedArrIndex++] = arr[leftIndex++];
        ans += rightIndex - mid - 1;
    }
    while (rightIndex <= end) sortedArr[sortedArrIndex++] = arr[rightIndex++];
    for (int i = 0, j = start; j <= end; ++i, ++j){
        arr[j] = sortedArr[i];
    }
    return ans;
    }


int main(){
    string firstLine;
    string secondLine;
    int tmp;
    int n;
    int arrIndex = 0;

    getline(cin, firstLine);
    istringstream is_n(firstLine);
    while(is_n>>tmp){
        n = tmp;
    }
    getline(cin, secondLine);
    istringstream is_v(secondLine);
    while(is_v>>tmp){
        arr[arrIndex] = tmp;
        arrIndex++;
    }
    
    cout << inversions(0, n-1) << endl;

    return 0;
}
