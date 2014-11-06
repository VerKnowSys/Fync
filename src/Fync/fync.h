/**
 *  @author dmilith
 *
 *   © 2014 - VerKnowSys
 *
 */

#ifndef __Fync_H__
#define __Fync_H__


/* ignore certain kinds of warnings: */
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wmismatched-tags"


/* all system wide includes required: */
#include <QtCore>
#include <sys/stat.h>

#include <QCryptographicHash>

#include "../CuteLogger/Logger.h"
#include "../CuteLogger/ConsoleAppender.h"
#include "../CuteLogger/FileAppender.h"


#define APP_VERSION "0.1.0"

#define FILE_SYNC_TIMEOUT 1000000 /* 1 second in us */
#define COPYRIGHT "2014 verknowsys.com"
#define DEFAULT_STRING_CODEC "UTF8"
#define ALLOWED_FILE_TYPES "\\.*$" /* NOTE: switched to wildcard to accept any file type drop */
// #define ALLOWED_FILE_TYPES "\\.pro$|\\.hpp$|\\.h$|\\.c$|\\.cc$|\\.cpp$|\\.scala$|\\.java$|\\.rb$|Rakefile$|\\.properties$|\\.xml$|\\.html$|\\.js$|\\.coffee$|\\.sh$|\\.def$|\\.md$|\\.haml$|\\.slim$|\\.css$|\\.sass$|\\.scss$|\\.less$|\\.erb$|\\.yml|\\.yaml$$|\\.conf$|\\.json$|\\.jpg$|\\.jpeg$|\\.png$|\\.svg$|\\.gif$|\\.jar$|\\.ini$|\\.patch$|\\.jp2$"

/* Loggers */
#define logTrace LOG_TRACE
#define logDebug LOG_DEBUG
#define logInfo  LOG_INFO
#define logWarn  LOG_WARNING
#define logError LOG_ERROR
#define logFatal LOG_FATAL


QString readFileContents(const QString& fileName);

#endif
