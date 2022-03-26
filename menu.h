#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

/*I added these due to tell that these functions are to be called to other fucntions because of the interwined 
nature of my part of the program. I've added new functions at the top of each other as I wrope my part of the
program. That's why I arranged my part as backwards as in the Exit() function at the top and main() is at the bottom.
This of it as similar to the film called Memento (2000) by Christopher Nolan. It is backwards, starting from the end
towards the start of it.  -Zaim, Sabahaddin (The menu developer)*/
void startMenu();
void startup(char);
char Login();
void AdminMenu();
void AdminChoice();
void MainMenu();
void ReadFile();
void StatsMenu();
void Statchoice();
void ReportMenu();
void ChangePass();
void Exit();