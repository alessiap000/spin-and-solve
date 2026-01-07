#ifndef PHRASELIBRARY_H
#define PHRASELIBRARY_H

#include <vector>
#include <string>

struct Phrase {
    std::string text;
    std::string category;
    std::vector<std::string> hints;
};

class PhraseLibrary {
private:
    std::vector<Phrase> easyPhrase;
    std::vector<Phrase> hardPhrase;
    int lastEasyIndex;
    int lastHardIndex;

public:
    PhraseLibrary();
    Phrase getRandomPhrase(const std::string &difficulty);
};

#endif // PHRASELIBRARY_H
