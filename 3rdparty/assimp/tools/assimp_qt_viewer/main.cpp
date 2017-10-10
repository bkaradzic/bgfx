/// \file   main.cpp
/// \brief  Start-up file which contain function "main".
/// \author smal.root@gmail.com
/// \date   2016
// Thanks to acorn89 for support.

// Header files, project.
#include "mainwindow.hpp"

// Header files, Qt.
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
