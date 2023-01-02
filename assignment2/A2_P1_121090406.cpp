#include<iostream>
#include<cmath>
using namespace std;
string representation02(int num){
    string result = "";
    int logNum;
    if (num == 0){
        return "0";
    }else{
        if (num <= 7){
            logNum = log2(num+0.0);
            if(logNum == 1){
                result += "2";
            }else{
                result += "2("+to_string(logNum)+")";
            }
            num -= pow(2, logNum);
            while(num > 0){
                logNum = log2(num+0.0);
                if(logNum == 1){
                    result += "+2";
                }else{
                    result += "+2("+to_string(logNum)+")";
                }
                num -= pow(2, logNum);
            }
            return result;
        }else{
            logNum = log2(num+0.0);
            result += "2("+representation02(logNum)+")";
            num -= pow(2, logNum);
            while(num > 0){
                logNum = log2(num+0.0);
                if(logNum == 1){
                    result += "+2";
                }else{
                    result += "+2("+representation02(logNum)+")";
                }
                num -= pow(2, logNum);
            }
            return result;
        }
    }
 
}

int main(){
    int num;
    cin >> num;
    cout << representation02(num) << endl;
}
