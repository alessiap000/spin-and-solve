#ifndef PHRASEHANDLER_H
#define PHRASEHANDLER_H

#include <QString>

class PhraseHandler
{
public:
    explicit PhraseHandler(const QString &phrase);

    bool guessLetter(QChar letter);
    void revealPhrase();

    QString getDisplayedPhrase() const;
    QString getOriginalPhrase() const { return originalPhrase; }
    bool isComplete() const;

private:
    QString originalPhrase;
    QString currentLetters;
};

#endif // PHRASEHANDLER_H
