#include "LetterGuesser.h"

LetterGuesser::LetterGuesser(const QString &phrase)
    : phrase(phrase.toUpper())
{
    displayedPhrase = "";
    for (QChar c : this->phrase) {
        if (c == ' ')
            displayedPhrase += "   ";
        else
            displayedPhrase += "_  ";
    }
}

bool LetterGuesser::guessLetter(QChar letter)
{
    bool found = false;
    QString updatedDisplay = "";

    letter = letter.toUpper();

    for (int i = 0; i < phrase.length(); i++) {
        if (phrase[i] == ' ') {
            updatedDisplay += "   ";
        } else if (phrase[i] == letter) {
            updatedDisplay += QString(letter) + "  ";
            found = true;
        } else {
            // Keep current character (either letter or underscore)
            int displayIndex = i * 3; // because each char is "_  " (3 wide)
            if (displayedPhrase.mid(displayIndex, 1) != "_")
                updatedDisplay += displayedPhrase.mid(displayIndex, 3);
            else
                updatedDisplay += "_  ";
        }
    }

    displayedPhrase = updatedDisplay;
    return found;
}

QString LetterGuesser::getDisplayedPhrase() const
{
    return displayedPhrase;
}

bool LetterGuesser::isComplete() const
{
    return !displayedPhrase.contains("_");
}
