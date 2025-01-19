#include "testGame.hh"
using namespace cdxg;

// TODO : find a way to handle runtime errors for the user (error code ?)
// TODO : create a log system
// TODO : ASAP document everything before it gets messier

/**
 * The main function, called when the executable lauches
 */
int main(){
    TestGame game = TestGame(800, 600, "testGame");
    game.Run();
    return 0;
}