# Fync - © 2013 verknowsys.com
#
# author:
#   Daniel (dmilith) Dettlaff
#


include(../Common.pro)

HEADERS += \
            file_watchers_manager.h \
            worker_thread.h \
            fync.h

SOURCES += \
            file_watchers_manager.cc \
            worker_thread.cc \
            fync.cc


TARGET = ../../bin/fync
LIBS += -lz ../liblogger.a
