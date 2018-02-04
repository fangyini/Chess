
#ifndef ChessPiece_h
#define ChessPiece_h

#include <stdio.h>
#include <vector>
#include "Location.h"
#include "Player.h"

class ChessPiece {
private:
    Player* player;
    
protected:
    bool has_moved;
    
public:
    ChessPiece(int player_id) {player = new Player(player_id); has_moved=false;}
    Player* getPlayer () {return this->player;}
    virtual string get_name () =0;
    virtual bool is_valid (Location loc1, Location loc2) =0;
    virtual bool get_moved_status () =0;
    virtual void change_move_status () =0;
    virtual ~ChessPiece() {
        delete player;
    }
};

class King: public ChessPiece {
public:
    King(int id): ChessPiece(id) {}
    string get_name() override {return "King";}
    bool is_valid(Location loc1, Location loc2) override;
    bool get_moved_status () override {return has_moved;}
    void change_move_status () override {has_moved=true;}
};

class Rook: public ChessPiece {
public:
    Rook(int id): ChessPiece(id) {}
    string get_name() override {return "Rook";}
    bool is_valid(Location loc1, Location loc2) override;
    bool get_moved_status () override {return has_moved;}
    void change_move_status () override {has_moved=true;}
};

class Bishop: public ChessPiece {
public:
    Bishop(int id): ChessPiece(id) {}
    string get_name() override {return "Bishop";}
    bool is_valid(Location loc1, Location loc2) override;
    bool get_moved_status () override {return has_moved;}
    void change_move_status () override {has_moved=true;}
};

class Queen: public ChessPiece {
public:
    Queen(int id): ChessPiece(id) {}
    string get_name() override {return "Queen";}
    bool is_valid(Location loc1, Location loc2) override;
    bool get_moved_status () override {return has_moved;}
    void change_move_status () override {has_moved=true;}
};

class Knight: public ChessPiece {
public:
    Knight(int id): ChessPiece(id) {}
    string get_name() override {return "Knight";}
    bool is_valid(Location loc1, Location loc2) override;
    bool get_moved_status () override {return has_moved;}
    void change_move_status () override {has_moved=true;}
};

class Pawn: public ChessPiece {
public:
    Pawn(int id): ChessPiece(id) {}
    string get_name() override {return "Pawn";}
    bool is_valid(Location loc1, Location loc2) override;
    bool get_moved_status () override {return has_moved;}
    void change_move_status () override {has_moved=true;}
};

#endif /* ChessPiece_h */
