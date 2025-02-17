#include "modifprog.h"

ModifProg::ModifProg(const QString& inputMask, const QString& outputPath, bool isdeleteInput, bool isOnce, int interval, uint64_t binValue,  bool writeType)
    : inputMask(inputMask), outputPath(outputPath), isdeleteInput(isdeleteInput), isOnce(isOnce), interval(interval), binValue(binValue), writeType(writeType)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));
}

void ModifProg::startTimer()
{
    qDebug() << "Starting timer with interval:" << interval;
    timer->start(interval);
}

void ModifProg::onTimerTimeout()
{
    qDebug() << "Checking for files...";

    QStringList files;
    findFiles(files);

    if (!files.isEmpty()) {
        modificateFiles(files, binValue);
        qDebug() << "Files modified";
    } else {
        qDebug() << "No files found";
        timer->stop();
    }
}

void ModifProg::findFiles(QStringList &files) {
    QDir dir("../Input");

    if (!dir.exists()) {
        qDebug() << "Directory 'Input' not found";
        return;
    }

    QStringList filters;
    filters << inputMask;

    files = dir.entryList(filters, QDir::Files);
    if(files.empty()) {
        qDebug() << "Files not found";
    }

}

void ModifProg::modificateFiles(QStringList files, uint64_t binValue) {

    QDir dirOutput(outputPath);
    QDir dirInput("../Input");

    if(!dirOutput.exists()) {
        dirOutput.mkpath(outputPath);
    }

    for(const QString& file : files) {
        QFile inputFile(dirInput.filePath(file));
        QFile outputFile(dirOutput.filePath(file));

        qDebug() << file;

        if(!inputFile.open(QIODevice::ReadOnly)) {
            qDebug() << "File not found";
            return;
        }

        if(writeType){
            if(!outputFile.open(QIODevice::WriteOnly)) {
                qDebug() << "Output file not found";
                return;
            }
        } else {
            if(!outputFile.open(QIODevice::Append)) {
                qDebug() << "Output file not found";
                return;
            }
        }


        QDataStream input(&inputFile);
        QDataStream output(&outputFile);
        uint64_t value;

        while (!inputFile.atEnd()) {
            char byte;
            inputFile.read(&byte, 1);
            byte ^= (binValue & 0xFF);
            outputFile.write(&byte, 1);
        }

        qDebug() << "Input file size: " << inputFile.size();
        qDebug() << "Output file size: " << outputFile.size();

        inputFile.close();
        outputFile.close();

        isdeleteInput ? inputFile.remove() : 0;
    }
}
