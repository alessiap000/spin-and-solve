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

void Difficulty::easyClicked() {
    difficulty = 0;
    accept();
}

void Difficulty::hardClicked() {
    difficulty = 1;
    accept();
}
