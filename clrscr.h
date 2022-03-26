#if defined(__linux__) || defined(__APPLE__)
    #define command "clear"
#else
    #define command "cls"
#endif

void clrscr(){
    system(command);
}