
// Database.cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include "Database.h"


using namespace std;
namespace Records {
Database::Database() {
    mNextSlot = 0;
    mNextDefectCode = kFirstDefectCode;
}

Database::~Database() {
}

Defect& Database::addDefect(int inModel, std::string inDescription, string inRepairMethods) {
    if (mNextSlot >= kMaxDefects) {
        cerr << "There is no more spase to add the new defect!" << endl;
        throw exception();
    }

    Defect& theDefect = mDefects[mNextSlot++];
    theDefect.setDefectCode(mNextDefectCode++);
    theDefect.setModelCode(inModel);
    theDefect.setDescription(inDescription);
    theDefect.setRepairMethods(inRepairMethods);
    return theDefect;
}

Defect& Database::getDefect(int inCode) {
    for (int i = 0; i < mNextSlot; i++) {
        if (mDefects[i].getDefectCode() == inCode) {
            return mDefects[i];
        }
    }
    cerr << "No defect type with code " << inCode << endl;
    throw exception();
}

QString Database::displayAllDefects() {
    QString defects;
    for (int i = 0; i < mNextSlot; i++) {
        defects += mDefects[i].display();
    }
    return defects;
}

QString Database::displayFixed() {
    QString fixed_defects;
    for (int i = 0; i < mNextSlot; i++) {
        if(mDefects[i].getIsFixed()){
            fixed_defects += mDefects[i].display();
        }
    }
    return fixed_defects;
}

QString Database::displayUnfixed() {
    QString unfixed_defects;
    for (int i = 0; i < mNextSlot; i++) {
        if(!mDefects[i].getIsFixed()){
            unfixed_defects += mDefects[i].display();
        }
    }
    return unfixed_defects;

    // namespace Records
}
}
