
#include "ChessBoard.h"
#include "Location.h"
#include <iostream>

using namespace std;

bool ChessBoard::check_castling (Location loc1, Location loc2) {
    int diff_r = loc1.get_row()-loc2.get_row();
    int diff_c = loc1.get_colomn()-loc2.get_colomn();
    int i=0, j=0;
    bool is_cas = false;
    if (current->get_name() == "White") {
        i=7;
    }
    if (current->get_name() == "Black") {
        i=0;
    }
    Location king(i,4);
    if (diff_c==2) { //king moves to the left
        j=3;
    }
    if (diff_c==-2) { //king moves to the right
        j=5;
    }
    Location passing(i,j), passing2(i,1);
    if (loc1==king && get_piece(i,0)->get_name()=="Rook" && get_piece(i,7)->get_name()=="Rook" && !current->get_check_status() && diff_r==0 && abs(diff_c)==2){//Make sure 1. either king or rook has moved, 2.current player is not in check
        if (get_piece(passing)==nullptr && get_piece(loc2)==nullptr && !can_attack_or_move(passing, opponent) && !can_attack_or_move(loc2, opponent)) { //Make sure there is no piece between loc1 and loc2
            if (diff_c==2 && get_piece(passing2)==nullptr && !can_attack_or_move(passing2, opponent)) { //long castling
                pieces[i][3]=pieces[i][0];  //only change rook's position
                pieces[i][0]=NULL;
                is_cas=true;
            }
            if (diff_c==-2) { //short castling
                pieces[i][5]=pieces[i][7];
                pieces[i][7]=NULL;
                is_cas=true;
            }
        }
    }
    return is_cas;
}

bool ChessBoard::pawn_capture (Location loc1, Location loc2) {  //Pawn can go diagonally if it can capture a piece in that location
    int diff_r = abs(loc1.get_row()-loc2.get_row());
    int diff_c = abs(loc1.get_colomn()-loc2.get_colomn());
    if (diff_r==1 && diff_c==1 && get_piece(loc2)!=nullptr && get_piece(loc2)->getPlayer()->get_name() == opponent->get_name() ) {   //Check if there is a piece of opponent in the destination
        return true;
    }
    return false;
}

bool ChessBoard::is_valid(Location loc1, Location loc2) {
    
    //Given that there is no piece at loc2, or there is a piece of opponent's at loc2, or both cases
    
    if (get_piece(loc1)->get_name()=="Knight") {  //Knight can jump pieces when moving
        if (get_piece(loc1)->is_valid(loc1, loc2)) {
            return true;
        }
        else
            return false;
    }
    if (get_piece(loc1)->get_name()=="Pawn") {  //Pawn can go diagonally in special cases
        if (pawn_capture(loc1, loc2) || (get_piece(loc1)->is_valid(loc1, loc2) && get_piece(loc2)==nullptr)) {
            return true;
        }
        return false;
    }
    else{
        if (get_piece(loc1)->is_valid(loc1, loc2) && (!has_chess(loc1, loc2))) {  //If this kind of piece can go to the destination legally and there is no chess in the middle way
            return true;
        }
        else
            return false;
    }
    return false;
}

bool ChessBoard::has_chess (Location loc1, Location loc2){  //Check if there is any piece between loc1 and loc2
    int i = loc1.get_row(), j=loc1.get_colomn();
    if (loc1.get_row()<loc2.get_row())
        i++;
    if (loc1.get_row()>loc2.get_row())
        i--;
    if (loc1.get_colomn()<loc2.get_colomn())
        j++;
    if (loc1.get_colomn()>loc2.get_colomn())
        j--;
    
    while (i!=loc2.get_row() || j!=loc2.get_colomn()) {
        if (pieces[i][j]!=nullptr) {
            return true;
        }
        if (loc1.get_row()<loc2.get_row())
            i++;
        if (loc1.get_row()>loc2.get_row())
            i--;
        if (loc1.get_colomn()<loc2.get_colomn())
            j++;
        if (loc1.get_colomn()>loc2.get_colomn())
            j--;
    }
    return false;
}

ChessPiece* ChessBoard::get_piece (Location loc) {  //Get a pointer pointing to the piece at location loc
    return pieces[loc.get_row()][loc.get_colomn()];
}

ChessPiece* ChessBoard::get_piece (int i, int j) {  //Get a pointer pointing to the piece at coordinates (i,j)
    return pieces[i][j];
}

bool ChessBoard::submitMove (const char ini[], const char dest[]) {
    
    Location loc1(ini), loc2(dest);
    
    //Assign the player
    if (count%2==0) {
        current=players[0];  //White first
        opponent=players[1];
    }
    else{
        current=players[1];
        opponent=players[0];
    }
    
    if (ini==dest) {  //Two locations must be different
        return false;
    }
    
    if (!get_piece(loc1)) {
        cout<<"There is no piece at position "<<ini<<"!"<<endl;
        return false;
    }
    
    if ((get_piece(loc1)->getPlayer()->get_name())==(opponent->get_name())) {
        cout<<"It is not "<<get_piece(loc1)->getPlayer()->get_name()<<"’s turn to move!"<<endl;
        return false;
    }
    
    if (get_piece(loc1)->get_name()=="King") {  //Check if King's location has been changed
        //Check castling
        if (!check_castling(loc1, loc2) && !is_valid(loc1, loc2)){
            cout<<current->get_name()<<"'s "<<get_piece(loc1)->get_name()<<" cannot move to "<<dest<<"!"<<endl;
            return false;
        }
        //current->change_king_loc(&loc2);
        current->change_king_loc(loc2);
    }
    else  if(!is_valid(loc1, loc2)) {
        cout<<current->get_name()<<"'s "<<get_piece(loc1)->get_name()<<" cannot move to "<<dest<<"!"<<endl;
        return false;
    }
    
    cout<<current->get_name()<<"'s "<<get_piece(loc1)->get_name()<<" from "<<ini<<" to "<<dest;
    if (get_piece(loc2)!=nullptr) {  //Check if there is any piece at location loc2
        //check if this piece belongs to current player
        if ((get_piece(loc2)->getPlayer()->get_name())==(current->get_name())) {
            cout<<endl<<"You cannot capture your own piece!"<<endl;
            return false;
        }
        cout<<" taking "<<opponent->get_name()<<"'s "<<get_piece(loc2)->get_name();
    }
    
    cout<<endl;
    if (!(get_piece(loc1)->get_moved_status())) {  //Set the move status after this piece moved
        get_piece(loc1)->change_move_status();
    }

    
    pieces[loc2.get_row()][loc2.get_colomn()]=pieces[loc1.get_row()][loc1.get_colomn()];
    pieces[loc1.get_row()][loc1.get_colomn()]=NULL;
    count++;
    
    vector<Location> checking_pieces;
    if (can_attack_or_move((*opponent).get_king_loc(), current, checking_pieces)) {  //Check if current player can attack the king by any piece on the board
        opponent->hasChecked();  //Opponent is in check
        cout<<opponent->get_name()<<" is in ";

        //Check 1. if King is no long under in check after King moves (King can move to another location （empty location or capture the piece at that location) where no piece can attack it
        //2. If some piece can be put between king and attacking piece, or capture the attacking piece
        if (!move_king((*opponent).get_king_loc()) && !interpose_or_capture((*opponent).get_king_loc(), checking_pieces)) {
            cout<<"checkmate"<<endl;
            //Game is over
        }
        else
            cout << "check"<<endl;
    }
    else if (opponent->get_check_status())
        opponent->has_not_checked();
    
    return true;
}

bool ChessBoard::interpose_or_capture (Location king, vector<Location> checking_pieces) {
    int i = king.get_row(), j=king.get_colomn();
    Location loc;
    vector<Location> moving_pieces;
    ChessPiece* temp;

    for (int k=0; k<checking_pieces.size(); k++) {
        while (i!=checking_pieces[k].get_row() || j!=checking_pieces[k].get_colomn()) {
            if (king.get_row()<checking_pieces[k].get_row())
                i++;
            if (king.get_row()>checking_pieces[k].get_row())
                i--;
            if (king.get_colomn()<checking_pieces[k].get_colomn())
                j++;
            if (king.get_colomn()>checking_pieces[k].get_colomn())
                j--;
            loc.change_value(i, j);
            if (can_attack_or_move(loc, opponent, moving_pieces)) {  //Check if opponent can interpose a piece or capture the checking piece, and after this move, king is still not attacked from other piece
                for (int ind=0; ind<moving_pieces.size(); ind++) {
                    temp=pieces[i][j];
                    pieces[i][j]=pieces[moving_pieces[ind].get_row()][moving_pieces[ind].get_colomn()];
                    pieces[moving_pieces[ind].get_row()][moving_pieces[ind].get_colomn()]=NULL;
                    if (!can_attack_or_move(king, current)) {  //After a piece of opponent's is placed between king and a checking piece, other pieces of current player's may checkmate due to the change
                        pieces[moving_pieces[ind].get_row()][moving_pieces[ind].get_colomn()]=pieces[i][j];
                        pieces[i][j]=temp;
                        return true;
                    }
                    else{
                        pieces[moving_pieces[ind].get_row()][moving_pieces[ind].get_colomn()]=pieces[i][j];
                        pieces[i][j]=temp;
                    }
                }
            }
        }
    }
    return false;
}

bool ChessBoard::move_king(Location loc) {
    //move king by one square
    //check if some piece can attack the king on the current location
    Location new_loc;
    for (int i=0; i<8; i++) {
        new_loc=loc;
        new_loc.move(Direction(i));
        //new_loc.print();
        if (new_loc.check_valid()==false) {  //Check if the location is out of the board
            continue;
        }
        if (get_piece(new_loc)==nullptr || get_piece(new_loc)->getPlayer()->get_name() == current->get_name()) {  //Check if King can move to the new location
            if (!can_attack_or_move(new_loc,current)) {
                return true;
            }
        }
    }
    return false;
}

bool ChessBoard::can_attack_or_move (Location loc, Player* player) {
    Location loc2;
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            loc2.change_value(i, j);
            if (get_piece(i, j)!=nullptr && (get_piece(loc2)->getPlayer()->get_name())==(player->get_name()) && is_valid(loc2, loc)) { //Check if there is a piece of opponent's at loc2 that can attack the piece on loc
                    return true;
            }
        }
    }
    return false;
}

bool ChessBoard::can_attack_or_move (Location loc, Player* player, vector<Location>& checking_pieces) {
    Location loc2;
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            loc2.change_value(i, j);
            if (get_piece(i, j)!=nullptr && (get_piece(loc2)->getPlayer()->get_name())==(player->get_name()) && is_valid(loc2, loc)) { //Check if there is a piece of opponent's at loc2 that can attack the piece on loc
                checking_pieces.push_back(loc2);
                return true;
            }
        }
    }
    return false;
}

void ChessBoard::resetBoard () {
    count = 0;
    //Delete all the pointers pointing to a piece on the board
    int j=0, i=0;
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            pieces[i][j] = nullptr;
        }
    }
    
    //Set initial board
    //Black side
    pieces[0][0] = new Rook(2);
    pieces[0][1] = new Knight(2);
    pieces[0][2] = new Bishop(2);
    pieces[0][3] = new Queen(2);
    pieces[0][4] = new King(2);
    pieces[0][5] = new Bishop(2);
    pieces[0][6] = new Knight(2);
    pieces[0][7] = new Rook(2);
    players[1]->change_king_loc("E8");
    
    //White side
    pieces[7][0] = new Rook(1);
    pieces[7][1] = new Knight(1);
    pieces[7][2] = new Bishop(1);
    pieces[7][3] = new Queen(1);
    pieces[7][4] = new King(1);
    pieces[7][5] = new Bishop(1);
    pieces[7][6] = new Knight(1);
    pieces[7][7] = new Rook(1);
    players[0]->change_king_loc("E1");
    
    for (i=0; i<8; i++) {
        pieces[1][i] = new Pawn(2);  //Black pawn
        pieces[6][i] = new Pawn(1);  //White pawn
    }

    cout<<"A new chess game is started!"<<endl;
}
