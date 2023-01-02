#include<iostream>
#include<cmath>

using namespace std;
bool arr[2187][2187];//2187 = 3^7, true is for "#", false is for " ".

void setArr(int k){
    if (k == 0){
        arr[0][0] = true;
    }
    else{
        setArr(k-1);
        //set first 3^(k-1) rows: copy arr[0,2,...,3^(k-1)-1][1,2,...,3^(k-1)-1] 2 times.
        for (int columnIndex = pow(3, k-1); columnIndex <= (int)(pow(3, k) - 1); columnIndex++){
            for (int rowIndex = 0; rowIndex <= (int)(pow(3, k-1) - 1); rowIndex++){
                arr[rowIndex][columnIndex] = arr[rowIndex][columnIndex - (int)pow(3, k-1)];
            }
        }
        //set first 3^(k-1) columns
        for (int rowIndex = pow(3, k-1); rowIndex <= (int)(pow(3, k) - 1); rowIndex++){
            for (int columnIndex = 0; columnIndex <= (int)(pow(3, k-1) - 1); columnIndex++){
                arr[rowIndex][columnIndex] = arr[rowIndex - (int)pow(3, k-1)][columnIndex];
            }
        }
        //set second 3^(k-1) columns
        for (int rowIndex = (int)(pow(3, k-1)); rowIndex <= (int)(2*pow(3, k-1) - 1); rowIndex++){
            for (int columnIndex = (int)(pow(3, k-1)); columnIndex <= (int)(2*pow(3, k-1) - 1); columnIndex++){
                arr[rowIndex][columnIndex] = false;
            }
        }
        for (int rowIndex = (int)(2*pow(3, k-1)); rowIndex <= (int)(pow(3, k) - 1); rowIndex++){
            for (int columnIndex = (int)(pow(3, k-1)); columnIndex <= (int)(2*pow(3, k-1) - 1); columnIndex++){
                arr[rowIndex][columnIndex] = arr[rowIndex - (int)(2*pow(3, k-1))][columnIndex];
            }
        }
        //set third 3 3^(k-1) columns
        for (int rowIndex = pow(3, k-1); rowIndex <= (int)(pow(3, k) - 1); rowIndex++){
            for (int columnIndex = (int)(2*pow(3, k-1)); columnIndex <= (int)(pow(3, k) - 1); columnIndex++){
                arr[rowIndex][columnIndex] = arr[rowIndex - (int)pow(3, k-1)][columnIndex];
            }
        }
    }
}


int main(){
    string line = "";
    int k;
    cin >> k;
    setArr(k);

    for (int rowIndex = 0; rowIndex < (int)(pow(3, k)); rowIndex++){
        for (int columnIndex = 0; columnIndex <= (int)(pow(3, k)); columnIndex++){
            if (columnIndex == (int)(pow(3, k))){
                line += "\n";
            }
            else{
                if (arr[rowIndex][columnIndex]){
                    line += "#";
                }else{
                    line += " ";
                }
            }
        }
        cout << line;
        line = "";
    }
    cout << endl;
}
