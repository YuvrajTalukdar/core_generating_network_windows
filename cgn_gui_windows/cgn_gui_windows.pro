QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += lpthread

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core_generating_network_win/core_class.cpp \
    core_generating_network_win/genetic_algorithm.cpp \
    core_generating_network_win/input_raw_to_prepared.cpp \
    core_generating_network_win/segment_class.cpp \
    main.cpp \
    mainwindow.cpp \
    make_individual_prediction.cpp \
    set_critical_variable.cpp

HEADERS += \
    core_generating_network_win/core_class.h \
    core_generating_network_win/neural_network_core_data_package_class.h \
    core_generating_network_win/neuron_and_ann_class.h \
    core_generating_network_win/segment_class.h \
    mainwindow.h \
    make_individual_prediction.h \
    set_critical_variable.h

FORMS += \
    mainwindow.ui \
    make_individual_prediction.ui \
    set_critical_variable.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
