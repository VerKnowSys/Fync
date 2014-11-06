/**
 *  @author dmilith
 *
 *   © 2014 - VerKnowSys
 *
 */

#include "file_watchers_manager.h"


FileWatchersManager::FileWatchersManager(const QString& sourceDir) {

    logDebug() << "Starting recursive watch on dir:" << sourceDir;
    this->baseCWD = sourceDir;
    // this->fullDestinationLog = fullDestinationLog; /* f.e: someuser@remotehost:/remote/path */

    // loadSettings();
    // QSettings settings;

    // signal(SIGPIPE, SIG_IGN); /* ignore SIGPIPE error */

    /* connect hooks to invokers */
    connect(this, SIGNAL(fileChanged(QString)), this, SLOT(fileChangedSlot(QString)));
    connect(this, SIGNAL(directoryChanged(QString)), this, SLOT(dirChangedSlot(QString)));
    scanDir(QDir(sourceDir)); /* will fill up manager 'files' field */
}


void FileWatchersManager::loadSettings() {
    QSettings settings;
}


// void FileWatchersManager::callSuccess() {
//     logDebug() << "Success called";
// }


void FileWatchersManager::scanDir(QDir dir) {
    long start = QDateTime::currentMSecsSinceEpoch();
    logDebug() << "Scanning:" << dir.absolutePath();

    // this->oldFiles = this->files;
    // this->files = QStringList();
    // for (int index = 0; index < files.length(); index++) {
    //     // removePath(files.at(index));
    //     files.removeAt(index);
    // }

    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QDirIterator it(dir, QDirIterator::Subdirectories);
    // files << dir.absolutePath(); /* required for dir watches */

    while (it.hasNext())
        files << it.next();
    files.removeDuplicates();

    addPaths(files);
    logDebug() << "Total dirs on watch for dir:" << baseCWD << "-" << QString::number(files.size());
    long end = QDateTime::currentMSecsSinceEpoch();
    logDebug() << "Scan took:" << QString::number(end - start) << "ms";
    // logDebug() << "Ready.";
}


void FileWatchersManager::fileChangedSlot(const QString& file) {
    logInfo() << "File changed slot called for:" << file;

    /* compare file name and modification date. Ignore doubles */
    // if ((last != file) || (QFileInfo(file).created() != this->lastModified)) {
    //     this->lastModified = QFileInfo(file).created();
    //     this->last = file;
    //     // logDebug() << "Invoked copy to remote host for file:" << file;
    //     // copyFilesToRemoteHost(QStringList(file));
    // }
}


// QStringList FileWatchersManager::removeFromList(QStringList& list, const QStringList& toDelete) {
//     QStringListIterator i(toDelete);
//     while (i.hasNext()) {
//         list.removeAll(i.next());
//     }
//     return list;
// }


void FileWatchersManager::dirChangedSlot(const QString& dir) {
    long start = QDateTime::currentMSecsSinceEpoch();
    logDebug() << "Dir changed:" << dir;
    // scanDir(dir);
    if (not QDir(dir).exists()) {
        logDebug() << "Dir has gone. Assuming directory deletion of:" << dir;
        removePath(dir);
        // scanDir(QDir(dir + "/.."));
    } else {
        logDebug() << "Dir changed:" << dir;
        scanDir(QDir(dir)); /* don't scan non existent directories */
    }
    //     /* show number of differences */
    //     auto diffs = abs(files.length() - oldFiles.length());
    //     logDebug() << "Found" << diffs << "change(s)";

    //     if (diffs > 0) {
    //         /* scan for new files by file list diff */
    //         QStringList gatheredList = QStringList();
    //         Q_FOREACH(QString nextOne, files) {
    //             if (QFile::exists(nextOne)) {
    //                 if (not QDir(nextOne).exists()) {
    //                     // logDebug() << "Traversing next file:" << nextOne;
    //                     if (not oldFiles.contains(nextOne)) {
    //                         logDebug() << "New file?:" << nextOne;
    //                         gatheredList << nextOne;
    //                     }
    //                 }
    //             } else {
    //                 logDebug() << "File was REMOVED:" << nextOne;
    //                 gatheredList << nextOne;
    //             }
    //         }
    //     }
    // }
    long end = QDateTime::currentMSecsSinceEpoch();
    logDebug() << "Dir changed slot took:" << QString::number(end - start) << "ms";
}
