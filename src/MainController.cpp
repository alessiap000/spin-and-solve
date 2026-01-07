#include "MainController.h"
#include "Difficulty.h"
#include "GameController.h"
#include "Instructions.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>

MainController::MainController(QWidget *parent) : QWidget(parent) {
    // Set fixed size
    setFixedSize(750, 550);

    // Background image using QLabel
    QLabel *background = new QLabel(this);
    QPixmap pix(":/images/images/SPIN_SOLVE.png");
    background->setPixmap(pix.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    background->setGeometry(0, 0, width(), height());
    background->lower(); // send it behind all other widgets

    // Buttons
    startButton = new QPushButton("Start Game", this);
    instructionsButton = new QPushButton("Instructions", this);

    // Customize button color
    startButton->setStyleSheet("background-color: #5C1F53; color: white; font-size: 18px;");
    instructionsButton->setStyleSheet("background-color: #5C1F53; color: white; font-size: 18px;");

    startButton->setFixedSize(150, 40);
    instructionsButton->setFixedSize(150, 40);

    // Layout for buttons side by side
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(instructionsButton);
    buttonLayout->setSpacing(30);
    buttonLayout->setAlignment(Qt::AlignCenter);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch(); // push buttons down a bit
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    // Connect buttons
    connect(startButton, &QPushButton::clicked, this, &MainController::startGame);
    connect(instructionsButton, &QPushButton::clicked, this, &MainController::showInstructions);
}

void MainController::startGame() {
    Difficulty dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        int difficulty = dlg.getSelectedDifficulty();
        qDebug() << "Difficulty selected:" << (difficulty == 0 ? "Easy" : "Hard");

        GameController *gameScreen = new GameController(difficulty);

        connect(gameScreen, &QWidget::destroyed, this, [=]() {
            this->show();
        });

        gameScreen->setWindowTitle("Spin & Solve");
        gameScreen->show();

        this->hide();
    }
}

void MainController::showInstructions() {
    Instructions *instructions = new Instructions();

    connect(instructions, &Instructions::backToMenu, this, [=]() {
        instructions->close();
        this->show();
    });

    instructions->setWindowTitle("Spin & Solve");
    instructions->show();

    this->hide();
}

void MainController::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Exit Game",
        "Do you want to leave the game?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}
