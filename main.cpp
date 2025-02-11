#include <QCoreApplication>
#include <iostream>
#include "modifprog.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string inputMask, outputPath;
    int interval;
    bool isdeleteInput, isOnce, writeType;
    uint64_t binValue;
    QStringList files;

    std::cout << "Enter Mask: ";
    std::cin >> inputMask;

    std::cout << "Delete input files? (1/0): ";
    std::cin >> isdeleteInput;

    std::cout << "Enter output path: ";
    std::cin >> outputPath;

    std::cout << "Run the program once/timer? (1/0): ";
    std::cin >> isOnce;

    if(!isOnce) {
        std::cout << "Enter timer (ms): ";
        std::cin >> interval;
    }

    std::cout << "Filename duplicates. overwrite/modificate? (1/0)";
    std::cin >> writeType;

    std::cout << "Enter modification value: ";
    std::cin >> std::hex >> binValue;

    ModifProg modifProg(QString::fromStdString(inputMask), QString::fromStdString(outputPath), isdeleteInput, isOnce, interval, binValue, writeType);
    if (!isOnce) {
        modifProg.startTimer();
    } else {
        modifProg.findFiles(files);
        modifProg.modificateFiles(files, binValue);
        a.quit();
    }

    return a.exec();
}
