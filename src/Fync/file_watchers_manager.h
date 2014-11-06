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
        // void callSuccess();
        void scanDir(QDir dir);
        QStringList removeFromList(QStringList& list, const QStringList& toDelete);
        void loadSettings(); /* load app settings */

    // signals:
        /* slot to trigger icon type in tray */
        // void setWork(int state);


    private:
        QStringList files = QStringList(); //, oldFiles = QStringList();
        QString baseCWD, fullDestinationLog;
        QDateTime lastModified;
        QSettings settings;

    public slots:
        void fileChangedSlot(const QString& file);
        void dirChangedSlot(const QString& dir);

};

#endif
