#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MainController : public QWidget {
    Q_OBJECT

public:
    explicit MainController(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QPushButton *startButton;
    QPushButton *instructionsButton;

private slots:
    void startGame();
    void showInstructions();
};

#endif // MAINCONTROLLER_H
