QT += charts
requires(qtConfig(combobox))

HEADERS += \
    charts_limits.hpp \
    linear_space.hpp \
    move_node.hpp \
    themewidget.h

SOURCES += \
    linear_space.cpp \
    main.cpp \
    move_node.cpp \
    themewidget.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/chartthemes
INSTALLS += target

FORMS += \
    themewidget.ui
