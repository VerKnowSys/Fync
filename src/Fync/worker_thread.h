/**
 *  @author dmilith
 *
 *   © 2014 - VerKnowSys
 *
 */

#ifndef __WORKER_THREAD_H__
#define __WORKER_THREAD_H__


#include "fync.h"
#include "file_watchers_manager.h"


class WorkerThread: public QThread {
    Q_OBJECT

    public:
        WorkerThread(const QString& sourceDir, QFile* logger);
        void run();


    private:
        QPointer<FileWatchersManager> watcher;
        QString source;
        QFile* pipeLogger;

};


#endif
