#-------------------------------------------------
#
# Project created by QtCreator 2011-08-05T18:11:49
#
#-------------------------------------------------

QT       += core widgets

TARGET = Notifier
TEMPLATE = app


SOURCES += src/main.cpp\
        src/widget.cpp

HEADERS  += src/widget.h

FORMS    += ui/widget.ui

RESOURCES += \
    res/icons.qrc

TRANSLATIONS += i18n/notifier.ts

OTHER_FILES += \
    i18n/notifier.ts \
    res/notifier.rc

RC_FILE += res/notifier.rc
