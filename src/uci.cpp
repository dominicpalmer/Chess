#include "move.h"
#include <iostream>
#include <string>
#include <thread>
#include <list>


namespace uci
{

// UCI communication loop
void uciLoop()
{
    // Setup default board position
    boardSpace::Board* boardPtr = new boardSpace::Board();

    std::string line, token;
    while (token.clear(), std::getline(std::cin, line))
    {
        // Send line to a string stream, with first word fed into token
        std::istringstream stream(line);
        stream >> std::skipws >> token;

        // Responses for initial setup
        if (token == "ucinewgame" || token == "setoption" || token == "ponderhit")
            continue;
        else if (token == "uci")
        {
            std::cout << "id name " << "\n"
                      << "id author Dominic Palmer" << "\n"
                      << "uciok" << std::endl;
        }
        else if (token == "isready")
            std::cout << "readyok" << std::endl;

        // Position and move responses
        else if (token == "position") 
        {
            setBoard(boardPtr, stream);
        }
        else if (token == "go")
        {
            // 1. Parse time controls
            // int whiteRemainingTime = x, blackRemainingTime = y;

            // 2. Generate all moves, returning a moveList
            std::list<Move*>* moveList = moveSpace::generateMoves(boardPtr);
            
            // 3. Search function. Will use an evaluation function, and ultimately return the best move
            // Move* bestmove = search(boardPtr, moveList);

            // 4. Convert the best move to asci and send to standard output
            // std::string bestmoveStr = moveToString(bestmove);
            // std::cout << "bestmove " + bestmoveStr << std::endl; 
    
            

            //std::thread goThread(boardPtr, std::ref(stream));
            //goThread.detach();
        }

        // Handle exits and unknown commands
        else if (token.empty() || token == "quit" || token == "stop")
            break;
        else 
            std::cout << "Unknown command: " << token << std::endl;
    };
}

} // namespace