#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include "Database.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
private slots:
    void unfixDefect();
    void fixDefect();
    void increaseRepairCost();
    void displayAllDefects();
    void displayUnfixedDefects();
    void displayFixedDefects();
    void saveToFile();

private:
    Records::Database employeeDB;
    QTextEdit *outputTextEdit;
    QPushButton *saveBut;
    void displayMenu();
};

#endif // MAINWINDOW_H



