/**
 *  @author dmilith
 *
 *   © 2014 - VerKnowSys
 *
 */

#include "worker_thread.h"


WorkerThread::WorkerThread(const QString& sourceDir) {
    this->source = sourceDir;
}


void WorkerThread::run() {
    this->watcher = new FileWatchersManager(source); /* true => store files on remote as SHA1 of original name */
    exec();
}
