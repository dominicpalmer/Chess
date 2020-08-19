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
    this->turns = 0;
    this->fmrCount;
    this->activePlayer = activePlayerWhite;
    this->enPassantAvailable = "-";

    this->whiteCanCastleQS = true;
    this->whiteCanCastleKS = true;
    this->blackCanCastleQS = true;
    this->blackCanCastleKS = true;

    this->whitePawns = 0xFF00;
    this->whiteKnights = 0x42; 
    this->whiteBishops = 0x24;
    this->whiteRooks = 0x81;
    this->whiteQueens = 0x8;
    this->whiteKing = 0x10;
    this->blackPawns = 0xFF000000000000;
    this->blackKnights = 0x4200000000000000;
    this->blackBishops = 0x2400000000000000;
    this->blackRooks = 0x8100000000000000;
    this->blackQueens = 0x800000000000000;
    this->blackKing = 0x1000000000000000;
}

// Fen position parser,  e.g: "position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1"
void parseFen(Board* boardPtr, std::istringstream& stream)
{
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

    // Force the stream to treat whitespace as tokens
    char token;
    stream >> std::noskipws;
    stream >> token;

    // Piece placement
    Bitboard shiftCount = 0;
    while (stream >> token && !std::isspace(token))
    {
        switch (token)
        {
            case '8': shiftCount += 8; break;
            case '7': shiftCount += 7; break;
            case '6': shiftCount += 6; break;
            case '5': shiftCount += 5; break;
            case '4': shiftCount += 4; break;
            case '3': shiftCount += 3; break;
            case '2': shiftCount += 2; break;
            case '1': shiftCount += 1; break;
            case 'P': (*boardPtr).whitePawns |= 0x8000000000000000 >> 8*((int)shiftCount/8) + (7 - (shiftCount % 8)); shiftCount++; break;
            case 'N': (*boardPtr).whiteKnights |= 0x8000000000000000 >> 8*((int)shiftCount/8) + (7 - (shiftCount % 8)); shiftCount++; break;
            case 'B': (*boardPtr).whiteBishops |= 0x8000000000000000 >> 8*((int)shiftCount/8) + (7 - (shiftCount % 8)); shiftCount++; break;
            case 'R': (*boardPtr).whiteRooks |= 0x8000000000000000 >> 8*((int)shiftCount/8) + (7 - (shiftCount % 8)); shiftCount++; break;
            case 'Q': (*boardPtr).whiteQueens |= 0x8000000000000000 >> 8*((int)shiftCount/8) + (7 - (shiftCount % 8)); shiftCount++; break;
            case 'K': (*boardPtr).whiteKing |= 0x8000000000000000 >> 8*((int)shiftCount/8) + (7 - (shiftCount % 8)); shiftCount++; break;
            case 'p': (*boardPtr).blackPawns |= 0x8000000000000000 >> 8*((int)shiftCount/8) + (7 - (shiftCount % 8)); shiftCount++; break;
            case 'n': (*boardPtr).blackKnights |= 0x8000000000000000 >> 8*((int)shiftCount/8) + (7 - (shiftCount % 8)); shiftCount++; break;
            case 'b': (*boardPtr).blackBishops |= 0x8000000000000000 >> 8*((int)shiftCount/8) + (7 - (shiftCount % 8)); shiftCount++; break;
            case 'r': (*boardPtr).blackRooks |= 0x8000000000000000 >> 8*((int)shiftCount/8) + (7 - (shiftCount % 8)); shiftCount++; break;
            case 'q': (*boardPtr).blackQueens |= 0x8000000000000000 >> 8*((int)shiftCount/8) + (7 - (shiftCount % 8)); shiftCount++; break;
            case 'k': (*boardPtr).blackKing |= 0x8000000000000000 >> 8*((int)shiftCount/8) + (7 - (shiftCount % 8)); shiftCount++; break;
            case '/': break;
        }
    }
    
    // Set the player to move and consume whitespace
    stream >> token;
    (*boardPtr).activePlayer = (token == 'w' ? activePlayerWhite : activePlayerBlack);
    stream >> token;
    
    // Castling rights
    while (stream >> token, token != ' ')
    {
        switch (token)
        {
            case 'K': (*boardPtr).blackCanCastleKS = true; break;
            case 'Q': (*boardPtr).blackCanCastleQS = true; break;
            case 'k': (*boardPtr).whiteCanCastleKS = true; break;
            case 'q': (*boardPtr).whiteCanCastleQS = true; break;
            case '-': break;
        }
    }

    // Enpassant move played
    while (stream >> token, token != ' ')
    {
        (*boardPtr).enPassantAvailable = token;
    }
    
    // Moves since 50 move rule reset and turn count
    stream >> std::skipws >> (*boardPtr).fmrCount >> (*boardPtr).turns;
}

// Set up a position from startpos or fen
void setBoard(Board* boardPtr, std::istringstream& stream)
{
    // Parse the first argument
    std::string token;
    stream >> token;

    // Two cases: startpos or fen
    if (token == "startpos")
    {
        // Ignore the 'moves' argument
        stream >> token;

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
    else if (token == "fen")
    {
        parseFen(boardPtr, stream);
        std::list<Move*>* moveList = generateMoves(boardPtr);
    }
}

} // namespace