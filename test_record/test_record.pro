QT       += core gui

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

INCLUDEPATH += C:\opencv\build\include

LIBS += C:\buildopencv\bin\libopencv_calib3d401.dll
LIBS += C:\buildopencv\bin\libopencv_core401.dll
LIBS += C:\buildopencv\bin\libopencv_dnn401.dll
LIBS += C:\buildopencv\bin\libopencv_features2d401.dll
LIBS += C:\buildopencv\bin\libopencv_flann401.dll
LIBS += C:\buildopencv\bin\libopencv_gapi401.dll
LIBS += C:\buildopencv\bin\libopencv_highgui401.dll
LIBS += C:\buildopencv\bin\libopencv_imgcodecs401.dll
LIBS += C:\buildopencv\bin\libopencv_imgproc401.dll
LIBS += C:\buildopencv\bin\libopencv_ml401.dll
LIBS += C:\buildopencv\bin\libopencv_objdetect401.dll
LIBS += C:\buildopencv\bin\libopencv_photo401.dll
LIBS += C:\buildopencv\bin\libopencv_stitching401.dll
LIBS += C:\buildopencv\bin\libopencv_video401.dll
LIBS += C:\buildopencv\bin\libopencv_videoio401.dll


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
