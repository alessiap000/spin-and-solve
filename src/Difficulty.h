#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>

class Difficulty : public QDialog {
    Q_OBJECT

public:
    explicit Difficulty(QWidget *parent = nullptr);
    int getSelectedDifficulty() const; // 0 = Easy, 1 = Hard

private slots:
    void easyClicked();
    void hardClicked();

private:
    int difficulty;
};

#endif // DIFFICULTY_H
