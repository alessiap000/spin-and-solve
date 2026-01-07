#ifndef LETTERGUESSER_H
#define LETTERGUESSER_H

#include <QString>

class LetterGuesser {
private:
    QString phrase;
    QString displayedPhrase;

public:
    LetterGuesser(const QString &phrase);
    bool guessLetter(QChar letter);
    QString getDisplayedPhrase() const;
    bool isComplete() const;
};

#endif
 // LETTERGUESSER_H
