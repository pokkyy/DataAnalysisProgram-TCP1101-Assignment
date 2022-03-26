#include "menu.h"
#include "login.h"
#include "clrscr.h"
#include "reader.h"
#include "stats.h"

// compilation guide:
// enter "g++ menu.cpp login.cpp reader.cpp stats.cpp -o main"
// run the program by typing in ""./main"

// global variables that need to exist
int row = 0, col = 0;
string filename;
int **data;

extern struct registered_user user;                // tells compilier this exists in an external source

/*This last function was added because of a bug happening when I wrote the program initially. It is just the message shown
if you use the program and exit (logout message basically) -Zaim, Sabahaddin (The menu developer)*/
void Exit()
{
    cout<<"Thanks for using our program!"<<endl;
    cout<<"- The Developer Team"<<endl;
    delArray(data, row);                        // deletes array upon exit
}

/*Simply the report menu. I don't remember why I used 'U' for the access of normal report. 
-Zaim, Sabahaddin (The menu developer)*/
void ReportMenu()
{
    cout<<"Please type in the following to access the features:"<<endl;
    cout<<"Report: 'U'\nHTML Report: 'H'"<<endl<<endl;
    cout<<"To exit the report menu type in 'E'."<<endl;
    char rep;
    cin>>rep;
    rep = toupper(rep);
    cout<<endl<<endl;
    switch(rep)
    {
        case 'U':{cout<<"Report"<<endl;
                  addtoLog("Saved as report",'s', 0, 0); saveReport(filename, data, row, col); ReportMenu(); break;}
        case 'H':{cout<<"HTML Report"<<endl;
                  addtoLog("Save report as HTML", 'h', 0, 0); htmlReport(filename, data, row, col); ReportMenu(); break;}
        case 'E':{MainMenu(); break;}
        default: ReportMenu(); break;
    }
}

/*In this function, the user can choose the statistical action they want to take. I wanted to use strings 
for this part initially, but switch wouldn't accept it, and it is already pretty space consuming.
 -Zaim, Sabahaddin (The menu developer)*/
void Statchoice ()
{   
   char RoC = 'c';
   int input, compare;
   char c;
   cin>>c;
   c = toupper(c);
   switch(c)
    {
        case 'M':{cout<<"Find Minimum"<<endl;
                 RoC = findRowsOrCols(); input = findNumber(); addtoLog("Find minimum", RoC, input, 0);  int min = findMin(RoC, input, data, col, row);
                 statPrinter("minimum", RoC, input, 0, min); StatsMenu(); break;}
        case 'X':{cout<<"Find Maximum"<<endl;
                 RoC = findRowsOrCols(); input = findNumber(); addtoLog("Find maximum", RoC, input, 0); int max = findMax(RoC, input, data, col, row);
                 statPrinter("maximum", RoC, input, 0, max); StatsMenu(); break;}
        case 'D':{cout<<"Median"<<endl;
                 RoC = findRowsOrCols(); input = findNumber(); addtoLog("Find median", RoC, input, 0); float median = findMedian(RoC, input, data, col, row);
                 statPrinter("median", RoC, input, 0, median); StatsMenu(); break;}
        case 'N':{cout<<"Mean"<<endl;
                 RoC = findRowsOrCols(); input = findNumber(); addtoLog("Find mean", RoC, input, 0); float mean = findMean(RoC, input, data, col, row);
                 statPrinter("mean", RoC, input, 0, mean); StatsMenu(); break;}
        case 'V':{cout<<"Variance"<<endl;
                 RoC = findRowsOrCols(); input = findNumber(); addtoLog("Find variance", RoC, input, 0); float variance = findVariance(RoC, input, data, col, row);
                 statPrinter("variance", RoC, input, 0, variance); StatsMenu(); break;}
        case 'S':{cout<<"Standart Deviation"<<endl;
                 RoC = findRowsOrCols(); input = findNumber(); addtoLog("Find standard deviation", RoC, input, 0); float STD = findSTD(RoC, input, data, col, row);
                 statPrinter("standard deviation", RoC, input, 0, STD); StatsMenu(); break;}
        case 'C':{cout<<"Correlation between any selected 2 columns"<<endl;
                 input = findNumber(); compare = findNumber(); addtoLog("Find correlation", RoC, input, compare); correlationPrinter(input, compare, data, row);
                 StatsMenu(); break;}
        case 'I':{cout<<"Distinct Members"<<endl;
                 input = findNumber(); addtoLog("Find distinct data members", RoC, input, 0); printDistinctDataMember(data, row, input); StatsMenu(); break;}
        case 'H':{cout<<"Plot a Histogram"<<endl;
                 input = findNumber(); vector<string> histo = histogram(data, input, row); printHistogram(histo); addtoLog("Print histogram", RoC, input, 0); StatsMenu(); break;}
        case 'E': MainMenu(); break;
        default: cout<<"You've chosen and invalid choice. Try again"<<endl<<endl; StatsMenu(); break;
    }
}

/*Since Statistical Menu was an important part of it and it is large, I had to split them up with the messages and choices.
This one just displays the messages and leads to the choice part of it. -Zaim, Sabahaddin (The menu developer)*/
void StatsMenu()
{
    
    cout<<endl<<"Please write the following to access the function you want:"<<endl;
    cout<<"Minimum: 'M' \nMaximum: 'X', \nMedian: 'D', \nMean: 'N', \nVariance: 'V',"<<endl;
    cout<<"Standart Deviation: 'S' \nCorrelation: 'C', \nDistinct Members: 'I',"<<endl;
    cout<<"Histogram: 'H'. \n\nType in 'E' to exit the menu."<<endl;
    
    Statchoice();

}

/*The place the user can access the file reader and its functionalities. After doing each function, they return back to this 
ReadFile() function until they exit. -Zaim, Sabahaddin (The menu developer)*/
void ReadFile()
{
    char fchoice;
    cout<<endl<<"Please type in the correct character to access the following commands:"<<endl;
    cout<<"\nLoad Data File: 'D'\nSave As: 'S'\nSave as Report: 'R'";
    cout<<"\nSave Report as HTML: 'H'\nSee the Log: 'L'\nType in 'E' to exit the File Reader Menu.";
    cout<<endl;
    cin>>fchoice;
    fchoice = toupper(fchoice);
    cout<<endl<<endl;
    switch (fchoice)
    {
        case 'D': cout<<"Load Data File: "<<endl;
                  addtoLog("Uploaded a file", 'u', 0, 0); data = loadFile(filename, row, col, data);
                  ReadFile(); break;
        case 'S': cout<<"Save As: "<<endl;
                  addtoLog("Saved file as a new name",'s', 0, 0); saveAs(filename);
                  ReadFile(); break;
        case 'R': cout<<"Save As Report: "<<endl;
                  saveReport(filename, data, row, col);
                  ReadFile(); break;
        case 'H': cout<<"Save Report as HTML "<<endl;
                  addtoLog("Save report as HTML", 'h', 0, 0); htmlReport(filename, data, row, col);
                  ReadFile(); break;    
        case 'L': cout<<"Log "<<endl;
                  viewLog(); ReadFile(); break;
        case 'E': MainMenu(); break;
        default: cout<<"You've chosen an invalid choice"<<endl; ReadFile(); break;
    }

}

/*The Main Menu. In here the user can access the various functions. I made it so that they can access it and
re-access this menu in each function if they exit. The Exit() function was not supposed to be a thing.
The program bugged out when I did everything without it. I had to implement it because of it.
-Zaim, Sabahaddin (The menu developer)*/
void MainMenu()
{
    cout<<endl<<"---------- DATA ANALYSIS PROGRAM ----------"<<endl<<endl;
    cout<<setw(20)<< "Welcome "<< user.username<<endl<<endl;
    cout<<"Main Menu"<<endl<<endl;
    cout<<"Type in the following to access:"<<endl;
    cout<<"User Menu: 'U'\nData File Menu: 'F'\nStats Menu: 'S'\nReport Menu: 'R'"<<endl;
    cout<<"To exit the program, please type in 'E'."<<endl;
    char Menchoice;
    cin>>Menchoice;
    Menchoice = toupper(Menchoice);
    cout<<endl<<endl;
    switch(Menchoice)
    {
        case 'U': user_menu(); break;
        case 'F': cout<<"Data File Reader Menu"<<endl;
                  ReadFile(); break;
        case 'S': cout<<"Stats Menu"<<endl; StatsMenu(); break;
        case 'R': cout<<"Report Menu"<<endl; ReportMenu(); break;
        case 'E': Exit(); break;
        default: cout<<"An invalid menu choice. \nPlease try again."<<endl; MainMenu(); break; 
    }    
}

/*Startup is the function to enter into the login part. You can actually exit before logging in if needed.
That is the reason why I added a startup, in case if anyone accidentally opened up our program and didn't 
wanted to use it. -Zaim, Sabahaddin (The menu developer)*/
void startup(char login)
{
    cin>>login;
    cin.ignore(2, '\n');
    cout << endl;
    if (login == 'L'| login =='l')
     {
        login_menu();
     }
    else
     if(login=='e'| login=='E')
      cout<<"You've exited without using our program."<<endl;
    else
     do
     {
         clrscr();
         cout<<"You must be confused. Please try again for an acceptable command: ";
         cin>>login;
         cin.ignore(2, '\n');
          if (login == 'L'| login =='l')
           {
            login_menu();
           }
          else
          if(login=='e'| login=='E')
            cout<<"You've exited without using our program."<<endl;  
     }while(login!='l'&& login!='L'&& login!='e'&& login!='E');
}

/*The main function. The place before starting up. -Zaim, Sabahaddin (The menu developer)*/
void startMenu()
{
    char Lin;
    cout<<endl<<"This is a statistical program where you can use statistical functions, get reports and even html report.";
    cout<<endl;
    cout<<"To enter the program, please type in 'L' to log in, or 'E' to exit without entering."<<endl;
    startup(Lin);
}

int main()
{
    startMenu();
    return 0;
}