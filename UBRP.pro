QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AuthRule.cpp \
    SMTP/attachment.cpp \
    SMTP/base64.cpp \
    SMTP/credential.cpp \
    SMTP/errorresolver.cpp \
    SMTP/forcedsecuresmtpclient.cpp \
    SMTP/htmlmessage.cpp \
    SMTP/message.cpp \
    SMTP/messageaddress.cpp \
    SMTP/opportunisticsecuresmtpclient.cpp \
    SMTP/plaintextmessage.cpp \
    SMTP/securesmtpclientbase.cpp \
    SMTP/smtpclient.cpp \
    SMTP/smtpclientbase.cpp \
    SMTP/stringutils.cpp \
    USBDevice.cpp \
    emailsmtp.cpp \
    main.cpp \
    mainwindow.cpp \
    smpttest.cpp

HEADERS += \
    AuthRule.h \
    SMTP/attachment.h \
    SMTP/base64.h \
    SMTP/credential.h \
    SMTP/errorresolver.h \
    SMTP/forcedsecuresmtpclient.h \
    SMTP/htmlmessage.h \
    SMTP/message.h \
    SMTP/messageaddress.h \
    SMTP/opportunisticsecuresmtpclient.h \
    SMTP/plaintextmessage.h \
    SMTP/securesmtpclientbase.h \
    SMTP/serverauthoptions.h \
    SMTP/smtpclient.h \
    SMTP/smtpclientbase.h \
    SMTP/smtpclienterrors.h \
    SMTP/smtpserverstatuscodes.h \
    SMTP/socketerrors.h \
    SMTP/sslerrors.h \
    SMTP/sslsmtpclient.h \
    SMTP/stringutils.h \
    USBDevice.h \
    emailsmtp.h \
    mainwindow.h \
    smpttest.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/./ -lsmtpclient

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix:!macx: PRE_TARGETDEPS += $$PWD/./libsmtpclient.a

unix:!macx: LIBS += -lusb-1.0

unix:!macx: LIBS += -lfmt

unix:!macx: LIBS += -lssl

unix:!macx: LIBS += -lcrypto
