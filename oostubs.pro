TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    src/machine/pic.cc \
    src/machine/keyctrl.cc

HEADERS += \
    include/config.h \
    include/machine/io_port.h \
    include/machine/pic.h \
    include/machine/cpu.h

