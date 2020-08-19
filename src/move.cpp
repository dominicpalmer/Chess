#include "board.h"
#include <iostream>
#include <list>
#include <intrin.h>

using namespace boardSpace;

namespace moveSpace
{

// TODO: Append all legal pawn moves to moveList
void generatePawnMoves(Board* boardPtr, std::list<Move*>* moveListPtr)
{   
    // White to move
    if ((*boardPtr).activePlayer == activePlayerWhite)
    {   
        Bitboard pseudoEligibleSquares = ~((*boardPtr).whitePawns | (*boardPtr).whiteKnights | 
                                     (*boardPtr).whiteBishops | (*boardPtr).whiteRooks | 
                                     (*boardPtr).whiteQueens | (*boardPtr).whiteKing | 
                                     (*boardPtr).blackKing);

        Bitboard caputrablePieces = (*boardPtr).blackPawns | (*boardPtr).blackKnights | 
                                     (*boardPtr).blackBishops | (*boardPtr).blackRooks | 
                                     (*boardPtr).blackQueens;

        // Loop through all the white pawns and append their valid moves
        Bitboard pawnsRemaining = (*boardPtr).whitePawns;
        while (pawnsRemaining)
        {
            // Bitscan the white pawns bitboard for the LSB
            unsigned long index;
            _BitScanForward64(&index, pawnsRemaining);
            Bitboard startSquare = (Bitboard)1 << index;

            // Check for captures (including enpassant)
            Bitboard endSquareNE = (startSquare << northEast) & caputrablePieces;
            if (endSquareNE)
            {
                Move* movePtr = new Move();
                (*movePtr).startSquare = startSquare;
                (*movePtr).endSquare = endSquareNE;
                (*movePtr).pieceColour = pieceColourWhite;
                (*movePtr).pieceType = pieceTypePawn;
                (*movePtr).moveType = capture;
                (*movePtr).promotedTo = pieceTypeNone;                
                (*moveListPtr).push_back(movePtr);
            }

            Bitboard endSquareNW = (startSquare << northWest) & caputrablePieces;
            if (endSquareNW)
            {
                Move* movePtr = new Move();
                (*movePtr).startSquare = startSquare;
                (*movePtr).endSquare = endSquareNW;
                (*movePtr).pieceColour = pieceColourWhite;
                (*movePtr).pieceType = pieceTypePawn;
                (*movePtr).moveType = capture;
                (*movePtr).promotedTo = pieceTypeNone;                
                (*moveListPtr).push_back(movePtr);
            }

            // Check for single pawn pushes

            // Check for double pawn pushes

            
            

            pawnsRemaining ^= startSquare;

        }
    }

    // Black to move
    else
    {

    }
}

// TODO: Append all legal knight moves to moveList
void generateKnightMoves(Board* boardPtr, std::list<Move*>* moveListPtr)
{
    //do stuff

}

// TODO: Append all legal bishop moves to moveList
void generateBishopMoves(Board* boardPtr, std::list<Move*>* moveListPtr)
{
    //do stuff

}

// TODO: Append all legal rook moves to moveList
void generateRookMoves(Board* boardPtr, std::list<Move*>* moveListPtr)
{
    //do stuff


}

// TODO: Append all legal queen moves to moveList
void generateQueenMoves(Board* boardPtr, std::list<Move*>* moveListPtr)
{
    //do stuff


}

// TODO: Append all legal king moves to moveList
void generateKingMoves(Board* boardPtr, std::list<Move*>* moveListPtr)
{
    //do stuff


}

// Generate all legal moves for a given position
std::list<Move*>* generateMoves(Board* boardPtr)
{   
    std::list<Move*> moveList;
    std::list<Move*>* moveListPtr = &moveList;
    
    generatePawnMoves(boardPtr, moveListPtr);
    generateKnightMoves(boardPtr, moveListPtr);
    generateBishopMoves(boardPtr, moveListPtr);
    generateRookMoves(boardPtr, moveListPtr);
    generateQueenMoves(boardPtr, moveListPtr);
    generateKingMoves(boardPtr, moveListPtr);

    return moveListPtr;
}

// TODO: Update a board according to a given move
Board* makeMove(Board* boardPtr, Move* movePtr)
{
    // Update the turn count
    (*boardPtr).turns += 1;

    // // White move
    // if ((*boardPtr).whitePieces & (*movePtr).startSquare)
    // {
    //     (*boardPtr).activePlayer = activePlayerBlack; // Update the player set to make the next move
    //     (*movePtr).pieceColour = pieceColourWhite;
        
    //     if ((*boardPtr).whitePawns & (*movePtr).startSquare)
    //     {
    //         (*movePtr).pieceType = pieceTypePawn;

    //         // Check if it's an enpassant move


    //         // Check if it's a capture
    //         if ((*movePtr).endSquare & (*boardPtr).blackPieces)
    //         {
    //             (*movePtr).moveType = capture;
    //         }
    //     }
    //     else if ((*boardPtr).whiteKnights & (*movePtr).startSquare)
    //     {
    //         (*movePtr).pieceType = pieceTypeKnight; 


    //     }                
    //     else if ((*boardPtr).whiteBishops & (*movePtr).startSquare)
    //     {
    //         (*movePtr).pieceType = pieceTypeBishop;


    //     }                 
    //     else if ((*boardPtr).whiteRooks & (*movePtr).startSquare)
    //     {
    //         (*movePtr).pieceType = pieceTypeRook;


    //     }
    //     else if ((*boardPtr).whiteQueens & (*movePtr).startSquare)
    //     {
    //         (*movePtr).pieceType = pieceTypeQueen;


    //     }                
    //     else if ((*boardPtr).whiteKing & (*movePtr).startSquare)
    //     {
    //         (*movePtr).pieceType = pieceTypeKing;  

    //         // Castling
    //         if ((*movePtr).startSquare == 0x10 && (((*movePtr).endSquare == 0x40) || ((*movePtr).endSquare == 0x4)))
    //         {
    //             (*movePtr).moveType = castle;
    //             (*boardPtr).whiteCanCastleKS = false;
    //             (*boardPtr).whiteCanCastleQS = false;
    //         }
    //     }
    // }

    // // Black move
    // else
    // {
        
    // }


    std::cout << (*movePtr).startSquare << std::endl << (*movePtr).endSquare << std::endl;

    return boardPtr;
}

// Convert a start square cartesian coordinate to it's equivalent bitboard representation
Bitboard getStartSquare(std::string moveStr)
{
    Bitboard fileShift = moveStr[0] - 'a';
    Bitboard rankShift = north*(moveStr[1] - '1');

    return (Bitboard)1 << fileShift + rankShift;
}

// Convert an end square cartesian coordinate to it's equivalent bitboard representation
Bitboard getEndSquare(std::string moveStr)
{
    Bitboard fileShift = moveStr[2] - 'a';
    Bitboard rankShift = north*(moveStr[3] - '1');

    return (Bitboard)1 << fileShift + rankShift;
}

// TODO: Convert a move object into algebraic notation
std::string moveToString(Move* movePtr)
{
    std::string moveStr;
    
    // Shift the start and end squares appropriately to determine the coordinate
    Bitboard b;
    short idx;
    while (b > 128)
    {
        b = (*movePtr).startSquare >> 8*idx;
        idx++;
    }
    char rank = idx;


    while (!(((*movePtr).startSquare >> idx) > 1))
    {
        (*movePtr).startSquare >> idx;
    }
    short file = idx;

    //std::cout << rank << std::endl << file << std::endl;

    //moveStr[0] = std::__int_to_char(rank + std::atoi('a'));







    if ((*movePtr).moveType == promotion)
    {
        moveStr += "=";

        switch ((*movePtr).promotedTo)
        {
            case pieceTypeQueen:
                moveStr += "Q";
                break;
            case pieceTypeRook:
                moveStr += "R";
                break;
            case pieceTypeBishop:
                moveStr += "B";
                break;
            case pieceTypeKnight:
                moveStr += "N";
                break;
            default:
                break;
        }
    }
    else if ((*movePtr).moveType == check)
        moveStr += "+";
    else if ((*movePtr).moveType == checkmate)
        moveStr += "#";

    return moveStr;
}

} // namespace

