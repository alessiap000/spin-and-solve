#include "Instructions.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

// The Instructions class is a QWidget window that introduces the player to the game
Instructions::Instructions(QWidget *parent)
    : QWidget(parent)
{
    // Set window size
    setFixedSize(750, 550);

    // Background image
    QLabel *background = new QLabel(this);
    QPixmap pix(":/images/images/Instructions.png");
    background->setPixmap(pix.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    background->setGeometry(0, 0, width(), height());
    background->lower();

    // Back button
    backButton = new QPushButton("← Back", this);
    backButton->setStyleSheet("background-color: #EBD1E5; color: #5C1F53; font-size: 16px;");
    backButton->setFixedSize(100, 35);
    backButton->move(10, 10);

    // Connect the back button to return to the main menu
    connect(backButton, &QPushButton::clicked, this, &Instructions::backToMenu);

    // Instructions text
    instructionsLabel = new QLabel(this);
    instructionsLabel->setText(
        "<b>Welcome to Spin & Solve!</b><br><br>"
        "Spin & Solve is a fun word puzzle game where you spin the wheel, guess letters, "
        "buy vowels or hints, and solve hidden phrases. Challenge your thinking and vocabulary "
        "while enjoying an interactive game experience!<br><br>"

        "<b>How to Play:</b><br>"
        "1. Click 'Start Game' and select your difficulty level.<br>"
        "2. To guess a letter, first spin the wheel. You earn gems or prizes only if your guess is correct.<br>"
        "3. Guess consonants to reveal letters in the hidden phrase.<br>"
        "4. Use your gems to buy vowels or get hints.<br>"
        "5. Click 'Solve Phrase' to attempt the full phrase before time runs out.<br><br>"

        "Good luck, contestant!"
        );

    // Adjust the text
    instructionsLabel->setWordWrap(true);
    instructionsLabel->setAlignment(Qt::AlignCenter);
    instructionsLabel->setMaximumWidth(390);
    instructionsLabel->setStyleSheet("font-size: 14px; color: #5C1F53;");

    // Layout setup
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addSpacing(70);
    mainLayout->addWidget(instructionsLabel);
    mainLayout->setAlignment(instructionsLabel, Qt::AlignCenter);
    setLayout(mainLayout);
}
