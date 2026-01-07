#ifndef GAME_H
#define GAME_H

#include <QString>

class Game {
public:
    Game();
    QString spinWheel(int difficulty); // returns a random prize
};

#endif // GAME_H
