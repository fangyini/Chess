
#include "ChessPiece.h"
#include <stdlib.h>
bool King::is_valid(Location loc1, Location loc2){
    int diff_r = abs(loc1.get_row()-loc2.get_row());
    int diff_c = abs(loc1.get_colomn()-loc2.get_colomn());
    if ((diff_r==0 && diff_c==1) || (diff_c==0 && diff_r==1) /*|| (diff_r==0 && diff_c==2) || (diff_c==0 && diff_r==2)*/) {
        return true;
    }
    return false;
}

bool Rook::is_valid(Location loc1, Location loc2) {
    int diff_r = abs(loc1.get_row()-loc2.get_row());
    int diff_c = abs(loc1.get_colomn()-loc2.get_colomn());
    if (diff_r==0 || diff_c==0) {
        return true;
    }
    return false;
}

bool Bishop::is_valid(Location loc1, Location loc2) {
    int diff_r = abs(loc1.get_row()-loc2.get_row());
    int diff_c = abs(loc1.get_colomn()-loc2.get_colomn());
    if (diff_c==diff_r) {
        return true;
    }
    return false;
}

bool Queen::is_valid(Location loc1, Location loc2) {
    int diff_r = abs(loc1.get_row()-loc2.get_row());
    int diff_c = abs(loc1.get_colomn()-loc2.get_colomn());
    if (diff_r==0 || diff_c==0 || diff_c==diff_r) {
        return true;
    }
    return false;
}

bool Knight::is_valid(Location loc1, Location loc2) {
    int diff_r = abs(loc1.get_row()-loc2.get_row());
    int diff_c = abs(loc1.get_colomn()-loc2.get_colomn());
    if ((diff_r==2 && diff_c==1) || (diff_c==2 && diff_r==1)) {
        return true;
    }
    return false;
}

bool Pawn::is_valid(Location loc1, Location loc2) {
    int diff_r = abs(loc1.get_row()-loc2.get_row());
    int diff_c = abs(loc1.get_colomn()-loc2.get_colomn());
        if (get_moved_status()) {
            if (diff_c==0 && diff_r==1)
                return true;
        }
        else{
            if (diff_c==0) {
                if (diff_r==1 || diff_r==2)
                    return true;
            }
        }
    return false;
}

