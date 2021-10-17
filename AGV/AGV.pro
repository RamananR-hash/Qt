QT       += core gui network serialport gamepad

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

LIBS += -LC:\cvb\install\x64\vc16\lib -lopencv_core452 -lopencv_imgproc452 -lopencv_highgui452 -lopencv_imgcodecs452 -lopencv_videoio452 -lopencv_video452 -lopencv_calib3d452 -lopencv_photo452 -lopencv_features2d452
INCLUDEPATH += C:\cvb\install\include
DEPENDPATH += C:\cvb\install\include


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    scr.qrc
