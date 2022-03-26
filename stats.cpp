#include "stats.h"
#include "reader.h"

// function printer
/*  how this works:
        call it after the operation is done just input
            operation (hardcorded so write "minimum"/"median"/etc)
            char for roworcolumn
            first value it calculates on
            second value it calculates on
            the results of the find min/max/etc
*/
void statPrinter(string operation, char RoC, int v1, int v2, double result)
{
    string RoworColumn;

    if (RoC = 'r')
        RoworColumn = "row";
    else
        RoworColumn = "column";
    
    stringstream text;

    text << "The " << operation << " for " << RoworColumn;

    if (v2 != 0)
        text << "s " << v1 << " and " << v2;
    else
        text << " " << v1;
    
    text << " is " << fixed << showpoint << setprecision(2) << result;

    string stat = text.str();

    cout << stat << endl;
}

char findRowsOrCols()   //Asks the user to choose either rows or columns
{   
    char colsorrows;    //Declare new variable

    cout << "Do you want to calculate column or row (all the columns) ?" << endl   //Asks the user input
         << "Please enter 'c' for columns or 'r' for rows" << endl;                 
    cin >> colsorrows;                                                             //Stores the input into the variable
    colsorrows = tolower(colsorrows);

    while (colsorrows != 'c' && colsorrows != 'r')                                     //Making sure the user gives out the right input before  
    {
        cout << "You did not enter 'c' nor 'r'. Please try again." << endl;         //proceeding with the next function
        cin >> colsorrows;
        colsorrows = tolower(colsorrows);
    }

    return colsorrows;
}

int findNumber()    //Asks the use which rows or columns they want to calculate
{   
    int number;     //Declare new variable

    cout << "Please enter the column / row number that you want to calculate."      //Asks the user input
         << endl;
    cin  >> number;                                                                 //Stores the input into the variable

    return number;                                                                  //Returns the input
}


// The statistical funtions uses the same base by using an if else statement for each user input
// that was entered. 


// To find the minimum function. 
int findMin(char &roworcol, int &number, int **array, int &sizecols, int &sizerows) // Declares the function and its parameters
{
    int lowest;

    if ( roworcol == 'c')                                                           // If the user inputs 'c' for columns in the previous function,
    {                                                                               // it will pass by reference and choose this part of the code.
        lowest = array[0][number];                                              // Declares a variable to be the array.

        for (int i=0; i < sizecols; i++)                                            // Will go through the array until the end of it.
                if (lowest > array[i][number])                                      // If it detects a lower number in the array, 
                    lowest = array[i][number];                                      // it will assign it to the variable.
    }

    else 
        if ( roworcol == 'r')                                                       // If the user inputs 'r' for rows in the previous function,
        {                                                                           // it will pass by reference and choose this part of the code.
            lowest = array[number][0];                                          // Declares a variable to be the array.

            for (int i=0; i < sizerows; i++)                                        // Will go through the array until the end of it.
                    if (lowest > array[number][i])                                  // If it detects a lower number in the array, 
                        lowest = array[number][i];                                  // it will assign it to the variable.
        }
    return lowest;                                                                  // Return the value
}

// To find the maximum function. 
int findMax(char &roworcol, int &number, int **array, int &sizecols, int &sizerows) // Declares the function and its parameters
{
    int highest;

    if ( roworcol == 'c')                                                           // If the user inputs 'c' for columns in the previous function,
    {                                                                               // it will pass by reference and choose this part of the code.
        highest = array[0][number];                                             // Declares a variable to be the array.

        for (int i=0; i < sizecols; i++)                                            // Will go through the array until the end of it.
            if (highest < array[i][number])                                         // If it detects a higher number in the array,
                highest = array[i][number];                                         // it will assign it to the variable.
    }

    else 
        if ( roworcol == 'r')                                                       // If the user inputs 'r' for rows in the previous function,
        {                                                                           // it will pass by reference and choose this part of the code.
            highest = array[number][0];                                         // Declares a variable to be the array.

            for (int i=0; i < sizerows; i++)                                        // Will go through the array until the end of it.
                    if (highest < array[number][i])                                 // If it detects a higher number in the array,
                        highest = array[number][i];                                 // it will assign it to the variable.
        }
    return highest;
}

// To find the mean function. 
float findMean(char &roworcol, int &number, int **array, int &sizecols, int &sizerows) // Declares the function and its parameters
{
    float mean;

    if ( roworcol == 'c')                                                           // If the user inputs 'c' for columns in the previous function,
    {                                                                               // it will pass by reference and choose this part of the code.
        float sum = 0;                                                              // Declares a variable to be the array.
        
        for (int i=0; i < sizecols; i++)                                            // Will go through the array until the end of it.
            sum = sum + array[i][number];                                           // Will add every number in the array to find the sum.

        mean = sum / sizecols;                                                      // Find the mean by dividing the sum with the size of the array
    }

    else 
        if ( roworcol == 'r')                                                       // If the user inputs 'r' for rows in the previous function,
        {                                                                           // it will pass by reference and choose this part of the code.
            float sum = 0;                                                          // Declares a variable to be the array.

            for (int i=0; i < sizerows; i++)                                        // Will go through the array until the end of it.
                sum = sum + array[number][i];                                       // Will add every number in the array to find the sum.

        mean = sum / sizerows;                                                      // Find the mean by dividing the sum with the size of the array
        }
    return mean;                                                                    // returns the value
}


// To find the median is the user picks columns
float findMedianCols(int **array, int &sizecols, int &number)
{  
    int i=0, j=0, temp=0;                                                           // Declares the variables
    float median;

        for(i=0 ; i<sizecols ; i++)                                                 // Goes through the array.
        {   
            for(j=0 ; j<sizecols-1 ; j++)                                           
            {   
                if( array[j][number] > array[j+1][number] )                          // Will swap the int if the int is bigger than the previous one
                {
                    temp = array[j][number];                                         // Stores the current it in a temp variable
                    array[j][number] = array[j+1][number];                           // The next value stored in to the one before it.
                    array[j+1][number] = temp;                                       // The new number is stored in temp. 
                }       
            }
        }

        if ( sizecols%2 == 0 )                                                       // Checks if the size of the comlumn is odd
            median = ( array[(sizecols-1)/2][number] + array[sizecols/2][number] )/2.0; // If its odd then it will take the sum of two closest to the 
                                                                                        // middle of the array size and divides it.
        else
            median = array[sizecols/2][number];                                    // If it is even, then it will take the middle of the array size. 
    return median;                                                             // Returns the value
}

// To find the median if the user picks rows
float findMedianRows(int **array, int &sizerows, int &number)
{  
    int i=0, j=0, temp=0;                                                           // Declares the variables
    float median;

     for(i=0 ; i<sizerows ; i++)                                                    // Goes through the array.
            {   
                for(j=0 ; j<sizerows-1 ; j++)                                       
                {   
                    if(array[number][j]>array[number][j+1])                         // Will swap the int if the int is bigger than the previous one
                    {
                        temp = array[number][j];                                    // Stores the current it in a temp variable
                        array[number][j] = array[number][j+1];                      // The next value is put into the one before it.
                        array[number][j+1] = temp;                                  // The new number is stored in temp.
                    }
                }
            }

    if(sizerows%2 == 0)                                                        // Checks if the size of the comlumn is odd
        median = (array[number][(sizerows-1)/2] + array[number][sizerows/2])/2; // If its odd then it will take the sum of two closest to the 
                                                                                        // middle of the array size and divides it.
    else
        median = array[number][sizerows/2];                                    // If it is even, then it will take the middle of the array size
        
    return median;                                                             // Returns the value
}

// To find the median function.
float findMedian(char &roworcol, int &number, int **array, int &sizecols, int &sizerows) // Declares the function and its parameters
{    
    int i=0, j=0, temp=0;                                                           // Declares the variables
    float median;

    if ( roworcol == 'c')                                                           // If the user inputs 'c' for columns in the previous function                                                                      // it will pass by reference and choose this part of the code.
        median = findMedianCols(array, sizerows, number);
    else 
        if ( roworcol == 'r')                                                      // If the user inputs 'r' for rows in the previous function,
            median = findMedianRows(array, sizecols, number);
    return median;
}

//To find the variance
float findVariance(char &roworcol, int &number, int **array, int &sizecols, int &sizerows) // Declares the function and its parameters
{   
    float mean, variance;                                                                         // Declares a variable

    mean = findMean(roworcol, number, array, sizecols, sizerows);                                                                  // Finds the mean and is put into the variable

    if ( roworcol == 'c')                                                               // If the user inputs 'c' for columns in the previous function,
    {                                                                                   // it will pass by reference and choose this part of the code.
        for (int i=0; i < sizecols; i++)                                                // Will go through the array until the end of it.
            variance = variance + pow(array[i][number] - mean,2);                       // Will keep adding each value into the variable.
        
        variance = variance / (sizecols-1);                                            
    }   

    else 
        if ( roworcol == 'r')                                                           // If the user inputs 'r' for rows in the previous function,
        {                                                                               // it will pass by reference and choose this part of the code.
            for (int i=0; i < sizerows; i++)                                            // Will go through the array until the end of it.
                variance = variance + pow(array[number][i] - mean,2);                   // Will keep adding each value into the variable.

            variance = variance / (sizerows-1);                                         
        }
    return variance;                                                                    // Return the value
}


//To find the standard deviation 
float findSTD(char &roworcol, int &number, int **array, int &sizecols, int &sizerows)                       // Declares the function and its parameters
{   
    float variance, STD;                                                                //Declares varibales.

    variance = findVariance(roworcol, number, array, sizecols, sizerows);                                                          // Find the variance first.
    STD=sqrt(variance);                                                                 // Standard deviation is square root of variance.

    return STD;                                                                         // Returns the value

}

void correlationPrinter(int &colA, int &colB, int**data, int rows)
{
    vector<string> cor = CorrelationTable(colA, colB, data, rows);

    for (auto i: cor)
        cout << i;
}
//To find the correlation between two columns
string findCorrelation(float &sumX, float &sumY, float &xy , float &x2, float &y2, int &sizerows)  // Declares the function and its parameters
{   
    vector<string> coro;                                                               // Declares the variables
    stringstream ss;

    double r, numerator, denominator1, denominator2;                                   // Declares variables

    numerator = (sizerows * xy) - (sumX * sumY);                                      // Pearson's Correlation Between 2 Columns Formula using A Table of Values
    denominator1 = sqrt((sizerows *x2) - pow(sumX,2));                                //                       ∑ xi yi - ∑x ∑y                                nummerator
    denominator2 = sqrt((sizerows *y2) - pow(sumY,2));                                //  r      = ---------------------------------------------- = ----------------------------
                                                                                      //    xy       ________________        __________________
    r = numerator / (denominator1 * denominator2);                                    //           \/ n ∑ x^2 - (∑ x)^2  * \/ n ∑ y^2 - (∑ y)^2      denominator1 * denominator2                                                           

    ss << " The correlation function, r, is equal to  " << fixed << showpoint << setprecision(2) << r << endl;          // Will print out the r value

    return ss.str();                                                                  
}

vector<string> CorrelationTable(int &colA, int &colB, int**data, int rows)                         // Declares vector string and its parameters   
{
    vector<string> coro;                                                                // Declares the variables
    float sumX, sumY, sumXY, sumX2, sumY2, xy, x2, y2;
    stringstream ss;

    ss << "-----------------------------------------------------" << endl               // Prints out the header of the correlation 
       << "|" << setw(5) << "x" << setw(5) << "|" << setw(5) << "y" << setw(5)          // table of values
       << "|" << setw(5) << "xy" << setw(5) << "|" << setw(5) << "x^2" << setw(5) 
       << "|" << setw(5) << "y^2" << setw(5) << "|" << endl
       << "-----------------------------------------------------" << endl;
    
    coro.push_back(ss.str());
    ss.str("");

    for (int i = 0; i < rows; i++)                                                      // Will go through the array until the end of it.
    {
        ss << "| " << setw(5) << data[i][colA] << setw(5) << "|" << setw(5)             //Finding all the required calculations for each index
           <<  data[i][colB] << setw(5) << "|";
        sumX += data[i][colA];
        sumY += data[i][colB];

        xy = (data[i][colA] * data[i][colB]);
        ss << setw(5) <<  xy << setw(5) << "|";
        sumXY += xy;

        x2 = pow(data[i][colA], 2);
        ss << setw(5) <<  x2 << setw(5) << "|";
        sumX2 += x2;

        y2 = pow(data[i][colB], 2);
        ss << setw(5) <<  y2 << setw(5) << "|" << endl;
        sumY2 += y2;

        coro.push_back(ss.str());
        ss.str(""); // empties it
    }

    ss << "-----------------------------------------------------" << endl              // Prints out each row as it goes throught the array
         << " |" << setw(5) << sumX << setw(5) << "|" << setw(5) << sumY << setw(5) 
         <<  "|" << setw(5) << sumXY  << setw(5) <<  "|" << setw(5) << sumX2 << setw(5)                     
         << "|" << setw(5) << sumY2 << setw(5) <<  "|" << endl
         << "-----------------------------------------------------" << endl;

    coro.push_back(ss.str());
    string correlation = findCorrelation(sumX, sumY, sumXY, sumX2, sumY2, rows);        // Takes the values calculated to find the actual correlation value , r
    coro.push_back(correlation);

    return coro;
}

vector<int> distinctdatamember (int **array, int &rowsize, int &column)
{    
    vector<int>unique;

    for (int i = 0; i < rowsize; i++) // row loop
    {
        if (count(unique.begin(), unique.end(), array[i][column]) == 1) // if dupes are found
            i++; // skip this
        else
            unique.push_back(array[i][column]); // adds the unqiue item to the vector
    }

    return unique; // returns the vector with distinct data members
}

void printDistinctDataMember(int **array, int &rowsize, int column) 
{
    vector<int>index = distinctdatamember(array, rowsize, column);
    int counter = 0;

    cout << "---------------" << endl;

    for (auto i : index)                // cycles thru every item in the vector
    {
        for (int j = 0; j < rowsize; j++)   // goes through every item in the column
            if (i == array[j][column])  // if a duplicate is found
                counter++;              // add to the counter
    
        cout << "|" << i << "|" << counter << "|" << endl; // prints
    }

    cout << "---------------" << endl;
}

void printHistogram(vector<string> content)
{
    for (auto i : content) // cycles thru every item in the vector
        cout << i; // prints every item in the vector

}

vector<string> histogram (int **array, int &column, int &rowsize)
{   
    vector<int>index = distinctdatamember(array, rowsize, column); // finds the distinct members of the column
    vector<string> content; // declare a vector to store all the data
    int counter = 0;    // will keep track of every occurance of the data memmber
                        // at least one distinct member is guaranteed at the start

    for (auto i: index)     // goes through every unique item
    {
        for (int j = 0; j < rowsize; j++)   // goes through every item in the column
            if (i == array[j][column])  // if a duplicate is found
                counter++;              // add to the counter
        
        stringstream items;
        items << counter << setw(5) << i << " | ";

        for (int h = 0; h < counter; h++)
            items << "=";               // add = for every occurence

        items << endl;

        string histogramItems = items.str();    // converts the string stream into a string

        content.push_back(histogramItems);       // adds the items to the vector
        items.clear();                  // clear the stringstream for the next data
    }
    return content;
}