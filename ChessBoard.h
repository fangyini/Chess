#ifndef ChessBoard_h
#define ChessBoard_h

#include <stdio.h>
#include "ChessPiece.h"
#include "Player.h"
#include "Location.h"

class ChessBoard {
private:
    ChessPiece* pieces[8][8];
    Player* players[2];
    Player* current;
    Player* opponent;
    int count;
    
public:
    ChessBoard () {
        players[0] = new Player(1); //White
        players[1] = new Player(2); //Black
        current=nullptr;
        opponent=nullptr;
        resetBoard();
    }
    bool submitMove (const char ini[], const char dest[]);
    void resetBoard ();
    ChessPiece* get_piece (Location loc);
    ChessPiece* get_piece (int i, int j);
    bool has_chess (Location loc1, Location loc2);
    bool is_valid (Location loc1, Location loc2);
    bool pawn_capture (Location loc1, Location loc2);
    bool move_king (Location loc);
    bool can_attack_or_move (Location loc, Player* player);
    bool can_attack_or_move (Location loc, Player* player, vector<Location>& checking_pieces);
    bool check_castling (Location loc1, Location loc2);
    bool interpose_or_capture (Location king, vector<Location> checking_pieces);
    ~ChessBoard() {
        for (int i=0; i<8; i++) {
            for (int j=0; j<8; j++) {
                if (pieces[i][j]!=nullptr) {
                    delete pieces[i][j];
                }
            }
        }
        delete players[2];
    }
};

#endif /* ChessBoard_h */
