#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

static int checkPointCounter = 0;
// function to show dummy data in raw format
void showData(string rawData[], int rawSize);
void showMatrix(double matrix[4][50], int decimals, int MatrixLength);
string EffectsEncoding(int index, int N);
string DummyEncoding(int index, int N);
int LengthOfArray(int arr);
string toString(int n);
void EncodeFile(string originalFile, string encodedFile, int column, string encodingType);
int getStartPos(string str, int column, int coutingFrom);
int getEndPos(string str, int startPos);
void checkPoint();

int main()
{
    string sourceData[] = {"Sex     Age      Locale      Income      Politics",
                            "=================================================",
                            "Male    25      Rural       63,000.00   Conservative",
                            "Female  36      Suburban    55,000.00   Liberal",
                            "Male    40      Urban       74,000.00   Moderate",
                            "Female  23      Rural       28,000.00   Liberal" };
    string encodedData[] = {"-1      25      1 0         63,000.00   1 0 0",
                            " 1      36      0 1         55,000.00   0 1 0",
                            "-1      40      -1 -1       74,000.00   0 0 1",
                            " 1      23      1 0         28,000.00   0 1 0" };

    // show dummy data in raw format
    cout << "Dummy data in raw form: \n" << endl;
    showData(sourceData, 6);

    // show dummy encoded data in raw format
    cout << "\nData after categorical encoding: \n" << endl;
    showData(encodedData, 4);


    // Numeric data
    cout << "\nNumeric data stored in matrix: \n";
    double numericData[4][50];
    numericData[0] = { -1, 25.0, 1, 0, 63000.00, 1, 0, 0 };
    numericData[1] = { 1, 36.0, 0, 1, 55000.00, 0, 1, 0 };
    numericData[2] = { -1, 40.0, - 1,  -1, 74000.00, 0, 0, 1 };
    numericData[3] = { 1, 23.0, 1, 0, 28000.00, 0, 1, 0 };

    showMatrix(numericData, 2, 4);

    cout << endl << "Dummy Encoding of (1,3)  " << DummyEncoding(1,3); // 1-OF-N method
    cout << endl << "Effect Encoding of (0,3) " << EffectsEncoding(2,3); // 1-OF-(N-1) method. 2:current index value[from 0 to 2], 3:total of 3 values

    EncodeFile("Politics.txt", "encodedFile.txt", 2, "effect");


    getch();
    return 0;
}

void showData(string rawData[], int rawSize){
    for(int i=0; i<rawSize; i++){
        cout << rawData[i] << endl;
    }
}

void showMatrix(double matrix[4][50], int decimals, int MatrixLength){
    for(int i=0; i<MatrixLength; i++){
        //for(int j=0; j < ( sizeof(matrix[i]) / sizeof(matrix[0][0])); j++ ){
        for(int j=0; j<8; j++ ){
            double v = matrix[i][j];
            cout << fixed << setprecision(2) << v << "\t";
        }
        cout << endl;
    }
}

string EffectsEncoding(int index, int N){ // N = possible value, index = column value(for N=3, index = 3 column)
    if (N == 2){
        if(index == 0){
            return "-1";
        }
        else if(index == 1){
            return "1";
        }
    }

    int values[N-1];
    // in c++ garbage value gives a headache,
    // so im shooting every array index with 0
    for(int zz=0; zz<N-1; zz++)
        values[zz] = 0;

    if (index == N-1){ // Last item is all -1s.
        for (int i = 0; i < N-1; ++i) // N-1 == sizeof(values)/sizeof(int)
        values[i] = -1;
    }
    else{
        values[index] = 1; // 0 values are already there.
    }

    string s;
    if(values[0] == 0)
        s = "0";
    else
        s = toString(values[0]);

    for (int i = 1; i < N-1; ++i){
        //s += "," + values[i]; c# style code and above two line are c++ equivalent
        if(values[i] == 0)
            s += ",0";
        else
            s += "," + toString(values[i]);
    }
    return s;
}

string DummyEncoding(int index, int N) // N = possible value, index = column value(for N=3, index = 3 column)
{
    int values[N]; // in c++ garbage value gives a headache, so im shooting every array index with 0
    for(int zz=0; zz<N; zz++)
        values[zz] = 0;

    values[index] = 1;

    string s;
    if(values[0] == 0)
        s = "0";
    else
        s = toString(values[0]);

    for (int i = 1; i < N; ++i){
        if(values[i] == 0)
            s += ",0";
        else
            s += "," + toString(values[i]);
    }
    return s;
}

int LengthOfArray(int arr) {
    return arr/sizeof(int);
}

string toString(int n) {
    int arrOfN[20], r, counter = 0;
    string s = "";

    //cout << "The number is " << n << endl;

    // If n value is -ve
    if(n<0) {
        // make n positve for easy computation
        n = n*(-1);
        while(n > 0){
            r = n%10;
            arrOfN[counter] = r;
            counter++;
            n = n/10;
        }

        for(int i=--counter; i>=0; i--){
            //cout << "\nThe number is " << arrOfN[i];
            switch(arrOfN[i]){
                case 0:
                    s += "-0";
                    break;
                case 1:
                    s += "-1";
                    break;
                case 2:
                    s += "-2";
                    break;
                case 3:
                    s += "-3";
                    break;
                case 4:
                    s += "-4";
                    break;
                case 5:
                    s += "-5";
                    break;
                case 6:
                    s += "-6";
                    break;
                case 7:
                    s += "-7";
                    break;
                case 8:
                    s += "-8";
                    break;
                case 9:
                    s += "-9";
                    break;
                default:
                    break;
            }
        }

    // if n value is +ve
    } else {
        while(n > 0){
            r = n%10;
            arrOfN[counter] = r;
            counter++;
            n = n/10;
        }

        for(int i=--counter; i>=0; i--){
            //cout << "\nThe number is " << arrOfN[i];
            switch(arrOfN[i]){
                case 0:
                    s += "0";
                    break;
                case 1:
                    s += "1";
                    break;
                case 2:
                    s += "2";
                    break;
                case 3:
                    s += "3";
                    break;
                case 4:
                    s += "4";
                    break;
                case 5:
                    s += "5";
                    break;
                case 6:
                    s += "6";
                    break;
                case 7:
                    s += "7";
                    break;
                case 8:
                    s += "8";
                    break;
                case 9:
                    s += "9";
                    break;
                default:
                    break;
            }
        }
    }



    return s;
}

void EncodeFile(string originalFile, string encodedFile, int column, string encodingType)
{
    // encodingType: "effects" or "dummy"
    ifstream inFile(originalFile.c_str());
    ofstream outFile(encodedFile.c_str());

    string inputDataStr = "";
    string tempStr = "";
    string outputDataStr = "";

    // put all the data in a string variable
    while(inFile >> tempStr){
        //cout << inputDataStr;
        inputDataStr += tempStr += "\n";
    }

    // delete this line later
    cout << endl << endl << inputDataStr << endl << endl;

    outputDataStr = inputDataStr;

    vector <string> tokens; // make an array of non numeric string as tokens of given column
    int startPos, endPos;
    int i, N, index; // N is the total number of value
    for(i=0; i<inputDataStr.length(); ){
        startPos = getStartPos(inputDataStr, column, i);
        endPos = getEndPos(inputDataStr, startPos);

        string currentToken;
        for(int j=startPos; j<endPos; j++){
            currentToken += inputDataStr.at(j);
        }

        if(tokens.empty()){
            tokens.push_back(currentToken);
        }
        else{
            int flag = 0; // 0 means no duplicate
            for(int m=0; m<tokens.size(); m++){
                if(currentToken == tokens[m])
                    flag = 1; // found duplicate
            }
            if(flag == 0){
                tokens.push_back(currentToken);
            }
        }

        // jump to next line
        int n;
        for(n=i; inputDataStr.at(n) != '\n'; n++);
        i = ++n; // i have to increament it because currently n at newline
    }


    // this for loop is for testing purpose, delete when testing is done
    for(int m=0; m<tokens.size(); m++){
        cout << endl << tokens[m];
    }


    N = tokens.size();

    for(i=0; i<inputDataStr.length(); ){
        startPos = getStartPos(inputDataStr, column, i);
        endPos = getEndPos(inputDataStr, startPos);

        string currentToken;
        for(int j=startPos; j<endPos; j++){
            currentToken += inputDataStr.at(j);
        }

        // get the index value for the current token
        for(int m=0; m<tokens.size(); m++){
            if(currentToken == tokens[m]){
                index = m;
            }
        }

        cout << endl << startPos << " " << endPos << endl;

        // check whether effect or dummy encoding then perform oeration
        if(encodingType == "effect"){
            string effectEncodingStr = EffectsEncoding(index, N);
            cout << endl << effectEncodingStr << endl; // delete
            inputDataStr.replace(startPos, endPos - startPos, effectEncodingStr);
            cout << endl << endl << inputDataStr << endl << endl; // delete
        }
        else if(encodingType == "dummy"){
            string dummyEncodingStr = DummyEncoding(index, N);
            cout << endl << dummyEncodingStr << endl; // delete
            inputDataStr.replace(startPos, endPos - startPos, dummyEncodingStr);
            cout << endl << endl << inputDataStr << endl << endl; // delete
        }
        else
            cout << endl << "### wrong encoding type ###" << endl;

        // jump to next line
        int n;
        for(n=i; inputDataStr.at(n) != '\n'; n++);
        i = ++n; // i have to increament it because currently n at newline
    }

    cout << inputDataStr << endl;
    outFile << inputDataStr;
}

int getStartPos(string str, int column, int coutingFrom){
    int startPos;
    for(int i=coutingFrom; i<str.length(); i++){
        if(column == 0){
            startPos = i;
            break;
        }
        if(str.at(i) == ',')
            column--;
    }
    return startPos;
}
int getEndPos(string str, int startPos){
    int endPos;
    for(int i=startPos; i<str.length(); i++){
        if(str.at(i) == ','){
            endPos = i;
            break;
        }
    }
}

void checkPoint(){
    cout << endl << endl << "### " << checkPointCounter << " ###" << endl << endl;
    checkPointCounter += 1;
}
















/*  // Array size using function
    int a[] = {1,5,6,7,2,8};
    cout << endl << "size = " << intArrSize(sizeof(a));
*/

/*
// writing file
    int id;
    string name;
    ofstream sourceDataFromFile("source.txt");
    while(cin >> id >> name){
        sourceDataFromFile << id << ' ' << name << endl;
    }
*/

/*
// reading
    int id;
    string name;
    ifstream sourceDataFromFile("source.txt");
    while(sourceDataFromFile >> id >> name){
        cout << id << ", " << name << endl;
    }
*/
