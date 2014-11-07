/**
 *  @author dmilith
 *
 *   © 2014 - VerKnowSys
 *
 */

#include "file_watchers_manager.h"


FileWatchersManager::FileWatchersManager(const QString& sourceDir, QFile* logger) {
    logDebug() << "Starting recursive watch on dir:" << sourceDir;
    this->baseCWD = sourceDir;
    this->loggerPipe = logger;

    /* connect hooks to invokers */
    connect(this, SIGNAL(fileChanged(QString)), this, SLOT(fileChangedSlot(QString)));
    connect(this, SIGNAL(directoryChanged(QString)), this, SLOT(dirChangedSlot(QString)));
    scanDir(QDir(sourceDir));
}


void FileWatchersManager::scanDir(QDir dir) {
    long start = QDateTime::currentMSecsSinceEpoch();
    logDebug() << "Scanning:" << dir.absolutePath();

    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QDirIterator it(dir, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString nextOne = it.next();
        QRegExp matcher(NOT_ALLOWED_FILE_TYPES);
        matcher.setCaseSensitivity(Qt::CaseInsensitive);
        if (not nextOne.contains(matcher)) {
            logTrace() << "Found match:" << nextOne;
            addPath(nextOne);
        } else {
            removePath(nextOne);
        }
    }

    logDebug() << "Watched dir:" << baseCWD; // << "Diff:" << QString::number(files.size());
    long end = QDateTime::currentMSecsSinceEpoch();
    logDebug() << "Scan took:" << QString::number(end - start) << "ms";
}


void FileWatchersManager::fileChangedSlot(const QString& file) {
    logInfo() << "File changed slot called for:" << file;
    /*  here all the magic wil lhappen. We need to create thread safe
        queue of events from fs, which will be passed to endpoint mechanism */
    mutex.lock();
    logDebug() << "Writing to log pipe:" << file;
    loggerPipe->write(file.toUtf8() + "\n");
    loggerPipe->flush();
    mutex.unlock();
}


void FileWatchersManager::dirChangedSlot(const QString& dir) {
    long start = QDateTime::currentMSecsSinceEpoch();
    logDebug() << "Dir changed:" << dir;
    if (not QDir(dir).exists()) {
        logDebug() << "Dir has gone. Assuming directory deletion of:" << dir;
        removePath(dir);
    } else {
        logDebug() << "Dir changed:" << dir;
        scanDir(QDir(dir));
    }
    long end = QDateTime::currentMSecsSinceEpoch();
    logDebug() << "Dir changed slot took:" << QString::number(end - start) << "ms";
}
