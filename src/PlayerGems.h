#ifndef PLAYERGEMS_H
#define PLAYERGEMS_H

#include <QObject>
#include <algorithm>

class PlayerGems : public QObject {
    Q_OBJECT

private:
    int gems;

public:
    explicit PlayerGems(int initialGems = 10, QObject *parent = nullptr)
        : QObject(parent), gems(initialGems) {}

    int getGems() const { return gems; }

public slots:
    void addGems(int value) { gems += value; emit gemsChanged(gems); }
    void spendGems(int value) { gems = std::max(0, gems - value); emit gemsChanged(gems); }
    void resetGems(int value = 0) { gems = value; emit gemsChanged(gems); }
    void setGems(int value) { gems = value; emit gemsChanged(gems); }

signals:
    void gemsChanged(int newAmount);
};

#endif // PLAYERGEMS_H

