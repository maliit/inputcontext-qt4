include(../config.pri)

TOP_DIR = ..

TEMPLATE = lib
TARGET = $$TOP_DIR/lib/maliit-common

CONFIG += staticlib

FRAMEWORKHEADERSINSTALL = \
    maliit/namespace.h \
    maliit/settingdata.h \

HEADERS += \
    $$FRAMEWORKHEADERSINSTALL \
    maliit/namespaceinternal.h \

SOURCES += \
    maliit/settingdata.cpp \

frameworkheaders.path += $$INCLUDEDIR/$$MALIIT_FRAMEWORK_HEADER/maliit
frameworkheaders.files += $$FRAMEWORKHEADERSINSTALL

INSTALLS += \
    frameworkheaders \

OTHER_FILES += \
    libmaliit-common.pri
