#include "game.h"
#include "game.h"
#include <vector>
#include <cstdlib>
#include <ctime>

Game::Game() {
    std::srand(std::time(nullptr)); // random generator
}

QString Game::spinWheel(int difficulty) {
    // declare and initialize segments inside the function
    std::vector<QString> segments = {
        "minus 5 seconds",
        "minus 5 seconds",
        "5 gems",
        "2 gems",
        "2 gems",
        "2 gems",
        "2 gems",
        "free hint"
    };

    QString result = "No prize"; // initialize result to avoid warnings

    // compute spin length, shorter for harder difficulty
    int spinLength = 20 + std::rand() % 10 - difficulty * 2;

    int index = 0;
    for (int i = 0; i < spinLength; i++) {
        index = (index + 1) % segments.size();
    }

    // assign the final segment to result
    result = segments[index];

    return result;
}
