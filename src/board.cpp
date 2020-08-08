#include "board.h"
#include "move.h"
#include <iostream>

using namespace moveSpace;

namespace boardSpace
{

// Initisalise the board to a default state
Board::Board()
{
    short int moveCountxTwo = 0; // Number of moves
    ActivePlayer playerToMove = activePlayerWhite; // Player to move
    bool whiteCanCastleQS = true; // White's QS castling rights
    bool whiteCanCastleKS = true; // White's KS castling rights
    bool blackCanCastleQS = true; // Black's QS castling rights
    bool blackCanCastleKS = true; // Black's KS castling rights

    whitePawns = 0xFF00;
    whiteKnights = 0x42; 
    whiteBishops = 0x24;
    whiteRooks = 0x81;
    whiteQueens = 0x10;
    whiteKing = 0x8;
    blackPawns = 0xFF000000000000;
    blackKnights = 0x4200000000000000;
    blackBishops = 0x2400000000000000;
    blackRooks = 0x8100000000000000;
    blackQueens = 0x800000000000000;
    blackKing = 0x1000000000000000;

    whitePieces = whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing;
    blackPieces = blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing;

    squareOccupied = whitePieces | blackPieces;
}

// TODO: Set up a position from startpos or fen
void setBoard(Board* boardPtr, std::istringstream &stream)
{
    // Parse the first argument
    std::string argument;
    stream >> argument;

    // Two cases: startpos or fen
    if (argument == "startpos")
    {
        // Ignore the 'moves' argument
        stream >> argument;

        // Parse and make moves
        std::string moveStr;
        while (stream >> moveStr)
        {
            // -------------
            std::cout << getStartSquare(moveStr) << std::endl << getEndSquare(moveStr) << std::endl;
            // -------------
            
            Move* movePtr = new Move();
            std::list<Move*>* moveList = generateMoves(boardPtr);

            for (std::list<Move*>::iterator it = (*moveList).begin(); it != (*moveList).end(); ++it)
            {
                if (moveToString(*it) == moveStr)
                    movePtr = *it;
            }

            makeMove(boardPtr, movePtr);
        }
    }
    else if (argument == "fen")
    {
        // TODO: setup the board to the position provided

    }
}

} // namespace