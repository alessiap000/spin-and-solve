// This file handles returning a segment result based on predefined wheel segments

#include "game.h"
#include "game.h"
#include <vector>
#include <cstdlib>
#include <ctime>

Game::Game() {
    std::srand(std::time(nullptr)); // random generator
}

QString Game::spinWheel(int difficulty) {

    // Declare and initialize segments on the wheel
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

    // Compute spin length, shorter for harder difficulty
    int spinLength = 20 + std::rand() % 10 - difficulty * 2;

    int index = 0;
    for (int i = 0; i < spinLength; i++) {
        index = (index + 1) % segments.size();
    }

    // Assign the final segment to result
    result = segments[index];

    return result;
}
