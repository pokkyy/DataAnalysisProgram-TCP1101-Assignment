//user registration and authentication function by afif (1201303394)
#include "login.h"
#include "menu.h"

registered_user user;

void write_to_temp_file(string password){                // declare write to temp file function with string password parameter
    fstream newfile; ofstream tempfile; string split[4]; // declare fstream variable and declare ofstream variable
                                                         // split [4] is array for data
    int i=0;                                             // declare new variable
    newfile.open("user_data.dat",ios::in);               // open a user_data.dat file for reading and write purpose // ios::in is to open file for reading
    tempfile.open("temp.dat",ios::trunc);                // open the temp.dat file to truncate it in case that already exist
    if (newfile.is_open()){                              // check if file is open
      string data;                                       // declare new variable
      while(getline(newfile, data)){                     // get line newfile variable and data variable 
          stringstream string_stream(data);              // use for breaking words   
          while(string_stream.good()){                   // check whether state of stream is good
              string a;                                  // declare new variable    
              getline( string_stream, a, ',' );          // get line string_stream and a with ","
              split[i]=a;                                // insert value a in array with current loop
              i++;                                       // increment by 1
          }
          for(i=0;i<4;i++){                              // create for loop with less than 4
              if(split[0] == user.username){             // if split key array is 0 and equals to username 
                  data=user.username + "," + password + "," + user.role +","+ split[3]; // we want to search the one we need to change is the password
                  break;                                 // break the loop                              
              }
          }
            tempfile << data << "\n";                    // to write info to tempfile
          i=0;                                           // set i value equal to 0
      }
        tempfile.close();                                // close the temp.dat file
    }
    else{                                                
        cout << "File cannot be found" << endl;          // print out if the data is not found
    }
    newfile.close();                                     // close the user_data.dat file
}

void change_password(){                                  // declare chande password function
    string password;                                     // declare new string variable
    cout << "Change password for user : " << user.username << endl; // print out username
    cout << "Please enter your new password: ";          
    cin >> password; 
    cout << endl;                                        // get password value from user
    while(!validate_password(password)){                 // if function validate_password is not true can enter the loop
        cout << "Password does not meet the criteria, please re-enter: " << endl;
        cin >> password;                                 // get password value from user
    }
    write_to_temp_file(password);                        // write the data to tempfile
    fstream tempfile2;                                   // declare new fstream variable
    tempfile2.open("temp.dat",ios::in);                  // open a temp.dat file for reading and write purpose // ios::in is to open file for reading   
    ofstream datfile;                                    // declare new ofstream variable
    datfile.open("user_data.dat", ios::trunc);           // open the user_data.dat file to truncate it in case that already exist
    string data;                                         // declare new string variable
    while(getline(tempfile2, data)){                     // get line tempfile2 variable and data variable 
        datfile << data << "\n";                         // to write info to datfile
    }
    cout << "Password successfully changed !" << endl;
    datfile.close();                                     // close the user_data.dat file
    tempfile2.close();                                   // close the temp.dat file   
    if(user.role == "admin"){                            // if user role is equal to admin 
        admin_menu();                                    // go to admin menu
    }else{                                               // if role are not equal to admin
        user_menu();                                     // go to user menu
    }
}
    
void logout(){                                          // declare logout function
    startMenu();                                            // go back to menu function
}

void write_to_file(string username){                    // declare write to file function with string username parameters
    fstream newfile;                                    // declare new fstream variable
    ofstream tempfile;                                  // declare new ofstream variable
    int i=0;                                            // declare new int variable with equal 0
    string data, split[4];                              // delcare new string data and split array
    newfile.open("user_data.dat",ios::in);              // open a user_data.dat file for reading and write purpose // ios::in is to open file for reading
    tempfile.open("temp.dat",ios::trunc);               // open the temp.dat file to truncate it in case that already exist (replace)
    if (newfile.is_open()){                             // check if file is open 
      while(getline(newfile, data)){                    // get line newfile variable and data variable 
          stringstream string_stream(data);             // use for breaking words 
          while(string_stream.good()){                  // check whether state of stream is good    
              string a;                                 // declare new string variable
              getline( string_stream, a, ',' );         // get line string_stream and a with ","
              split[i]=a;                               // insert value a in array with current loop
              i++;                                      // increment by 1
          }
          if(username==split[0]){                       // if username is equals to split key array is 0
              cout << "User has been set to deleted status" << endl;
              data = split[0] + "," + split[1] + "," + split[2] +","+ "deleted"; // data is create new value
          }
          tempfile << data << "\n";                     // write new data to tempfile (temp.dat)
          i=0;                                          // set i value equal to 0
      }
        tempfile.close();                               // close the temp.dat file
    }
    else{cout << "File cannot be found" << endl;}
}

void delete_user(){                                     // declare delete_user function
    string username, data;                              // declare new string variable for username and data

    cout << "Enter the username to be deleted: ";
    cin >> username;                                    // get username value from user

    write_to_file(username);                            // called write to file function with username parameter
    fstream tempfile2;                                  // declare new fstream variable
    tempfile2.open("temp.dat",ios::in);                 // open a temp.dat file for reading and write purpose // ios::in is to open file for reading
    ofstream datfile;                                   // declare new ofstream variable
    datfile.open("user_data.dat");                      // open the user_data.dat file to truncate it in case that already exist (replace)

    while(getline(tempfile2, data)){                    // get line newfile variable and data variable 
        datfile << data << "\n";                        // write new data to datfile (user_data.dat)
    }
    datfile.close();                                    // close user_data.dat file
    admin_menu();                                        // go to admin menu
}

bool validate_password(string password){                // declare boolean function with string password parameter
    bool aUpper = false, aDigit = false;                // declare bool value for aUpper and aDigit as false
    for( char c : password )                            // loop for each password character
    {
        if(isdigit(password[0])){                       // to check if the password has digit or not
            return false;                               // return false
        }
        if( std::isupper(c) ) aUpper = true ;           // to check if the password has Upper character
        else if( std::isdigit(c) ) aDigit = true ;      // to check if the password has Digit
    }
    return aUpper && aDigit;                            // return to aUpper and aDigit
}

void insert_user(string username, string password, string role, string status){ //declare insert user function with username, password, role and status parameters
    ofstream newfile;                                   // declare new ofstream variable
    newfile.open("user_data.dat",ios::app);             // open a user_data.dat file for reading and write purpose // ios::in is to open file for reading

    if(newfile.is_open()){                              // check if file is open 
        newfile<<username<<","<<password<<","<<role<<","<<status<<endl; // to insert new data into user_data.dat
        newfile.close();                                // close user_data.dat file
        cout << "Data successfully inserted" << endl;
        admin_menu();                                    // go to admin menu
    }
}

void create_user(){                                     // declare create user function 
    string username, password, role, status;            // declare new string variables
    cout << "Create user" << endl;                      
    cout << "Enter username: ";
    cin >> username;                                    // get username value from user
    cout << "Enter password: password must start with letter, must contain digit and capital letter" << endl;
    cin >> password;                                    // get password value from user
    while(!validate_password(password)){                // if function validate_password is not true can enter the loop
        cout << "Password does not meet the criteria, please re-enter: " << endl;
        cin >> password;                                // get password value from user
    }
    cout << "Enter user type (admin/buyer): ";
    cin >> role;                                        // get role value from user
    while(role != "admin" && role != "buyer"){          // if role is not equal to admin and buyer can enter the loop
        cout << "Invalid role, please re-enter role (admin/user): ";  
        cin >> role;                                    // get role value from user
    }
    cout << "Enter user status (active/deleted): ";
    cin >> status;                                      // get status value from user
    while(status != "active" && status != "deleted"){   // if status is not equal to active and deleted can enter the loop    
        cout << "Invalid status, please re-enter status (active/deleted): "; 
        cin >> status;                                  // get status value from user
    }
    insert_user(username, password, role, status);      // pass value username, password, role and status to insert user function
}

void admin_menu(){                                      // declare admin menu function
    int choice = 0;                                     // declare int choice and set choice = 0 because to prevent choice from getting negative value
    cout << endl << "---------- DATA ANALYSIS PROGRAM ----------" << endl << endl;                                         
    cout << setw(20);                             
    cout << "Welcome " << user.username << endl;        
    cout << "Admin Menu" << endl;
    cout << endl;
    cout << "1.Create user account" << endl;
    cout << "2.Delete user account" << endl;
    cout << "3.Change password" << endl;
    cout << "4.Logout" << endl;
    cout << endl;
    cout << "Enter your choice (1/2/3/4): " << endl;
    cin >> choice;                                      // get choice value from user
    cout << endl;
    while(choice > 4 || choice <= 0){                   // if choice more than 4 or less than equal 0 can enter the loop
        cout << "Invalid choice, please re-enter: ";
        cin >> choice;                                  // get choice value from user
    }
    if(choice == 1){                    
        create_user();                                  // if choice value equals to 1 then go to create user function
    }
    else if (choice == 2){
        delete_user();                                  // if choice value equals to 2 then go to delete user function
    }
    else if (choice == 3){
        change_password();                              // if choice value equals to 3 then go to change password function
    }
    else{
        logout();                                       // else logout
    }
}

void user_menu(){                                       // declare user menu function
    int choice = 0;                                     // declare int choice and set choice = 0 because to prevent choice from getting negative value
    cout << "User Menu" << endl;
    cout << endl;
    cout << "1.Change password" << endl;
    cout << "2.Return to main menu" << endl;
    cout << "3.Logout" << endl;
    cout << endl;
    cout << "Enter your choice (1/2/3): " << endl;
    cin >> choice;                                      // get choice value from user
    while(choice > 3 || choice <= 0){                   // if choice more than 2 or less than equal 0
        cout << "Invalid choice, please re-enter: ";
        cin >> choice;                                  // get choice value from user
    }
    if(choice == 1){                                     
        change_password();                              // if choice is equal to 1 then go to change password function
    }
    else if(choice == 2){
        MainMenu();}                                    // if choice value equals to 2 then go to main menu
    else{
        logout();                                       //  else logout
    }
}

void authenticate(string username, string password, string role){ // declare authenticate function
    fstream newfile; string split[4]; int i=0; bool found = false; string data; // declare new fstream, strings, int and boolean variables
    newfile.open("user_data.dat",ios::in);              // open a user_data.dat file for reading and write purpose // ios::in is to open file for reading
    if (newfile.is_open()){                             // check if file is open 
      while(getline(newfile, data)){                    // get line newfile variable and data variable 
          stringstream string_stream(data);             // use for breaking words 
          while(string_stream.good()){                  // check whether state of stream is good 
              string a;                                 // declare new string variable
              getline( string_stream, a, ',' );         // get line string_stream and a with ","
              split[i]=a;                               // insert value a in array with current loop
              i++;                                      // increment by 1
          }
          for(i=0;i<4;i++){                             // create for loop with less than 4
              if(split[0] == username && split[1] == password && split[2] == role && split[3] == "active"){ // if array split is equals to username, password, role and active
                  newfile.close();                      // close user_data.dat file
                  found = true;                         // set value found to true
                  if(role == "admin"){admin_menu();}    // if role is equal to admin then go to admin menu function
                  else{MainMenu(); }break;              // else go to the main menu function
              }
          }
          i=0;                                          // set i value to 0
      }
        if(!found){                                     // if not found can enter  
            cout << "No user can be found or user is currently not active!" << endl;
            newfile.close();                            // close user_data.dat file
            login_menu();                               // go to menu function
        }
    } else{
        cout << "File cannot be open" << endl;          // else print out "File cannot be open"
    }
}

void login_menu(){                                       // declare menu function
    cout << "Please Login" << endl;
    cout << endl;
    cout << "Enter your username: ";
    cin >> user.username;                               // get user.username value from user    
    cout << "Enter your password: ";
    cin >> user.password;                               // get user.password value from user
    cout << "Enter your role (admin/buyer): ";
    cin >> user.role;                                   // get user.role value from user
    while(user.role != "admin" && user.role != "buyer"){ // if user.role is not equals to admin and buyer can enter the loop
        cout << "Invalid role, please re-enter type (admin/buyer): ";
        cin >> user.role;                               // get user.role value from user
    }
    authenticate(user.username,user.password,user.role);    // pass value user.username, user.password and user.role to authenticate function
}