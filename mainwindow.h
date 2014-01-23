#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "Jeux.h"
#include <QMessageBox>
#include <fstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots :
    void handleJouer();
    void handleGen();

private:
    Ui::MainWindow *ui;
    QMessageBox *popup2;
    bool is_readable(const std::string & file)
    {
        std::ifstream fichier(file.c_str());
        return !fichier.fail();
    }

    Jeux * m_jeux;
};

#endif // MAINWINDOW_H
