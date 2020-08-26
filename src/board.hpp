#ifndef BOARD_H_
#define BOARD_H_

#include "globals.hpp"
#include <sstream>

namespace boardSpace
{

class Board
{
    public:
        short turns; // Number of turns
        short fmrCount; // 50 move rule count
        ActivePlayer activePlayer; // Player to move next
        std::string enPassantAvailable; // Track validity of enpassant captures

        // Castling rights
        bool whiteCanCastleQS;
        bool whiteCanCastleKS;
        bool blackCanCastleQS;
        bool blackCanCastleKS;
        
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

        // Default constructor
        Board();
};

void parseFen(Board* boardPtr, std::istringstream& stream);
void setBoard(Board* boardPtr, std::istringstream& stream);

}

#endif