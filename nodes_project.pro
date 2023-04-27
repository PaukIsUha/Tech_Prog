QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graphicFigures/Geli.cpp \
    graphicFigures/GraphicsScene.cpp \
    viewItems/area2d_view.cpp \
    viewItems/edge.cpp \
    viewItems/grid.cpp \
    linSpace/linear_space.cpp \
    main.cpp \
    mainwindow.cpp \
    viewItems/move_node.cpp

HEADERS += \
    graphicFigures/Geli.hpp \
    graphicFigures/GraphicsScene.h \
    viewItems/area2d_view.hpp \
    viewItems/edge.hpp \
    viewItems/grid.hpp \
    linSpace/linear_space.hpp \
    mainwindow.h \
    viewItems/move_node.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
