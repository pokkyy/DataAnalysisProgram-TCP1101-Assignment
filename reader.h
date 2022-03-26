#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// function prototypes. the majority are passed by reference to save space
// general functions
void errorMsg();
string getName();
string timestamp();

// log functions
void addtoLog(string, char, int, int);
void viewLog();

// loading data functions
void getRowCols(ifstream&, int&, int&);
int **allocateArray(int, int);
void inputData(string, int**, int&);
void loadData(string const&, int**);
void delArray(int**, int);
int**loadFile(string&, int&, int&, int**);

// save as function
void saveAs(string&);

// statistical collector functions
vector<string> storeasString(int **, int &, int &);
void statsCollect_long(vector<string> &, int**, int&, int&);
void statsCollect_short2(vector<string> &, int**, int&, int&);
void statsCollect_short1(vector<string> &, int**, int&, int&);
vector<string> statsCollector(int**, int&, int&, int&);

// report functions
void reportHeader(ofstream&, string);
string reportName(const string&);
int reportStats();
void saveReport(const string&, int**, int&, int&);

// html report functions
void htmlStyle(ofstream&, string&);
void htmlContent(ofstream&, int&, int&, int**);
void htmlFooter(ofstream&);
void htmlReport(const string&, int**, int&, int&);