// This file handles the spinning wheel component in the game

#include "Wheel.h"

#include <QGraphicsPixmapItem>
#include <QVBoxLayout>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QtMath>
#include <QPropertyAnimation>

/*
 * The Wheel class handles the visual spinning wheel component,
 * including its animation and the logic for determining which segment the wheel lands on.
 */

Wheel::Wheel(QWidget *parent)
    : QWidget(parent),
    scene(new QGraphicsScene(this)),
    view(new QGraphicsView(scene, this))
{
    setUpWheelItem();
    setUpArrow();

    // Layout set up for displaying the wheel
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    // Create the spin animation for smooth rotation
    animation = new QPropertyAnimation(wheelItem, "rotation", this);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    connect(animation, &QPropertyAnimation::finished, this, &Wheel::handleAnimationEnd);
}

// Loads the wheel image and positions it in the center of the screen
void Wheel::setUpWheelItem() {
    QPixmap wheelPixmap(":/images/images/pink.png"); // corrected path from resources
    wheelItem = new WheelItem(wheelPixmap);

    const double cx = wheelPixmap.width() / 2.0;
    const double cy = wheelPixmap.height() / 2.0;

    // Set rotation origin to the center of the wheel
    wheelItem->setTransformOriginPoint(cx, cy);

    // Center the wheel in the scene
    wheelItem->setPos(-cx, -cy);

    scene->addItem(wheelItem);

    // Set the scene rect and view for proper display
    scene->setSceneRect(-cx, -cy, wheelPixmap.width(), wheelPixmap.height());
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    view->setAlignment(Qt::AlignCenter);
    view->scale(10, 10); // optional scaling factor
}

// Loads the arrow image that points to the resulting segment after the spin
void Wheel::setUpArrow() {
    QPixmap arrowPixmap(":/images/images/arrow.png"); // corrected path from resources
    arrowItem = new QGraphicsPixmapItem(arrowPixmap);

    arrowItem->setScale(0.5);
    arrowItem->setPos(-scene->width() / 2 + 130, -scene->height() / 2 - 20);

    scene->addItem(arrowItem);
}

// Starts the spinning animation for the wheel
void Wheel::spinWheel() {
    if (isSpinning) return; // Prevent multiple spins

    isSpinning = true;

    // Randomize the final wheel position
    int fullRotations = 6; // number of full 360° rotations
    int randomAngle = QRandomGenerator::global()->bounded(360); // random offset

    endAngle = currentRotation + 360 * fullRotations + randomAngle;

    // Configure animation
    animation->setStartValue(currentRotation);
    animation->setEndValue(endAngle);
    animation->setDuration(4000); // 4 seconds spin
    animation->start();
}

// Handles logic after spin animation ends
void Wheel::handleAnimationEnd() {
    currentRotation = fmod(endAngle, 360.0); // store last angle
    isSpinning = false;

    // Emit the segment that the wheel landed on
    emit landedSegment(calculateSegment(currentRotation));
}

// Calculate which segment the wheel landed on based on the rotation angle
int Wheel::calculateSegment(double angle) const {
    const double arrowOffset = 45.0 / 2.0; // half segment offset

    double adjusted = fmod(angle + arrowOffset, 360.0);
    int index = static_cast<int>(adjusted / segmentAngle);

    return numSegments - 1 - index;
}

// Stops the wheel mid-spin (if needed)
void Wheel::stopSpin() {
    if (!isSpinning) return; // nothing to stop

    if (animation && animation->state() == QAbstractAnimation::Running) {
        animation->stop(); // immediately stop animation
    }

    isSpinning = false;

    // Record current rotation for future spins
    currentRotation = wheelItem->rotation();

    // Emit the segment the wheel stopped at
    emit landedSegment(calculateSegment(currentRotation));
}
