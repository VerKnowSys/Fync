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
        FileWatchersManager(const QString& sourceDir);
        void scanDir(QDir dir);
        void loadSettings(); /* load app settings */
        QStringList removeFromList(QStringList& list, const QStringList& toDelete);

    private:
        QStringList files;
        QString baseCWD, fullDestinationLog;
        QDateTime lastModified;
        QSettings settings;

    public slots:
        void fileChangedSlot(const QString& file);
        void dirChangedSlot(const QString& dir);

};

#endif
