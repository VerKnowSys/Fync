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

    /* connect hooks to invokers */
    connect(this, SIGNAL(fileChanged(QString)), this, SLOT(fileChangedSlot(QString)));
    connect(this, SIGNAL(directoryChanged(QString)), this, SLOT(dirChangedSlot(QString)));
    scanDir(QDir(sourceDir)); /* will fill up manager 'files' field */
}


void FileWatchersManager::loadSettings() {
    QSettings settings;
}


void FileWatchersManager::scanDir(QDir dir) {
    long start = QDateTime::currentMSecsSinceEpoch();
    logDebug() << "Scanning:" << dir.absolutePath();

    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QDirIterator it(dir, QDirIterator::Subdirectories);

    while (it.hasNext())
        files << it.next();
    files.removeDuplicates();

    addPaths(files);
    logDebug() << "Total dirs on watch for dir:" << baseCWD << "-" << QString::number(files.size());
    long end = QDateTime::currentMSecsSinceEpoch();
    logDebug() << "Scan took:" << QString::number(end - start) << "ms";
}


void FileWatchersManager::fileChangedSlot(const QString& file) {
    logInfo() << "File changed slot called for:" << file;
}


void FileWatchersManager::dirChangedSlot(const QString& dir) {
    long start = QDateTime::currentMSecsSinceEpoch();
    logDebug() << "Dir changed:" << dir;
    if (not QDir(dir).exists()) {
        logDebug() << "Dir has gone. Assuming directory deletion of:" << dir;
        removePath(dir);
        // scanDir(QDir(dir + "/.."));
    } else {
        logDebug() << "Dir changed:" << dir;
        scanDir(QDir(dir)); /* don't scan non existent directories */
    }
    long end = QDateTime::currentMSecsSinceEpoch();
    logDebug() << "Dir changed slot took:" << QString::number(end - start) << "ms";
}
