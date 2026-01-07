#include "MainController.h"

#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    // Initialize the Qt application
    QApplication app(argc, argv);

    // Create the main game window
    MainController window;
    window.setWindowTitle("Spin & Solve");
    window.setFixedSize(750, 550);
    window.show();

    return app.exec();
}
