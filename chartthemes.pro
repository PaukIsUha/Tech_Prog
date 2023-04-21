QT += charts
requires(qtConfig(combobox))

HEADERS += \
    charts_limits.hpp \
    linear_space.hpp \
    themewidget.h

SOURCES += \
    linear_space.cpp \
    main.cpp \
    themewidget.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/chartthemes
INSTALLS += target

FORMS += \
    themewidget.ui
