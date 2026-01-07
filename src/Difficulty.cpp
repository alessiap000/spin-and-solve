// A simple dialog box that allows the user to select between Easy and Hard difficulty levels before starting the game

#include "Difficulty.h"

Difficulty::Difficulty(QWidget *parent) : QDialog(parent), difficulty(-1) {
    setWindowTitle("Select Difficulty");
    setFixedSize(300, 100);

    QPushButton *easyButton = new QPushButton("Easy", this);
    QPushButton *hardButton = new QPushButton("Hard", this);

    connect(easyButton, &QPushButton::clicked, this, &Difficulty::easyClicked);
    connect(hardButton, &QPushButton::clicked, this, &Difficulty::hardClicked);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(easyButton);
    layout->addWidget(hardButton);
    setLayout(layout);
}

int Difficulty::getSelectedDifficulty() const {
    return difficulty;
}

// Slot for Easy button
void Difficulty::easyClicked() {
    difficulty = 0;
    accept(); // Close the dialog and return QDialog::Accepted
}

// Slot for Hard button
void Difficulty::hardClicked() {
    difficulty = 1;
    accept(); // Close the dialog and return QDialog::Accepted
}
