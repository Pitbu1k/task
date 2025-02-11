#ifndef MODIFPROG_H
#define MODIFPROG_H

#include <QDir>
#include <QFile>
#include <QDataStream>
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

class ModifProg : QObject
{
    Q_OBJECT

private:
    QTimer* timer;
    QString inputMask, outputPath;
    int interval;
    bool isdeleteInput, isOnce, writeType;
    uint64_t binValue;

private slots:
    void onTimerTimeout();

public:
    ModifProg(const QString& inputMask, const QString& outputPath, bool IsdeleteInput,
              bool isOnce, int interval, uint64_t binValue, bool writeType);
    void startTimer();
    void findFiles(QStringList &files);
    void modificateFiles(QStringList files, uint64_t binValue);
};

#endif // MODIFPROG_H
