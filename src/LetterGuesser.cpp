// This file handles the letter-guessing logic for the Spin & Solve game

#include "LetterGuesser.h"

LetterGuesser::LetterGuesser(const QString &phrase)
    : phrase(phrase.toUpper()) // store the phrase in uppercase for consistency
{
    // Initialize displayedPhrase with underscores for letters and spaces for word gaps
    displayedPhrase = "";
    for (QChar c : this->phrase) {
        if (c == ' ')
            displayedPhrase += "   ";
        else
            displayedPhrase += "_  ";
    }
}

// Processes a guessed letter and updates the displayed phrase
bool LetterGuesser::guessLetter(QChar letter)
{
    bool found = false;             // Tracks if the guessed letter exists in the phrase
    QString updatedDisplay = "";    // Build the updated displayed phrase

    letter = letter.toUpper();      // Ensure case-insensitive comparison

    for (int i = 0; i < phrase.length(); i++) {
        if (phrase[i] == ' ') {
            updatedDisplay += "   "; // Preserve spaces between words
        } else if (phrase[i] == letter) {
            updatedDisplay += QString(letter) + "  "; // Reveal guessed letter
            found = true;
        } else {
            // Preserve previously guessed letters or underscores
            int displayIndex = i * 3;
            if (displayedPhrase.mid(displayIndex, 1) != "_")
                updatedDisplay += displayedPhrase.mid(displayIndex, 3);
            else
                updatedDisplay += "_  ";
        }
    }

    displayedPhrase = updatedDisplay; // Update the stored displayed phrase
    return found;                     // Return whether the guess was correct
}

// Returns the current state of the displayed phrase
QString LetterGuesser::getDisplayedPhrase() const
{
    return displayedPhrase;
}

// Returns true if the phrase has been completely guessed
bool LetterGuesser::isComplete() const
{
    return !displayedPhrase.contains("_"); // No underscores means phrase is complete
}
