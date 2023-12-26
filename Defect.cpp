// Defect.cpp
#include "Defect.h"
#include <QString>
#include <QStringList>

using namespace std;

namespace Records {
Defect::Defect() {
    mDefectCode = -1;
    mModelCode = -1;
    mDescription = "";
    mRepairMethods = "";
    mRepairCost = kDefaultRepairCost;
    iFixed = false;
}

void Defect::incRepairCost(int inRaiseAmount) {
    setRepairCost(getRepairCost() + inRaiseAmount);
}

void Defect::decRepairCost(int inDemeritAmount) {
    setRepairCost(getRepairCost() - inDemeritAmount);
}

void Defect::fix() {
    iFixed = true;
}

void Defect::unfix() {
    iFixed = false;
}

// Accessors and setters implementation
void Defect::setDefectCode(int inDefectCode) {
    mDefectCode = inDefectCode;
}

int Defect::getDefectCode() {
    return mDefectCode;
}

void Defect::setModelCode(int inModelCode) {
    mModelCode = inModelCode;
}

int Defect::getModelCode() {
    return mModelCode;
}

void Defect::setDescription(std::string inDescription) {
    mDescription = inDescription;
}

std::string Defect::getDescription() {
    return mDescription;
}

void Defect::setRepairMethods(std::string inRepairMethods) {
    mRepairMethods = inRepairMethods;
}

std::string Defect::getRepairMethods() {
    return mRepairMethods;
}

void Defect::setRepairCost(double inRepairCost) {
    mRepairCost = inRepairCost;
}

double Defect::getRepairCost() {
    return mRepairCost;
}

bool Defect::getIsFixed() {
    return iFixed;
}
// void Defect::display() {
//     // cout << "Defect Code: " << getDefectCode() << endl;
//     // cout << "Model Code: " << getModelCode() << endl;
//     // cout << "Description: " << getDescription() << endl;
//     // cout << "Repair Methods: " << getRepairMethods() << endl;
//     // cout << "Repair Cost: $" << getRepairCost() << endl;
//     // cout << (iFixed ? "Fixed" : "defective") << endl;
//     // cout << endl;


// }

//}
QString Defect::display()
{
    QStringList info;
    info << "Defect Code: " + QString::number(getDefectCode())
         << "Model Code: " + QString::number(getModelCode())
         << "Description: " + QString::fromStdString(getDescription())
         << "Repair Methods: " + QString::fromStdString(getRepairMethods())
         << "Repair Cost: $" + QString::number(getRepairCost())
         << "" + QString::fromStdString((iFixed ? "Fixed" : "defective"))
         << "  \n";

    QString information = info.join("\n"); // Об'єднати елементи списку в рядок з роздільником "\n"
    return information;
}
}


