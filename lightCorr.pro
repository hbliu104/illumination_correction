TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

# OpenCV
win32 {

INCLUDEPATH += D:/OpenCV/build/install/include

LIBS += -LD:/OpenCV/build/install/x86/mingw/bin \
        -llibopencv_core330 \
        -llibopencv_highgui330 \
        -llibopencv_imgcodecs330 \
        -llibopencv_imgproc330 \
        -llibopencv_features2d330 \
        -llibopencv_calib3d330
}

unix {
INCLUDEPATH += /opt/OpenCV/include

LIBS += -L/opt/OpenCV/lib \
        -lopencv_core \
        -lopencv_flann \
        -lopencv_imgproc \
        -lopencv_ml \
        -lopencv_photo \
        -lopencv_video \
        -lopencv_imgcodecs \
        -lopencv_shape \
        -lopencv_videoio \
        -lopencv_highgui \
        -lopencv_objdetect \
        -lopencv_superres \
        -lopencv_features2d \
        -lopencv_calib3d \
        -lopencv_videostab
}


SOURCES += main.cpp
