// data file reader function by Anis Hazirah binti Mohamad Sabry - 1211300373

#include "reader.h"
#include "menu.h"
#include "login.h"
#include "stats.h"

extern struct registered_user user;                 // declare struct registered_user user as a variable that exists somewhere else

void errorMsg()                                     // function that prints out error message
{
    cout << "An error has occurred." << endl
         << "Please try again"
         << endl
         << endl;
}

string getName()                                    // function that gets a name input from the user
{
    string name;

    cout << "Please input the file name including the file type (ie .txt/.dat/etc)" << endl;
    cin >> name;

    return name;
}

string timestamp()                                  // functions that collects the current time when called
{
    time_t current_time = time(NULL);               // declaring arg of time()

    string time = ctime(&current_time);             //ctime for current time

    return time;
}

/* ---------------------------------------- LOG FUNCTIONS ----------------------------------------  */
void addtoLog(string function, char letter = 'e', int value1 = 0, int value2 = 0)   // function that records a log of the user's actions
{
    string logname = user.username + "_log.txt";    // opens a log file of the user's name + "_log.txt"
    ofstream logfile;
    logfile.open(logname, ios::app);                // open the log file in "app" mode where new content is added to the end of the file
    string action;                                  // declare a string called action to store the log activities

    action += function;
    
    if (letter == 'c' || letter == 'C')             // determinea if operation was done on a column or row
        action += " was done on column ";
    else if (letter == 'r' || letter == 'R')
        action += " was done on row ";

    if (value1 != 0)                                // adds column/row used
        action += to_string(value1);
    else if (value1 != 0 && value2 != 0)            // if action was performed on two columns (comparision), it will add the second column
        action += to_string(value1) + " and " + to_string(value2);

    if (logfile.is_open())
        logfile << action << endl;                  // adds to the log file
    else
        errorMsg();

    action.clear();
    logfile.close();
}

void viewLog()                                      // function that will display the contents of the log file
{
    string divider = "-------------------------------------------------------------";
    string logname = user.username + "_log.txt";
    ifstream logfile;
    logfile.open(logname);                          // opens the log file

    string logitems;

    if (logfile.is_open())
    {
        cout << "Displaying log for " << user.username << endl << divider << endl << endl;
        while (!logfile.eof())
        {
            getline(logfile, logitems);             // stores a row of the log items in a string
            cout << logitems << endl;               // displays log items
            logitems.clear();                       // clears the string
        }
        cout << divider << endl << endl;
    }
    else
        errorMsg();                                 // if file isn't loaded, an error message will appear

    logfile.close();
}

/* ----------------------------------------  LOAD DATA FUNCTIONS ----------------------------------------  */
void getRowCols(ifstream &input, int &row, int &col) // calculate row and col amount
{
    string line;

    while (input >> line)                           // get row count
        row++;                                      // add to row count
    row--;                                          // ignore header count

    getline(input, line);

    for (int i = 1; i < line.length(); i++)         // starts when the data is presented in the file
        if (line[i] == ',')                         // if a seperator is found
            col++;                                  // add to column count
}

int **allocateArray(int row, int col) // allocating array
{
    int **array;
    array = new int *[row];                         // declare a new int the size of a row

    for (int i = 0; i < row; i++)
        array[i] = new int[col];                    // input columns for every row

    return array;
}

void inputData(string text, int **data, int &r)     // extracting data from the string
{
    string temp;

    int index = text.find(',');                     // find the end point of id
    text = text.substr(index+1, text.length());     // gets rid of id in the string

    int c = 0;                                      // column counter
    text += ',';                                    // adds a marker to end of the string

    for (int i = 0; i < text.length(); i++)         // column loop
    {
        if (text[i] != ',')                         // if it hasn't reached a marker
            temp += text[i];                        // the items will be stored in a temporary string
        else
        {
            data[r][c] = stoi(temp);                // converts string to int
            temp.clear();                           // clear the temp for the next item
            c++;                                    // move to the next column
        }
    }
}

void loadData(string const &filename, int **data)   // inputting data from file into the array
{
    ifstream input;
    input.open(filename);                           // open the file

    string line, dummyLine;                         // declare a string for inputting the rows,
                                                    // and a dummyline to collect the header line

    if (input.is_open())
    {
        int r = 0;
        getline(input, dummyLine);                  // get header row

        while (input >> line)                       // row loop
        {
            inputData(line, data, r);               // goes to inputData function to input the data
            r++;                                    // move to the next row
        }
    }
    else
        errorMsg();

    input.close();                                  // close the input file
}

void delArray(int **array, int row)                 // array deleter function
{
    for (int i = 0; i < row; i++)
        delete[] array[i];
    delete[] array;
}

int **loadFile(string &filename, int &rows, int &columns, int **data) // main function of load data file
{
    delArray(data, rows);                           // will delete any possible existing array beforehand
    int **array;

    ifstream input;                                 // declare input file
    filename = getName();                           // get the name of the file
    input.open(filename);                           // open input file

    if (input.good())                               // check if the file can be laoded
    {
        getRowCols(input, rows, columns);           // get the row and column count

        array = allocateArray(rows, columns);       // allocate the array
        loadData(filename, array);                  // load the data into the array

        cout << "Data was successfully loaded" << endl << endl;     // inform user the file has been loaded
    }
    else
        errorMsg();                                 // print an error message if the file cannot be loaded

    input.close();                                  // close the input file
    return array;                                   // return the array with the data
}

/* ----------------------------------------  SAVE AS FUNCTIONS ----------------------------------------  */
void saveAs (string &inputfile)                     // save the file with another name
{
    ifstream input;
    input.open(inputfile);

    string outputName = getName();                  // get the new name of the file
    ofstream output;
    output.open(outputName);

    string line;

    if (output.is_open())
    {
        while (getline(input, line))
            output << line << endl;                 // add contents from the original file to the new file
        cout << outputName << " has been saved." << endl << endl;
    }
    else
        errorMsg();                                // if an error occurs, print an error message

    input.close();
    output.close();
}

/* ---------------------------------------- CONVERTING STATS TO STRINGS --------------------------------*/
vector<string> storeasString(int **data, int &row, int &current)
{
    vector<string> dataitems;
    vector<int>index = distinctdatamember(data, row, current);
    int counter = 0;
    stringstream ss;

    for (int i = 0; i < index.size() - 1; i++)                // cycles thru every item in the vector
    {
        for (int j = 0; j < row; j++)   // goes through every item in the column
            if (index[i] == data[j][current])  // if a duplicate is found
                counter++;              // add to the counter
    
        ss << index[i] << " [" << counter << "]" << endl;
    }

    dataitems.push_back(ss.str());  // pushes the items into the vector
    ss.str("");                     // clears the string

    return dataitems;
}

void statsCollect_long(vector<string> &output, int **data, int &row, int &col, int &i)        // for longer stats
{
    if (i == 7)                             // correlation
        for (int j = 0; j < col; j++)                   // for some reason i HAD to put it in {} or else it wouldn't function
        {
            for (int k = 0; k < j; k++)
            {
                if (j != k)
                {
                    int current = j+1, currentcompare = k+1;
                    vector<string> correlation = CorrelationTable(j, k, data, row);
                    for (auto q: correlation)
                        output.push_back(q);
                }
            }
        }
    else if (i == 8)                        // distinct
        for (int j = 0; j < col; j++)
        {
            int current = j+1;
            string content = "Distinct members of column " + to_string(current) + " are: \n";
            output.push_back(content);
            vector<string>items = storeasString(data, row, j);
            for (auto p: items)
                output.push_back(p);
        }
    else if (i == 9) // histogram
        for (int j = 0; j < col; j++)
        {
            int current = j+1;
            vector<string> histo = histogram(data, j, row);
            string content = "The histogram of column " + to_string(current) + " is\n";
            output.push_back(content);
            for (auto k: histo)
            {
                output.push_back(k);
            }
        }
}

void statsCollect_short2(vector<string> &output, int **data, int &row, int &col, int &i)    // second function for statistic collecting
{
    char column = 'c';

    if (i == 4)                                         //mean
        for (int j = 0; j < col; j++)
        {
            int current = j+1;
            float mean = findMean(column, j, data, col, row);
            stringstream content;
            content << "Mean for column " << current << " is " << fixed << setprecision(2) << showpoint << mean;
            output.push_back(content.str());
        }         
    else if (i == 5)                                    // variance
        for (int j = 0; j < col; j++)
        {
            int current = j+1;
            float variance = findVariance(column, j, data, col, row);
            stringstream content;
            content << "Variance for column " << current << " is " << fixed << setprecision(2) << showpoint << variance;
            output.push_back(content.str());
        }
    else if (i == 6)                                   // standard deviation
        for (int j = 0; j < col; j++)
        {
            int current = j+1;
            float deviation = findSTD(column, j, data, col, row);
            string content = "Standard deviation for column " + to_string(current) + " is " + to_string(deviation);
            output.push_back(content);
        }
}

void statsCollect_short1(vector<string> &output, int **data, int &row, int &col, int &i)    // first function for statistic collecting
{
    char column = 'c';

    if (i == 1)                                     // min
        for (int j = 0; j < col; j++)
        {
            int current = j+1;
            int min = findMin(column, j, data, col, row);
            string content = "Minimum for column " + to_string(current) + " is " + to_string(min);
            output.push_back(content);
        }
    else if (i == 2)                                // max
        for (int j = 0; j < col; j++)
        {
            int current = j+1;
            int max = findMax(column, j, data, col, row);
            string content = "Maximum for column " + to_string(current) + " is " + to_string(max);
            output.push_back(content);
        }
    else if (i == 3)                                // Median
        for (int j = 0; j < col; j++)
        {
            int current = j+1;
            float median = findMedian(column, j, data, col, row);
            stringstream content;
            content << "Median for column " << current << " is " << fixed << setprecision(2) << showpoint << median;
            output.push_back(content.str());
        }
}

vector<string> statsCollector(int **data, int &row, int &col, int &stat)    // this function will collect statistics (for Save report and HTML report)
{
    vector<string> items;                           // declare a vector of string to store and return every item

    if (stat >= 0 && stat <= 3)
        statsCollect_short1(items, data, row, col, stat);
    else if (stat >= 4 && stat <= 6)
        statsCollect_short2(items, data, row, col, stat);
    else
        statsCollect_long(items, data, row, col, stat);

    return items;
}


/* ----------------------------------------  SAVE REPORT FUNCTIONS ----------------------------------------  */
void reportHeader(ofstream &report, string title)   // prints the report header
{
    string headerTitle = title;
    int index = headerTitle.find('.');
    headerTitle.erase(index, headerTitle.length() - 1);         // delete .txt/.dat/etc

    report << "Statistical report analysis for " << headerTitle << endl << endl;    // title of the report
    report << "Report generated on : " << timestamp() << endl;                      // report creation timestamp
    report << "----------------------------------------------------------------------"
           << endl;                                 // content divider
}

string reportName(const string &filename, int op)  // function that gets the report name
{
    int currentOp = op-1;

    vector<string> Ops = {"minimum", "maximum", "median", "mean", "variance", "standard_deviation",
                           "correlation", "distinct", "histogram"};

    string operation = "_" + Ops[currentOp];      // assings the operation name accordingly

    string newName = filename;
    int index = newName.find('.');

    string fileType = newName.substr(index, newName.length()); // gets the original file type
    newName.erase(index, newName.length()); // removes the file type

    newName += operation + "_Report" + fileType;    // the operation performed, "_Report", and the filetype is added

    return newName;
}

int reportStats()                           // prints out a list of statistics the user can do
{
    int choice = 0;
    cout << "What would you like to save as a report?" << endl << endl;
    cout << "1. Minimum" << endl
         << "2. Maximum" << endl
         << "3. Median" << endl
         << "4. Mean" << endl
         << "5. Variance" << endl
         << "6. Standard deviation" << endl
         << "7. Correlation" << endl
         << "8. Distinct" << endl
         << "9. Histogram" << endl;

    cin >> choice;

    string operation = "Save report for ";              // record this operation in the log
    if (choice == 1) operation += "minimum";
    else if (choice == 2) operation += "maximum";
    else if (choice == 3) operation += "median";
    else if (choice == 4) operation += "mean";
    else if (choice == 5) operation += "variance";
    else if (choice == 6) operation += "standard deviation";
    else if (choice == 7) operation += "correlation";
    else if (choice == 8) operation += "distinct";
    else if (choice == 9) operation += "histogram";
    addtoLog(operation, 's', 0, 0);

    return choice;
}

void saveReport(const string &filename, int **data, int &row, int &col)   // main functionn for save report. it saves reports into a text file
{
    int statOp = reportStats();         // ask what the user wants to a report of

    string reportFile = reportName(filename, statOp);

    ofstream report;
    report.open(reportFile);            // open the report file

    reportHeader(report, filename);     // report header
    vector<string> content = statsCollector(data, row, col, statOp);     // report contents
    for (auto i: content)
        report << i << endl;

    report << "----------------------------------------------------------------------" << endl;
    report << "END OF REPORT" << endl;

    report.close();                     // close the report

    cout << endl << "Report successfully created." << endl << endl;     // informs user about report status
}


/* ----------------------------------------  SAVE AS HTML FUNCTIONS ----------------------------------------  */
void htmlStyle(ofstream &output, string &title)        // adds tyling for the HTML report file
{
    output << "<title>" << title << " report</title>" << endl;
    output << "<style>" << endl;
    output << "body { text-align: center;}" << endl;    // makes sure all the page content is centered
    output << "table, th, td { width 60%;" << endl      // begin style for the table
           << "margin-left: auto; margin-right: auto;" << endl
           << "margin-collapse: collapse;" << endl
           << "border: 2px solid black;" << endl
           << "padding: 10px 30px 10px 30px;}" << endl; // declares the top padding, the right padding, the bottom padding, and the left padding
    output << "th {background-color: #A9A9A9}" << endl;
    output << "#statsTitle {background-color: #DCDCDC;}" << endl;
    output << "</style>";
    output << "<h1>" << title << "</h1>" << endl;
}

void htmlContent(ofstream &output, int &row, int &col, int** data) // function that generates the results the results
{
    vector<string> operationsList = {"Minimum", "Maximum", "Median", "Mean", "Variance", "Standard Deviation", "Pearson's Correlation", "Distinct Data Members", "Histogram"};
    
    output << "<table>" << endl;                      // creates a HTML table
    output << "<tr><th>Operation Perfomed</th>"       // creates the HTML header
           << "<th>Resuts</th></tr>" << endl;

    for (int i = 0; i < operationsList.size(); i++)
    {
        int current = i+1;
        vector<string> items = statsCollector(data, row, col, current);     // will call the stats collector function
        output << "<tr>" << endl;
        output << "<td id =\"statsTitle\">" << operationsList[i] << "</td>" << endl;
        output << "<td>";
        for (auto c: items)
            output << c << "<br>";                  // adds the statistical result with a linebreak at the end
        output << "</td>" << endl;
        output << "</tr>" << endl;
    }

    output << "</table>" << endl;
}

void htmlFooter(ofstream &output)               // HTML foother printing function
{
    output << "<br><br><hr>" << endl;
    output << "<p>This reported was generated on " << timestamp() << " by " << user.username << " using the Data Analysis Program.</p>" << endl;
    output << "<p><i>";
    output << "The Data Analaysis Program (BDAP) is a statistical program where you perform statistical operations and generate reports for them.";
    output << "</p></i>";
}

void htmlReport(const string &filename, int **data, int &row, int &col) // main HTML report function
{
    int index = filename.find('.');                                 // get rid of .txt/.dat/etc
    string webreport = filename.substr(0, index) + "_report.html";  // gets file name
    string htmltitle = filename;
    htmltitle.erase(index, htmltitle.length());                     // generates a title name

    ofstream htmlreport;
    htmlreport.open(webreport);

    htmlreport << "<!DOCTYPE html>" << endl;                    // HTML header items
    htmlreport << "<html><head>" << endl;
    htmlStyle(htmlreport, htmltitle);
    htmlreport << "</head><body>" << endl;

    htmlreport << "<p>This is a report for " << htmltitle       // HTML body items
                << "</p>" << endl;
    htmlContent(htmlreport, row, col, data);                    // adds the statistical data to the body of the HTML
    htmlFooter(htmlreport);                                     // adds the footer for the HTML report
    htmlreport << "</body></html>";

   htmlreport.close();                                              // closes the html file
   cout << "HTML report successfully created" << endl << endl;      // informs the user about report status
}