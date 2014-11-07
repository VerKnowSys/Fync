/**
 *  @author dmilith
 *
 *   © 2014 - VerKnowSys
 *
 */

#include "worker_thread.h"


WorkerThread::WorkerThread(const QString& sourceDir, QFile* logger) {
    this->source = sourceDir;
    this->pipeLogger = logger;
}


void WorkerThread::run() {
    this->watcher = new FileWatchersManager(source, pipeLogger); /* true => store files on remote as SHA1 of original name */
    exec();
}
