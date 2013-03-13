include(../config.pri)

CONFIG += ordered

TEMPLATE = subdirs

SUBDIRS += \
          sanitychecks \
          ut_maliit_attributeextension \
          ut_maliit_attributeextensionregistry \
          ut_maliit_inputmethod \
          ut_maliit_settings \
          ut_minputcontext \

QMAKE_EXTRA_TARGETS += check
check.target = check
check.CONFIG = recursive
