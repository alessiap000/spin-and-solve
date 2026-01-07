// This file implements the main gameplay logic and UI for Spin & Solve
// It handles the wheel, letter guessing, timers, hints, gems, and end-of-game scenarios.

#include "GameController.h"
#include "MainController.h"
#include "PhraseLibrary.h"
#include "PlayerGems.h"
#include "Help.h"
#include "PhraseHandler.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>
#include <QPainter>
#include <QInputDialog>
#include <QTimer>

GameController::GameController(int diff, QWidget *parent)
    : QWidget(parent), difficulty(diff), playerGems(0, this) {

    setFixedSize(750, 550);

    setUpUI();
}

// Wheel setup
void GameController::setUpWheel() {
    if (!wheel) {
        wheel = new Wheel(this);
        wheel->setFixedSize(280, 280);
        wheel->setStyleSheet(
            "border: 5px solid #FFE3F8;"
            "border-radius: 200px;"
            "background-color: #FFE3F8;"
            );

        // Connect wheel landing to reward processing
        connect(wheel, &Wheel::landedSegment, this, [=](int index){
            QStringList segments = { "2 gems","-5 seconds","3 gems","Free Hint",
                                    "1 gem","-10 seconds","2 gems","4 gems" };
            QString landedSegment = segments[index];

            wheelResultLabel->setText("Wheel landed on: " + landedSegment);

            startLetterGuessing(landedSegment);
        });
    }
}

// Handles letter guessing
void GameController::startLetterGuessing(const QString &landedSegment) {

    if (!gameActive || remainingTime <= 0 || letterDialogOpen) return;

    letterDialogOpen = true;

    auto askForLetter = std::make_shared<std::function<void()>>();

    *askForLetter = [this, landedSegment, askForLetter]() {
        if (!gameActive || remainingTime <= 0) {
            letterDialogOpen = false;
            return;
        }

        QInputDialog *dialog = new QInputDialog(this);
        dialog->setWindowTitle("Guess a Letter");
        dialog->setLabelText("Enter a letter (non-vowel only):");
        dialog->setTextValue("");
        dialog->setInputMode(QInputDialog::TextInput);
        dialog->setModal(true);

        activeDialogs.append(dialog);

        connect(dialog, &QInputDialog::textValueSelected, this, [=](const QString &guess) {
            dialog->deleteLater();
            activeDialogs.removeOne(dialog);

            letterDialogOpen = false;

            QChar letter = guess.isEmpty() ? QChar() : guess[0].toUpper();

            // Validation in order to guess a single constant, any other guess is invalid and the user will be prompted to guess again
            if (guess.length() != 1) {
                showWarningAndRetry("Invalid Input", "Please enter only one letter.", *askForLetter, true);
                return;
            }

            if (!letter.isLetter()) {
                showWarningAndRetry("Invalid Input", "Enter a single letter (A-Z).", *askForLetter, true);
                return;
            }

            if (QString("AEIOU").contains(letter)) {
                showWarningAndRetry("Invalid Letter", "Vowels are not allowed!", *askForLetter, true);
                return;
            }

            // if the user attempts to guess a letter previously guessed, they will be prompted to guess another letter
            if (guessedLetters.contains(letter)) {
                showWarningAndRetry("Already Guessed", "You already guessed that letter!", *askForLetter, true);
                return;
            }

            guessedLetters.insert(letter);

            // Update guessed letters in the text box on the game screen
            QString lettersText = "Guessed Letters: ";
            for (auto l : guessedLetters)
                lettersText += QString(l) + " ";
            guessedLettersBox->setText(lettersText);


            if (phraseHandler->guessLetter(letter)) {
                updateDisplayedPhrase();
                handleWheelReward(landedSegment);

                if (phraseHandler->isComplete()) {
                    endGame("You Win!", "You guessed the full phrase!");
                }
            } else {
                handleIncorrectGuess(landedSegment);
            }
            letterDialogOpen = false;
        });

        dialog->open();
    };

    (*askForLetter)();
}

// Helper functions
void GameController::showWarningAndRetry(const QString &title, const QString &text, std::function<void()> retry, bool retryDialog = false) {
    QMessageBox *msg = new QMessageBox(this);
    msg->setIcon(QMessageBox::Warning);
    msg->setWindowTitle(title);
    msg->setText(text);
    activeDialogs.append(msg);

    connect(msg, &QDialog::finished, this, [=]() {
        activeDialogs.removeOne(msg);
        if (retryDialog && retry) {
            QTimer::singleShot(0, this, retry);  // only retry when desired
        }
    });

    msg->open();
}

void GameController::handleWheelReward(const QString &landedSegment) {
    if (landedSegment.contains("gem")) {
        int gemAmount = landedSegment.split(" ")[0].toInt();
        playerGems.addGems(gemAmount);

    } else if (landedSegment == "Free Hint") {
        freeHintsCount++;
        freeHintsLabel->setText("Free Hints: " + QString::number(freeHintsCount));
    }
}

void GameController::handleIncorrectGuess(const QString &landedSegment) {

    if (landedSegment == "-5 seconds") {
        remainingTime -= 5;
    } else if (landedSegment == "-10 seconds") {
        remainingTime -= 10;
    }

    // Always show that the letter is not in the phrase
    showWarningAndRetry("Incorrect", "The letter is not in the phrase.", nullptr, false);

    if (remainingTime < 0) remainingTime = 0;

    updateTimerLabel();

    if (remainingTime == 0) {
        if (wheel) wheel->stopSpin();
        endGame("Time's Up!", "You ran out of time! Do you want to start a new game?");
    }
}

// Timer functions
void GameController::updateTimerLabel() {
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;
    timerLabel->setText(QString("Time: %1:%2")
                            .arg(minutes)
                            .arg(seconds, 2, 10, QChar('0')));
}

void GameController::initializePhrase() {
    PhraseLibrary library;

    // Pick a random phrase
    Phrase selectedPhrase = library.getRandomPhrase(difficulty == 0 ? "easy" : "hard");

    QString phrase = QString::fromStdString(selectedPhrase.text);
    QString category = QString::fromStdString(selectedPhrase.category);

    if (categoryLabel) {
        categoryLabel->setText("Category: " + category);
    }

    if (phraseHandler) {
        delete phraseHandler;
        phraseHandler = nullptr;
    }

    phraseHandler = new PhraseHandler(phrase);
    displayedPhrase = phraseHandler->getDisplayedPhrase();

    // Reset hint tracking for this new phrase
    currentHintIndex = 0;

    // Load hints directly from the selectedPhrase object
    hintsForCurrentPhrase.clear();
    for (const std::string &hint : selectedPhrase.hints) {
        hintsForCurrentPhrase.append(QString::fromStdString(hint));
    }
}


void GameController::updateDisplayedPhrase()
{
    if (!phraseLabel || !phraseHandler) return;

    displayedPhrase = phraseHandler->getDisplayedPhrase();

    // Display using monospace font and avoid HTML collapsing spaces
    phraseLabel->setText(displayedPhrase);
    phraseLabel->setStyleSheet("font-family: monospace; font-size: 30px; font-weight: bold;");
}

void GameController::updateTimer() {

    if (remainingTime < 12) {
        timerLabel->setStyleSheet(
            "font-size: 18px; font-weight: bold; color: red;"
            );
    } else {
        timerLabel->setStyleSheet(
            "font-size: 18px; font-weight: bold; color: #8F0774;"
            );
    }

    if (remainingTime <= 0) {
        gameTimer->stop();
        closeAllDialogs();

        // Reveal the full phrase if timer runs out
        if (phraseHandler) {
            phraseHandler->revealPhrase();
            updateDisplayedPhrase();
        }

        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Time's Up!",
            "You ran out of time!\n\nThe phrase was:\n\n\""
                + phraseHandler->getOriginalPhrase() +
                "\"\n\nDo you want to start a new game?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::Yes) {
            startNewGame();
        } else {
            returnToMainMenu(false);
        }

        return;
    }

    remainingTime--;

    updateTimerLabel();
}

// Initlaize labels
void GameController::setUpLabels() {

    // Category label
    categoryLabel = new QLabel("Category: ", this);
    categoryLabel->setAlignment(Qt::AlignCenter);
    categoryLabel->setStyleSheet("font-size: 18px; color: #8F0774; font-weight: bold;");

    initializePhrase();

    // Phrase label
    phraseLabel = new QLabel(displayedPhrase, this);
    phraseLabel->setAlignment(Qt::AlignCenter);
    phraseLabel->setWordWrap(true);
    phraseLabel->setStyleSheet("font-size: 30px; font-weight: bold;");

    // Gems label
    gemsLabel = new QLabel("💎 Gems: " + QString::number(playerGems.getGems()), this);
    gemsLabel->setAlignment(Qt::AlignCenter);
    gemsLabel->setFixedWidth(100);
    gemsLabel->setStyleSheet("font-size: 18px; color: #8F0774; font-weight: bold;");

    connect(&playerGems, &PlayerGems::gemsChanged, this, [=](int newGems){
        gemsLabel->setText("💎 Gems: " + QString::number(newGems));
    });

    // Timer label
    int initialTime = (difficulty == 0) ? 120 : 180; // 20 or 180 seconds
    remainingTime = initialTime;

    timerLabel = new QLabel("", this);
    updateTimerLabel();
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet("font-size: 18px; color: #8F0774; font-weight: bold;");

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameController::updateTimer);
    //gameTimer->start(1000); // tick every second

    // Free hints label
    freeHintsLabel = new QLabel("Free Hints: " + QString::number(freeHintsCount), this);
    freeHintsLabel->setAlignment(Qt::AlignCenter);
    freeHintsLabel->setFixedWidth(120);
    freeHintsLabel->setStyleSheet("font-size: 18px; color: #8F0774; font-weight: bold;");

    // Wheel result label
    wheelResultLabel = new QLabel("", this);
    wheelResultLabel->setAlignment(Qt::AlignCenter);
    wheelResultLabel->setStyleSheet("font-size: 16px; color: #8F0774; font-weight: bold;");
}

// Handle UI set up
void GameController::setUpUI() {

    // Guessed letters box
    guessedLettersBox = new QLineEdit(this);
    guessedLettersBox->setReadOnly(true);
    guessedLettersBox->setAlignment(Qt::AlignCenter);
    guessedLettersBox->setStyleSheet("font-size: 15px;");
    guessedLettersBox->setFixedWidth(450);
    guessedLettersBox->setFixedHeight(26);

    setUpLabels();
    setUpWheel();

    // Left buttons
    mainMenuButton = new QPushButton("Main Menu", this);
    helpButton = new QPushButton("Help", this);
    mainMenuButton->setFixedSize(80, 30);
    helpButton->setFixedSize(80, 30);

    connect(mainMenuButton, &QPushButton::clicked, this, &GameController::returnToMainMenu);
    connect(helpButton, &QPushButton::clicked, this, &GameController::openHelpScreen);

    QVBoxLayout *leftButtonsLayout = new QVBoxLayout();
    leftButtonsLayout->addStretch();
    leftButtonsLayout->addWidget(mainMenuButton, 0, Qt::AlignCenter);
    leftButtonsLayout->addWidget(helpButton, 0, Qt::AlignCenter);
    leftButtonsLayout->addStretch();
    leftButtonsLayout->setSpacing(10);

    // --- Wheel + guessed letters ---
    QVBoxLayout *wheelLayout = new QVBoxLayout();
    wheelLayout->addWidget(wheel, 0, Qt::AlignCenter);
    wheelLayout->addWidget(wheelResultLabel, 0, Qt::AlignCenter);
    wheelLayout->addSpacing(-5);
    wheelLayout->addWidget(guessedLettersBox, 0, Qt::AlignCenter);
    wheelLayout->addStretch();
    wheelLayout->setAlignment(Qt::AlignCenter);

    // --- Labels container for Gems and Free Hints ---
    QVBoxLayout *labelsLayout = new QVBoxLayout();
    labelsLayout->addSpacing(140);;  // Push labels down to center
    labelsLayout->addWidget(gemsLabel, 0, Qt::AlignCenter);
    labelsLayout->addWidget(freeHintsLabel, 0, Qt::AlignCenter);
    labelsLayout->addStretch();  // Push labels up to center
    labelsLayout->setSpacing(10);

    // --- Wheel row ---
    QHBoxLayout *wheelRow = new QHBoxLayout();
    wheelRow->addLayout(leftButtonsLayout);
    wheelRow->addSpacing(20);
    wheelRow->addLayout(wheelLayout);
    wheelRow->addSpacing(20);
    wheelRow->addLayout(labelsLayout);

    // --- Bottom action buttons ---
    spinButton = new QPushButton("Spin Wheel", this);
    buyVowelButton = new QPushButton("Buy Vowel (3 gems)", this);
    buyHintButton = new QPushButton("Buy Hint (5 gems)", this);
    solveButton = new QPushButton("Solve Phrase", this);

    // Set button sizes
    spinButton->setFixedSize(145, 40);
    buyVowelButton->setFixedSize(145, 40);
    buyHintButton->setFixedSize(145, 40);
    solveButton->setFixedSize(145, 40);

    // Set styles
    spinButton->setStyleSheet(
        "background-color: #bb129b;"
        "color: #efd4ed;"
        "font-family: Verdana;"
        "font-weight: bold;"
        "font-size: 16px;"
        "border: 4px solid #5C1F53;"
        "border-radius: 5px;"
        );
    buyVowelButton->setStyleSheet(
        "background-color: #5C1F53;"
        "color: white;"
        "font-family: Verdana;"
        "font-size: 12px;"
        "border-radius: 5px;"
        );
    buyHintButton->setStyleSheet(
        "background-color: #5C1F53;"
        "color: white;"
        "font-family: Verdana;"
        "font-size: 12px;"
        "border-radius: 5px;"
        );
    solveButton->setStyleSheet(
        "background-color:#5C1F53;"
        "color: white;"
        "font-family: Verdana;"
        "font-size: 12px;"
        "border-radius: 5px;"
        );

    // Connect buttons
    connect(spinButton, &QPushButton::clicked, this, &GameController::spinWheel);
    connect(buyVowelButton, &QPushButton::clicked, this, &GameController::buyVowel);
    connect(buyHintButton, &QPushButton::clicked, this, &GameController::buyHint);
    connect(solveButton, &QPushButton::clicked, this, &GameController::solvePhrase);

    // Layout for bottom buttons
    QHBoxLayout *bottomButtons = new QHBoxLayout();
    bottomButtons->addStretch();
    bottomButtons->addWidget(spinButton);
    bottomButtons->addWidget(buyVowelButton);
    bottomButtons->addWidget(buyHintButton);
    bottomButtons->addWidget(solveButton);
    bottomButtons->addStretch();
    bottomButtons->setSpacing(15);

    // --- Main layout ---
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(categoryLabel);
    mainLayout->addWidget(phraseLabel);
    mainLayout->addLayout(wheelRow);
    mainLayout->addSpacing(15); // spacing to lift guessed letters above buttons
    mainLayout->addLayout(bottomButtons);
    mainLayout->setSpacing(20);

    setLayout(mainLayout);

    // --- Start message box before timer ---
    QTimer::singleShot(0, this, [this]() {
        QMessageBox *msg = new QMessageBox(this);
        msg->setWindowTitle("How to Play");
        msg->setText(
            "Click the \"Spin Wheel\" button in the bottom left corner "
            "to begin guessing letters and play the game."
            );
        msg->setIcon(QMessageBox::Information);
        msg->setStandardButtons(QMessageBox::Ok);

        activeDialogs.append(msg);

        connect(msg, &QDialog::finished, this, [=]() {
            activeDialogs.removeOne(msg);
            msg->deleteLater();

            // Start timer AFTER user clicks OK
            if (gameTimer && !gameTimer->isActive())
                gameTimer->start(1000);
        });

        msg->open();
    });
}

// Game actions
void GameController::spinWheel()
{
    if (wheel) wheel->spinWheel();
}

void GameController::buyVowel() {

    gameActive = false;

    // Checks whether the user has enough gems to purchase a vowel
    if (wheel)
        wheel->stopSpin();

    if (playerGems.getGems() < 3) {
        showWarningAndRetry("Not enough gems", "Need 3 gems!", nullptr, false);
    } else {

        playerGems.spendGems(3);

        auto askVowel = std::make_shared<std::function<void()>>();

        *askVowel = [this, askVowel]() {
            QInputDialog *dialog = new QInputDialog(this);
            dialog->setWindowTitle("Buy a Vowel");
            dialog->setLabelText("Enter a vowel (A, E, I, O, U):");
            dialog->setTextValue("");
            dialog->setInputMode(QInputDialog::TextInput);
            dialog->setModal(true);

            activeDialogs.append(dialog);

            connect(dialog, &QInputDialog::textValueSelected, this, [=](const QString &guess) {
                dialog->deleteLater();
                activeDialogs.removeOne(dialog);

                // Validation for guessing a vowel
                if (guess.isEmpty() || guess.length() != 1 || !guess[0].isLetter()) {
                    showWarningAndRetry("Invalid Input", "Enter a single vowel.", *askVowel, true);
                    return;
                }

                QChar letter = guess[0].toUpper();

                if (!QString("AEIOU").contains(letter)) {
                    showWarningAndRetry("Invalid Input", "That's not a vowel.", *askVowel, true);
                    return;
                }

                if (guessedLetters.contains(letter)) {
                    showWarningAndRetry("Already Guessed", "This letter was already guessed.", *askVowel, true);
                    return;
                }

                guessedLetters.insert(letter);;

                QString lettersText = "Guessed Letters: ";
                for (auto l : guessedLetters) lettersText += QString(l) + " ";
                guessedLettersBox->setText(lettersText);

                // Guess the letter
                if (phraseHandler->guessLetter(letter)) {
                    updateDisplayedPhrase();
                    if (phraseHandler->isComplete()) {
                        showWarningAndRetry("You Win!", "You guessed the full phrase!", nullptr, false);
                    }
                } else {
                    showWarningAndRetry("Incorrect", "The letter is not in the phrase.", nullptr, false);
                }
            });

            dialog->open();
        };
        (*askVowel)();
    }
    gameActive = true;
}

void GameController::buyHint() {
    gameActive = false;

    if (wheel)
        wheel->stopSpin();

    // Max 3 hints per round
    const int maxHints = 3;

    // Already used all 3 hints?
    if (currentHintIndex >= maxHints) {
        showWarningAndRetry("No more hints", "You have already used all 3 hints for this phrase.", nullptr, false);
        gameActive = true;
        return;
    }

    // Using a free hint
    if (freeHintsCount > 0) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Use Free Hint",
            "You have a free hint! Do you want to use it?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::Yes) {
            freeHintsCount--;
            freeHintsLabel->setText("Free Hints: " + QString::number(freeHintsCount));

            QString hintText = hintsForCurrentPhrase[currentHintIndex];
            currentHintIndex++;

            showWarningAndRetry("Hint", hintText, nullptr, false);
        }
    }

    // No free hint since not enough gems
    else if (playerGems.getGems() < 5) {
        showWarningAndRetry("Not enough gems", "You need 5 gems or a free hint!", nullptr, false);
    }

    // Buying a hint with gems
    else {
        playerGems.spendGems(5);

        QString hintText = hintsForCurrentPhrase[currentHintIndex];
        currentHintIndex++;

        showWarningAndRetry("Hint:", hintText, nullptr, false);
    }

    gameActive = true;
}


void GameController::solvePhrase()
{
    if (!phraseHandler || !gameActive) return;  // don't proceed if game ended

    // Stop the game
    gameActive = false;

    if (gameTimer->isActive())
        gameTimer->stop();

    if (wheel)
        wheel->stopSpin();

    closeAllDialogs();          // close any open dialogs
    letterDialogOpen = false;   // reset letter input flag

    bool ok;
    QString playerInput = QInputDialog::getText(this, "Solve Phrase",
                                                "Enter the full phrase:",
                                                QLineEdit::Normal, "", &ok);

    if (!ok || playerInput.isEmpty()) {
        gameActive = true;       // resume game if player cancels
        if (gameTimer) gameTimer->start(1000);
        return;
    }

    QString inputUpper = playerInput.toUpper();
    QString phraseUpper = phraseHandler->getOriginalPhrase().toUpper();

    if (inputUpper == phraseUpper) {
        phraseHandler->revealPhrase();
        updateDisplayedPhrase();

        // Custom end-game dialog
        QMessageBox *msg = new QMessageBox(this);
        msg->setWindowTitle("You Won!");
        msg->setText("Congratulations! You guessed the full phrase correctly!");
        msg->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msg->button(QMessageBox::Ok)->setText("Return to Main Menu");
        msg->button(QMessageBox::Cancel)->setText("Exit Game");

        activeDialogs.append(msg);
        connect(msg, &QDialog::finished, this, [=](int result){
            activeDialogs.removeOne(msg);
            msg->deleteLater();

            if (result == QMessageBox::Ok)
                returnToMainMenu(true);
            else
                qApp->quit();
        });

        msg->open();

    } else {
        remainingTime -= 5; // an incorrect guess costs 5 seconds of users time
        if (remainingTime < 0) remainingTime = 0;
        updateTimerLabel();

        // Incorrect guess
        showWarningAndRetry("Incorrect", "Sorry, that was not correct. Keep playing!", nullptr, false);
        gameActive = true;
        if (gameTimer) gameTimer->start(1000);
    }
}

// Utility Functions
void GameController::closeAllDialogs() {
    for (QDialog* dlg : activeDialogs) {
        if (dlg) {
            dlg->close();
            dlg->deleteLater();
        }
    }
    activeDialogs.clear();
}

void GameController::startNewGame() {

    // 1. Reset guessed letters
    guessedLetters.clear();
    guessedLettersBox->clear();

    // 2. Reset free hints
    freeHintsCount = 0;
    freeHintsLabel->setText("Free Hints: 0");

    // 3. Reset wheel result label
    wheelResultLabel->setText("");

    // 4. Reset phrase
    initializePhrase();      // picks a new random phrase
    updateDisplayedPhrase(); // updates the UI

    // 5. Reset timer based on difficulty
    remainingTime = (difficulty == 0) ? 120 : 180;
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;
    timerLabel->setText(QString("Time: %1:%2")
                            .arg(minutes)
                            .arg(seconds, 2, 10, QChar('0')));

    // 6. Restart the timer
    if (gameTimer->isActive()) gameTimer->stop();

    gameTimer->start(1000);

    // 7. Reset player gems
    playerGems.resetGems(0);
}


void GameController::returnToMainMenu(bool skipConfirmation) {

    if (gameTimer && gameTimer->isActive())
        gameTimer->stop();

    gameActive = false;

    if (wheel)
        wheel->stopSpin();

    // Handles exiting the game and returning to the home screen
    if (!skipConfirmation) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Exit Game",
            "Are you sure you want to exit the game?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::No) {
            // User cancelled exit, just continue the game
            gameActive = true;
            if (gameTimer && !gameTimer->isActive())
                gameTimer->start(1000);
            return;
        }
    }

    closeAllDialogs();

    MainController *mainMenu = new MainController();
    mainMenu->setWindowTitle("Spin & Solve");
    mainMenu->show();

    this->close();
}


void GameController::openHelpScreen()
{
    Help *helpScreen = new Help(this);
    helpScreen->setWindowModality(Qt::ApplicationModal);
    helpScreen->show();
}

void GameController::endGame(const QString &title, const QString &message)
{
    // Stop timer
    if (gameTimer->isActive())
        gameTimer->stop();

    // Close all dialogs
    closeAllDialogs();

    // Ask player what to do
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        title,
        message,
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes)
        startNewGame();
    else
        returnToMainMenu(false);
}


void GameController::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap background(":/images/images/background.png");
    painter.drawPixmap(rect(), background);

    QWidget::paintEvent(event);
}
