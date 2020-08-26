#ifndef MOVES_H_
#define MOVES_H_

#include "board.hpp"
#include <string>
#include <list>

using namespace boardSpace;

namespace moveSpace
{

void generatePawnMoves(Board* boardPtr, std::list<Move*>* moveListPtr);
void generateKnightMoves(Board* boardPtr, std::list<Move*>* moveListPtr);
void generateBishopMoves(Board* boardPtr, std::list<Move*>* moveListPtr);
void generatePawnMoves(Board* boardPtr, std::list<Move*>* moveListPtr);
void generatePawnMoves(Board* boardPtr, std::list<Move*>* moveListPtr);
void generatePawnMoves(Board* boardPtr, std::list<Move*>* moveListPtr);
std::list<Move*>* generateMoves(Board* boardPtr);
Board* makeMove(Board* boardPtr, Move* movePtr);
Bitboard getStartSquare(std::string moveStr);
Bitboard getEndSquare(std::string moveStr);
std::string moveToString(Move* movePtr);

} // namespace move

#endif