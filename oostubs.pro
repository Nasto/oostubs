TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    src/machine/pic.cc \
    src/machine/keyctrl.cc \
    src/guard/guardian.cc \
    src/machine/plugbox.cc \
    src/device/keyboard.cc \
    src/device/panic.cc

HEADERS += \
    include/config.h \
    include/machine/io_port.h \
    include/machine/pic.h \
    include/machine/cpu.h \
    include/useful/cpu.h \
    include/machine/plugbox.h \
    include/guard/gate.h \
    include/useful/panic.h \
    include/machine/cgascr.h \
    include/object/strbuf.h \
    include/useful/kout.h \
    include/device/panic.h \
    include/device/keyboard.h \
    include/machine/keyctrl.h \
    include/machine/key.h \
    include/useful/plugbox.h \
    include/useful/pic.h

