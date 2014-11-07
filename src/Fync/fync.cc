/**
 *  @author dmilith, tallica
 *
 *   © 2014 - VerKnowSys
 *
 */

#include "fync.h"
#include "worker_thread.h"


/*
 *  Read file contents of text file
 */
QString readFileContents(const QString& fileName) {
    QString lines = "";
    QFile f(fileName);
    f.open(QIODevice::ReadOnly);
    QTextStream stream(&f);
    // stream.setCodec(QTextCodec::codecForName(DEFAULT_STRING_CODEC));
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (!line.trimmed().isEmpty()) {
            lines += line + "\n";
        }
    }
    lines += "\n";
    f.close();
    return lines;
}


int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setOrganizationName("VerKnowSys");
    QCoreApplication::setOrganizationDomain("verknowsys.com");
    QCoreApplication::setApplicationName("Fync");
    QSettings settings;
    settings.setValue("lastRun", QDateTime::currentDateTime());
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(DEFAULT_STRING_CODEC));
    QStringList args = app.arguments();
    QStringList remotes;
    QList<WorkerThread*> workers;

    /* Logger setup */
    ConsoleAppender *consoleAppender = new ConsoleAppender();
    Logger::registerAppender(consoleAppender);
    consoleAppender->setFormat("%t{dd-HH:mm:ss} [%-7l] <%c:(%F:%i)> %m\n");
    consoleAppender->setDetailsLevel(Logger::Debug);

    logInfo() << "Fync v" << APP_VERSION << "-" << COPYRIGHT;
    QStringList inputDirs = readFileContents("input-dirs").trimmed().split("\n");
    logDebug() << "Input dirs:" << inputDirs.join(", ");

    QFile* loggerPipe = new QFile(OUTPUT_PIPE);
    loggerPipe->open(QIODevice::WriteOnly);
    for (int i = 0; i < inputDirs.length(); i++) {
        logDebug() << "Creating thread for:" << inputDirs.at(i);
        workers << new WorkerThread(inputDirs.at(i), loggerPipe);
        workers.at(i)->start();
    }

    return app.exec();
}
