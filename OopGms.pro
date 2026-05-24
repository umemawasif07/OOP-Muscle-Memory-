QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addmemberdialog.cpp \
    addtrainerdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    recordpaymentdialog.cpp \
    viewmemberdialog.cpp \
    viewpaymentsdialog.cpp \
    viewtrainerdialog.cpp

HEADERS += \
    addmemberdialog.h \
    addtrainerdialog.h \
    mainwindow.h \
    recordpaymentdialog.h \
    viewmemberdialog.h \
    viewpaymentsdialog.h \
    viewtrainerdialog.h

FORMS += \
    addmemberdialog.ui \
    addtrainerdialog.ui \
    mainwindow.ui \
    recordpaymentdialog.ui \
    viewmemberdialog.ui \
    viewpaymentsdialog.ui \
    viewtrainerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
