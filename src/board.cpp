#include "board.h"
#include "move.h"
#include <iostream>
#include <vector>
#include <iterator>

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

// TODO: Fen position parser
void parseFen(Board* boardPtr, std::istringstream& stream)
{
    // Example:
    // "position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1"

    // Split the fen stream into a vector of whitespace seperated strings
    std::string buffer;
    std::vector<std::string> arguments;
    while (std::getline(stream, buffer, ' '))
    {
        arguments.push_back(buffer);
    }

    // Remove all pieces from the default initialised board and set castling rights to false
    (*boardPtr).whitePawns = 0;
    (*boardPtr).whiteKnights = 0;
    (*boardPtr).whiteBishops = 0;
    (*boardPtr).whiteRooks = 0;
    (*boardPtr).whiteQueens = 0;
    (*boardPtr).whiteKing = 0;
    (*boardPtr).blackPawns = 0;
    (*boardPtr).blackKnights = 0;
    (*boardPtr).blackBishops = 0;
    (*boardPtr).blackRooks = 0;
    (*boardPtr).blackQueens = 0;
    (*boardPtr).blackKing = 0;
    (*boardPtr).whiteCanCastleKS = false;
    (*boardPtr).whiteCanCastleQS = false;
    (*boardPtr).blackCanCastleKS = false;
    (*boardPtr).blackCanCastleQS = false;

    int argumentsIndex = 0;
    Bitboard shiftCount = 0;
    for (std::vector<std::string>::iterator it = arguments.begin(); it < arguments.end(); it++)
    {   
        switch (argumentsIndex)
        {
            // Piece placement
            case (0):
                for (int i = 0; i < (*it).length(); i++)
                {
                    switch ((*it)[i])
                    {
                        case '8': shiftCount += 8; break;
                        case '7': shiftCount += 7; break;
                        case '6': shiftCount += 6; break;
                        case '5': shiftCount += 5; break;
                        case '4': shiftCount += 4; break;
                        case '3': shiftCount += 3; break;
                        case '2': shiftCount += 2; break;
                        case '1': shiftCount += 1; break;
                        case 'p': (*boardPtr).whitePawns |= (Bitboard)1 << shiftCount; shiftCount++; break;
                        case 'n': (*boardPtr).whiteKnights |= (Bitboard)1 << shiftCount; shiftCount++; break;
                        case 'b': (*boardPtr).whiteBishops |= (Bitboard)1 << shiftCount; shiftCount++; break;
                        case 'r': (*boardPtr).whiteRooks |= (Bitboard)1 << shiftCount; shiftCount++; break;
                        case 'q': (*boardPtr).whiteQueens |= (Bitboard)1 << shiftCount; shiftCount++; break;
                        case 'k': (*boardPtr).whiteKing |= (Bitboard)1 << shiftCount; shiftCount++; break;
                        case 'P': (*boardPtr).blackPawns |= (Bitboard)1 << shiftCount; shiftCount++; break;
                        case 'N': (*boardPtr).blackKnights |= (Bitboard)1 << shiftCount; shiftCount++; break;
                        case 'B': (*boardPtr).blackBishops |= (Bitboard)1 << shiftCount; shiftCount++; break;
                        case 'R': (*boardPtr).blackRooks |= (Bitboard)1 << shiftCount; shiftCount++; break;
                        case 'Q': (*boardPtr).blackQueens |= (Bitboard)1 << shiftCount; shiftCount++; break;
                        case 'K': (*boardPtr).blackKing |= (Bitboard)1 << shiftCount; shiftCount++; break;
                        case '/': break;
                    }
                }
                break;

            // Player to move
            case (1):
                for (int j = 0; j < (*it).length(); j++)
                {
                    switch ((*it)[j])
                    {
                        case 'b': (*boardPtr).activePlayer = activePlayerBlack; break;
                        case 'w': (*boardPtr).activePlayer = activePlayerWhite; break;
                    }
                }
            
            // Castling rights
            case (2):
                for (int k = 0; k < (*it).length(); k++)
                {
                    switch ((*it)[k])
                    {
                        case 'K': (*boardPtr).blackCanCastleKS = true; break;
                        case 'Q': (*boardPtr).blackCanCastleQS = true; break;
                        case 'k': (*boardPtr).whiteCanCastleKS = true; break;
                        case 'q': (*boardPtr).whiteCanCastleQS = true; break;
                        case '-': break;
                    }
                }

            // Enpassant move played
            case (3):
                break;

            // Moves since 50 move rule reset
            case (4): 
                break;

            // Number of turns
            case (5):
                (*boardPtr).turns = std::stoi(*it);
        }
    }

    argumentsIndex++;
}




// Set up a position from startpos or fen
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
            Move* movePtr = new Move();
            std::list<Move*>* moveList = generateMoves(boardPtr);

            for (std::list<Move*>::iterator it = (*moveList).begin(); it != (*moveList).end(); it++)
            {
                if (moveToString(*it) == moveStr)
                    movePtr = *it;
            }

            makeMove(boardPtr, movePtr);
        }
    }
    else if (argument == "fen")
    {
        parseFen(boardPtr, stream);
    }
}

} // namespace