#include "PhraseHandler.h"

PhraseHandler::PhraseHandler(const QString &phrase)
    : originalPhrase(phrase)
{
    currentLetters = "";
    for (int i = 0; i < originalPhrase.length(); i++) {
        if (originalPhrase[i] == ' ')
            currentLetters += ' ';
        else
            currentLetters += '_';
    }
}

bool PhraseHandler::guessLetter(QChar letter)
{
    letter = letter.toUpper();
    bool found = false;

    for (int i = 0; i < originalPhrase.length(); i++) {
        if (originalPhrase[i].toUpper() == letter) {
            currentLetters[i] = originalPhrase[i]; // preserve original case
            found = true;
        }
    }

    return found;
}

void PhraseHandler::revealPhrase()
{
    currentLetters = originalPhrase;
}

QString PhraseHandler::getDisplayedPhrase() const
{
    QString spaced = "";
    for (int i = 0; i < currentLetters.length(); i++) {
        if (currentLetters[i] == ' ')
            spaced += "   ";   // space between words
        else
            spaced += QString(currentLetters[i]) + "  "; // letter or underscore plus 2 spaces
    }
    return spaced;
}

bool PhraseHandler::isComplete() const
{
    for (int i = 0; i < currentLetters.length(); i++) {
        if (originalPhrase[i] != ' ' && currentLetters[i] == '_')
            return false;
    }
    return true;
}
