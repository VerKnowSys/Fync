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


#define APP_VERSION "0.1.1"

#define OUTPUT_PIPE "/var/log/output_pipe"
#define FILE_SYNC_TIMEOUT 1000000 /* 1 second in us */
#define COPYRIGHT "2014 verknowsys.com"
#define DEFAULT_STRING_CODEC "UTF8"
#define NOT_ALLOWED_FILE_TYPES "\\.(wav|m4a|mov|aif|mp3|mp4|ogv|3gp|ogg|ai|psd|jpg|jpeg|png|tiff|avi|gif|jar|jp2|mp?g|bmp|gif|zip|rar|7z|tmp|lock|pdf|dts|flac)"


/* Loggers */
#define logTrace LOG_TRACE
#define logDebug LOG_DEBUG
#define logInfo  LOG_INFO
#define logWarn  LOG_WARNING
#define logError LOG_ERROR
#define logFatal LOG_FATAL


QString readFileContents(const QString& fileName);

#endif
