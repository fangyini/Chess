
#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <vector>
#include <cstring>
#include "Location.h"
using namespace std;

class Player {
private:
    int id;
    string name;
    Location king_loc;
    bool has_checked;
    
public:
    Player (int id) {
        this->id=id;
        if (id==1) {
            name= "White";
        }
        if (id==2) {
            name = "Black";
        }
        has_checked=false;
    }
    ~Player() {}
    int get_id () {return id;}
    string get_name() {return name;}
    void change_king_loc (Location/**/ loc) {king_loc=loc;}
    void change_king_loc (const char str[2]) {
        Location new_loc(str);
        king_loc = new_loc;
    }
    Location/**/ get_king_loc () {return king_loc;}
    bool get_check_status () {return has_checked;}
    void hasChecked () {has_checked=true;}
    void has_not_checked () {has_checked=false;}
};


#endif /* Player_h */
