#-------------------------------------------------
#
# Project created by QtCreator 2011-08-05T18:11:49
#
#-------------------------------------------------

QT       += core widgets

TARGET = Notifier
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

RESOURCES += \
    icons.qrc

TRANSLATIONS += notifier.ts

OTHER_FILES += \
    notifier.ts \
    notifier.rc

RC_FILE += notifier.rc
