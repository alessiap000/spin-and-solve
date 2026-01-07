#include "Wheel.h"

#include <QGraphicsPixmapItem>
#include <QVBoxLayout>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QtMath>
#include <QPropertyAnimation>

/*
 * The Wheel class handles the visual spinning wheel component,
 * including it's animation and the logic for determining results.
 */

Wheel::Wheel(QWidget *parent)
    : QWidget(parent),

    scene(new QGraphicsScene(this)),
    view(new QGraphicsView(scene, this)) {

    setUpWheelItem();
    setUpArrow();

    // Layout set up for displaying the wheel
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    // Create the spin animation
    animation = new QPropertyAnimation(wheelItem, "rotation", this);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    connect(animation, &QPropertyAnimation::finished, this, &Wheel::handleAnimationEnd);
}

// Loads the wheel image and positions it in the center of the screen
void Wheel::setUpWheelItem() {
    QPixmap wheelPixmap(":/images/images/pink.png");
    wheelItem = new WheelItem(wheelPixmap);

    const double cx = wheelPixmap.width() / 2.0;
    const double cy = wheelPixmap.height() / 2.0;

    // Set rotation origin to center of the wheel
    wheelItem->setTransformOriginPoint(cx, cy);

    // Center the wheel in the scene
    wheelItem->setPos(-cx, -cy);

    scene->addItem(wheelItem);

    // Set the scene for proper display
    scene->setSceneRect(-cx, -cy, wheelPixmap.width(), wheelPixmap.height());

    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    view->setAlignment(Qt::AlignCenter);
    view->scale(10, 10);
}

// Loads the arrow image that points to the resulting segment after the spin.
void Wheel::setUpArrow() {
    QPixmap arrowPixmap(":/images/images/arrow.png");
    arrowItem = new QGraphicsPixmapItem(arrowPixmap);

    // Place the arrow above the wheel
    arrowItem->setScale(0.5);
    arrowItem->setPos(-scene->width() / 2 + 130, -scene->height() / 2 - 20);

    scene->addItem(arrowItem);
}

// Starts the spinning animation for the wheel.
void Wheel::spinWheel() {
    if (isSpinning) return; // Prevents double spins

    isSpinning = true;

    // Randomize final wheel position after its rotation
    int fullRotations = 6;
    int randomAngle = QRandomGenerator::global()->bounded(360);

    endAngle = currentRotation + 360 * fullRotations + randomAngle;

    // Set the right animation parameters
    animation->setStartValue(currentRotation);
    animation->setEndValue(endAngle);
    animation->setDuration(4000);
    animation->start();
}

// Lended segment logic
void Wheel::handleAnimationEnd() {
    currentRotation = fmod(endAngle, 360.0); // Remember the last angle
    isSpinning = false;

    emit landedSegment(calculateSegment(currentRotation));
}

int Wheel::calculateSegment(double angle) const {
    const double arrowOffset = 45.0 / 2.0;

    double adjusted = fmod(angle + arrowOffset, 360.0);
    int index = static_cast<int>(adjusted / segmentAngle);

    return numSegments - 1 - index;
}

void Wheel::stopSpin() {
    if (!isSpinning) return; // nothing to stop

    if (animation && animation->state() == QAbstractAnimation::Running) {
        animation->stop(); // stop the animation immediately
    }

    // Mark as not spinning
    isSpinning = false;

    // Record current rotation of the wheel
    currentRotation = wheelItem->rotation();

    emit landedSegment(calculateSegment(currentRotation));
}
