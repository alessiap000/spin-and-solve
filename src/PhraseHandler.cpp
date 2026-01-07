// Handles the logic for displaying a phrase and checking letters guessed by the player

#include "PhraseHandler.h"

// Constructor: initialize the phrase handler with the given phrase
PhraseHandler::PhraseHandler(const QString &phrase)
    : originalPhrase(phrase)
{
    // Initialize currentLetters with underscores for letters and spaces for spaces
    currentLetters = "";
    for (int i = 0; i < originalPhrase.length(); i++) {
        if (originalPhrase[i] == ' ')
            currentLetters += ' ';  // keep spaces as is
        else
            currentLetters += '_';  // hide letters with underscore
    }
}

// Check if a guessed letter is in the phrase, returns true if at least one match is found
bool PhraseHandler::guessLetter(QChar letter)
{
    letter = letter.toUpper();  // make guess case-insensitive (turn all letters to upper case)
    bool found = false;

    for (int i = 0; i < originalPhrase.length(); i++) {
        if (originalPhrase[i].toUpper() == letter) {
            currentLetters[i] = originalPhrase[i]; // reveal the letter
            found = true;
        }
    }

    return found;
}

// Reveal the full phrase (used for ending the game or showing solution)
void PhraseHandler::revealPhrase()
{
    currentLetters = originalPhrase;
}

// Get the phrase formatted for display with underscores and spaces
QString PhraseHandler::getDisplayedPhrase() const
{
    QString spaced = "";
    for (int i = 0; i < currentLetters.length(); i++) {
        if (currentLetters[i] == ' ')
            spaced += "   ";   // extra spacing for word separation
        else
            spaced += QString(currentLetters[i]) + "  "; // letter or underscore plus 2 spaces
    }
    return spaced;
}

// Check if the player has successfully guessed the entire phrase
bool PhraseHandler::isComplete() const
{
    for (int i = 0; i < currentLetters.length(); i++) {
        if (originalPhrase[i] != ' ' && currentLetters[i] == '_')
            return false;  // found a hidden letter
    }
    return true; // all letters revealed
}
