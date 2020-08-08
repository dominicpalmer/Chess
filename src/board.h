#ifndef BOARD_H_
#define BOARD_H_

#include "globals.h"
#include <sstream>

namespace boardSpace
{

class Board
{
    public:
        short int moveCountxTwo; // Number of moves
        ActivePlayer playerToMove; // Player to move
        bool whiteCanCastleQS; // White's QS castling rights
        bool whiteCanCastleKS; // White's KS castling rights
        bool blackCanCastleQS; // Black's QS castling rights
        bool blackCanCastleKS; // Black's KS castling rights
        
        // Bitboards
        Bitboard whitePawns;
        Bitboard whiteKnights; 
        Bitboard whiteBishops;
        Bitboard whiteRooks;
        Bitboard whiteQueens;
        Bitboard whiteKing;
        Bitboard blackPawns;
        Bitboard blackKnights;
        Bitboard blackBishops;
        Bitboard blackRooks;
        Bitboard blackQueens;
        Bitboard blackKing;
        
        Bitboard whitePieces;
        Bitboard blackPieces;
        
        Bitboard squareOccupied;

        Board();
};

void setBoard(Board* boardPtr, std::istringstream &stream);

}

#endif