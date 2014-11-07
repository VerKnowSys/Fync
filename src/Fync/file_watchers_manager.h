/**
 *  @author dmilith
 *
 *   © 2014 - VerKnowSys
 *
 */

#ifndef __FILE_WATCHERS_MANAGER_H__
#define __FILE_WATCHERS_MANAGER_H__


#include <iostream>
#include <fstream>
#include <sys/stat.h>

#ifdef __linux__
    #include <unistd.h>
#endif

#include "fync.h"

using namespace std;


class FileWatchersManager: public QFileSystemWatcher {
    Q_OBJECT

    public:
        FileWatchersManager(const QString& sourceDir, QFile* logger);
        void scanDir(QDir dir);

    private:
        QString baseCWD;
        QFile* loggerPipe;
        QMutex mutex;

    public slots:
        void fileChangedSlot(const QString& file);
        void dirChangedSlot(const QString& dir);

};

#endif
