
#ifndef ChessSquare_h
#define ChessSquare_h

#include <stdio.h>

#include "ChessPiece.h"

class ChessSquare {
private:
    ChessPiece* piece;
    
    
public:
    ChessSquare () {piece=NULL;}
    ~ChessSquare() {}
    void setPiece (ChessPiece* piece);
    void removePiece ();
    ChessPiece* getPiece ();
    
};

#endif /* ChessSquare_hpp */
