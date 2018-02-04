
#ifndef Location_h
#define Location_h

#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;

enum Direction {UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT};
const string file = "ABCDEFGH";

class Location {
private:
    int colomn;
    int row;
    
public:
    Location () {colomn=-1; row=-1;}
    Location (const char str[2]) {
        colomn = str[0]-'A';
        row = 8- (str[1]-'0');
    }
    Location (int i, int j) {
        colomn = j;
        row = i;
    }
    ~Location() {}
    void print (){
        cout<<file[colomn]<<8-row<<endl;
    }
    int get_colomn () {return colomn;}
    int get_row () {return row;}

    Location& operator= (const Location& loc) {
        colomn=loc.colomn;
        row=loc.row;
        return *this;
    }
    bool operator== (const Location& loc) {
        if (colomn==loc.colomn && row==loc.row)
            return true;
        return false;
    }
    void move (Direction dire) {
        switch (dire) {
            case UP:
                row--;
                break;
            case DOWN:
                row++;
                break;
            case LEFT:
                colomn--;
                break;
            case RIGHT:
                colomn++;
                break;
            case UP_LEFT:
                colomn--;
                row--;
                break;
            case UP_RIGHT:
                row--;
                colomn++;
                break;
            case DOWN_LEFT:
                row++;
                colomn--;
                break;
            case DOWN_RIGHT:
                row++;
                colomn++;
                break;
                
            default:
                break;
        }
    }
    void change_value (int i, int j) {
        row=i;
        colomn=j;
    }
    bool check_valid () {
        if (row<=7 && row>=0 && colomn<=7 && colomn>=0) {
            return true;
        }
        return false;
    }
};



#endif /* Location_h */
