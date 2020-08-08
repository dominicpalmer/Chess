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

    std::string line, guiCommand;
    while (guiCommand.clear(), std::getline(std::cin, line))
    {
        // Send line to a string stream, with first word fed into guiCommand
        std::istringstream stream(line);
        stream >> std::skipws >> guiCommand;

        // Responses for initial setup
        if (guiCommand == "ucinewgame" || guiCommand == "setoption" || guiCommand == "ponderhit")
            continue;
        else if (guiCommand == "uci")
        {
            std::cout << "id name " << "\n"
                      << "id author Dominic Palmer" << "\n"
                      << "uciok" << std::endl;
        }
        else if (guiCommand == "isready")
            std::cout << "readyok" << std::endl;

        // Position and move responses
        else if (guiCommand == "position") 
        {
            setBoard(boardPtr, stream);
        }
        else if (guiCommand == "go")
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
        else if (guiCommand.empty() || guiCommand == "quit" || guiCommand == "stop")
            break;
        else 
            std::cout << "Unknown command: " << guiCommand << std::endl;
    };
}

} // namespace