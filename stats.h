#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <cctype>
#include <fstream>

using namespace std;

// All the function prototypes
void statPrinter(string, char, int, int, double);
char findRowsOrCols();
int findNumber();
int findMin(char &roworcol, int &number, int **array, int &sizecols, int&);
int findMax(char &roworcol, int &number, int **array, int &sizecols, int&);
float findMean(char &roworcol, int &number, int **array, int &sizecols, int&);
float findMedian(char &roworcol, int &number, int **array, int &sizecols, int&);
float findMedianCols(int **array, int &sizecols, int &number);
float findMedianRows(int **array, int &sizerows, int &number);
float findVariance(char &roworcol, int &number, int **array, int &sizecols, int&);
float findSTD(char &roworcol, int &number, int **array, int&, int&);
void correlationPrinter(int &colA, int &colB, int**data, int rows);
string findCorrelation(float &sumX, float &sumY, float &xy , float &x2, float &y2, int &sizerows);
vector<string> CorrelationTable(int &colA, int &colB, int**data, int rows);
vector<int>distinctdatamember(int**, int&, int&);
void printDistinctDataMember(int **array, int &row, int column);
void printHistogram(vector<string> content);
vector<string>histogram(int**, int&, int&);