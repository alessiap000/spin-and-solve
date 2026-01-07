#ifndef WHEEL_H
#define WHEEL_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>

// Custom QGraphicsPixmapItem with rotation property for animation
class WheelItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)

public:
    explicit WheelItem(const QPixmap &pixmap)
        : QGraphicsPixmapItem(pixmap) {}
};

// Wheel widget containing the spinning wheel and arrow graphics
class Wheel : public QWidget {
    Q_OBJECT

public:
    explicit Wheel(QWidget *parent = nullptr);

    void spinWheel();
    void stopSpin();
    int calculateSegment(double angle) const;

signals:
    void landedSegment(int index);

private slots:
    void handleAnimationEnd();

private:
    // Graphics components
    QGraphicsScene *scene = nullptr;
    QGraphicsView *view = nullptr;
    WheelItem *wheelItem = nullptr;
    QGraphicsPixmapItem *arrowItem = nullptr;

    // Animation
    QPropertyAnimation *animation = nullptr;

    // Spin properties
    int endAngle = 0;
    int numSegments = 8;
    double segmentAngle = 360.0 / numSegments;
    double currentRotation = 0.0;
    bool isSpinning = false;

    // Helper functions
    void setUpWheelItem();
    void setUpArrow();
};

#endif // WHEEL_H
