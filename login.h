#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;     

struct registered_user{            // create user structure
    string username;    // declare username variable
    string password;    // declare password variable
    string role;        // declare role variable
    string status;      // declare status variable
};                 // defining structure variable

//function declarations
void login_menu();
void create_user();
void delete_user();
void logout();
void admin_menu();
void user_menu();
void authenticate(string s1, string s2, string s3);
bool validate_password(string p);
void change_password();
void write_to_file();
void write_to_temp_file();