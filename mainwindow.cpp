#include "mainwindow.h"
#include <QVBoxLayout>
#include <QToolBar>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDir>

using namespace Records;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Defect Database");
    setMinimumSize(650, 200);

    outputTextEdit = new QTextEdit(this);
    outputTextEdit->setReadOnly(true);

    saveBut = new QPushButton("Save to File", this);
    connect(saveBut, &QPushButton::clicked, this, &MainWindow::saveToFile);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(outputTextEdit);
    layout->addWidget(saveBut);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    QToolBar *toolBar = addToolBar("Main Toolbar");

    QAction *unfixDefectAction = toolBar->addAction("Add Defect");
    connect(unfixDefectAction, &QAction::triggered, this, &MainWindow::unfixDefect);

    QAction *fixDefectAction = toolBar->addAction("Fix Defect");
    connect(fixDefectAction, &QAction::triggered, this, &MainWindow::fixDefect);

    QAction *increaseRepairCostAction = toolBar->addAction("Increase Repair Cost");
    connect(increaseRepairCostAction, &QAction::triggered, this, &MainWindow::increaseRepairCost);

    QAction *displayAllDefectsAction = toolBar->addAction("Display All Defects");
    connect(displayAllDefectsAction, &QAction::triggered, this, &MainWindow::displayAllDefects);

    QAction *displayUnfixedDefectsAction = toolBar->addAction("Display Unfixed Defects");
    connect(displayUnfixedDefectsAction, &QAction::triggered, this, &MainWindow::displayUnfixedDefects);

    QAction *displayFixedDefectsAction = toolBar->addAction("Display Fixed Defects");
    connect(displayFixedDefectsAction, &QAction::triggered, this, &MainWindow::displayFixedDefects);

    Database employeeDB;
    //displayMenu();

}

void MainWindow::displayMenu()
{

    QStringList items;
    items << "Add a new Defect "
          << "Exclude Defect(was fixed)"
          << "Increase price"
          << "List all Defects"
          << "List unfixed Defects"
          << "List fixed Defects"
          << "Quit";

    QString menuText = items.join("\n");
    outputTextEdit->setPlainText(menuText);
}

void MainWindow::unfixDefect()
{
    bool ok;

    int model = QInputDialog::getInt(this, "Add Defect", "Model Code:", 0, 0, 1000, 1, &ok);
    if (!ok) return;

    QString description = QInputDialog::getMultiLineText(this, "Add Defect", "Description:", "", &ok);
    if (!ok) return;

    QString methods = QInputDialog::getMultiLineText(this, "Add Defect", "Repair methods:", "", &ok);
    if (!ok) return;

    try {
        employeeDB.addDefect(model, description.toStdString(), methods.toStdString());
    } catch (const std::exception& ex) {
        QMessageBox::critical(this, "Error", "Unable to add new Defect");
    }
}


void MainWindow::fixDefect()
{
    bool ok;

    int code = QInputDialog::getInt(this, "Fix defect", "Defect Code:", 0, 100, 150, 1, &ok);
    if (!ok) return;

    employeeDB.getDefect(code).fix();

}

void MainWindow::increaseRepairCost()
{
    bool ok;

    int code = QInputDialog::getInt(this, "Increase Repair Cost", "Defect Code:", 0, 100, 150, 1, &ok);
    if (!ok) return;

    int pr = QInputDialog::getInt(this, "Increase Repair Cost", "Cost:", 0, 0, 1000, 1, &ok);
    if (!ok) return;

    employeeDB.getDefect(code).incRepairCost(pr);
}

void MainWindow::displayAllDefects()
{
    QString all_defects = employeeDB.displayAllDefects();
    outputTextEdit->setPlainText(all_defects);
}

void MainWindow::displayUnfixedDefects()
{
    QString unfixed_defects = employeeDB.displayUnfixed();
    outputTextEdit->setPlainText(unfixed_defects);
}

void MainWindow::displayFixedDefects()
{
    QString fixed_defects = employeeDB.displayFixed();
    outputTextEdit->setPlainText(fixed_defects);
}

void MainWindow::saveToFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", QDir::homePath(), "Text Files (*.txt);;All Files (*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            QString text = employeeDB.displayAllDefects();
            out << text;
            file.close();
        } else {
            QMessageBox::critical(this, "Error", "Unable to open the file for writing.");
        }
    }
}
