#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

// Displays the game's help screen
class Help : public QWidget {
    Q_OBJECT

public:
    explicit Help(QWidget *parent = nullptr);

private slots:
    void backToGame(); // Return to game

private:
    QPushButton *backButton;
    QLabel *helpLabel;
};

#endif // HELP_H
