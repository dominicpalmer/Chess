#ifndef GLOBALS_H_
#define GLOBALS_H_

typedef __UINT64_TYPE__ Bitboard;

enum PieceType {pieceTypePawn, pieceTypeKnight, pieceTypeBishop, pieceTypeRook, pieceTypeQueen, pieceTypeKing};
enum PieceColour {pieceColourWhite, pieceColourBlack};
enum ActivePlayer {activePlayerWhite, activePlayerBlack};
enum MoveType {normal, capture, enpassant, promotion, castle, check, checkmate};
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