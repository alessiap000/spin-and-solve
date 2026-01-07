#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

// Displays the game's instructions screen
class Instructions : public QWidget
{
    Q_OBJECT

public:
    explicit Instructions(QWidget *parent = nullptr);

signals:
    void backToMenu(); // Return to the main menu

private:
    QPushButton *backButton;
    QLabel *instructionsLabel;
};

#endif // INSTRUCTIONS_H
