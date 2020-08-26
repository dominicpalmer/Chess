#ifndef GLOBALS_H_
#define GLOBALS_H_

typedef __UINT64_TYPE__ Bitboard;

enum PieceType {pieceTypePawn, pieceTypeKnight, pieceTypeBishop, pieceTypeRook, pieceTypeQueen, pieceTypeKing, pieceTypeNone};
enum PieceColour {pieceColourWhite, pieceColourBlack};
enum ActivePlayer {activePlayerWhite, activePlayerBlack};
enum MoveType {normal, capture, enpassant, promotion, castle, check, checkmate};
enum Direction {north = 8,
                south = -north, 
                east = 1,
                west = -east,
                northEast = north + east,
                northWest = north + west,
                southEast = south + east,
                southWest = south + west};
struct Move
{
    Bitboard startSquare;
    Bitboard endSquare;
    PieceColour pieceColour;
    PieceType pieceType;
    MoveType moveType;
    PieceType promotedTo;
};

#endif