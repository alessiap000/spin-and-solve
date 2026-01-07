#include "Help.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QTimer>

// The Help class is a QWidget window that shows players how to play the game.
Help::Help(QWidget *parent)
    : QWidget(parent)
{
    // Set a fixed window size
    setFixedSize(750, 550);

    // Background image
    // Background image using QLabel
    QLabel *background = new QLabel(this);
    QPixmap pix(":/images/images/Instructions.png");
    background->setPixmap(pix.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    background->setGeometry(0, 0, width(), height());
    background->lower(); // send it behind all other widgets

    // Back button
    backButton = new QPushButton("← Back", this);
    backButton->setStyleSheet("background-color: #EBD1E5; color: #5C1F53; font-size: 16px;");
    backButton->setFixedSize(100, 35);
    backButton->move(10, 10);

    // When clicked, the back button closes the Help window (player goes back to the game screen)
    connect(backButton, &QPushButton::clicked, this, &Help::backToGame);

    // Help window text (the instructions on how to play the game)
    helpLabel = new QLabel(this);
    helpLabel->setText(
        "<b>Need a hand? Let’s break it down!</b><br><br>"

        "<b>1. Category:</b><br>"
        "- Look at the category label to know what kind of<br> phrase it is (e.g., Movie, Food, Book).<br><br>"

        "<b>2. Spin the Wheel:</b><br>"
        "- Click 'Spin' to spin the wheel and reveal a segment.<br>"
        "- You can earn gems for correct guesses, or special hints.<br><br>"

        "<b>3. Timer:</b><br>"
        "- Watch out for segments that subtract time - <b>Time is important!</b><br><br>"

        "<b>4. Guess Letters:</b><br>"
        "- Guess consonants to reveal letters.<br>"
        "- Click 'Solve Phrase' to attempt the full phrase, but be careful:<br>"
        "if your guess is wrong, it will cost you <b>5 seconds</b> of your time!<br><br>"

        "<b>Have fun solving the phrases!</b>"
        );

    // Adjust the text
    helpLabel->setWordWrap(true);
    helpLabel->setAlignment(Qt::AlignCenter);
    helpLabel->setMaximumWidth(390);
    helpLabel->setStyleSheet("font-size: 14px; color: #5C1F53;");

    // Layout setup
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addSpacing(70);
    mainLayout->addWidget(helpLabel);
    mainLayout->setAlignment(helpLabel, Qt::AlignCenter);
    setLayout(mainLayout);

};

// A function that closes the Help window and returns to the game screen
void Help::backToGame() {
    this->close();
}
