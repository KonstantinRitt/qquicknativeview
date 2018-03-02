QT *= quick
QT_PRIVATE *= quick-private

INCLUDEPATH += $$PWD/include

HEADERS += \
    $$PWD/src/qquickimagenativeview.h \
    $$PWD/src/qquickimagenativeview_p.h \
    $$PWD/src/qquickimplicitsizenativeview.h \
    $$PWD/src/qquickimplicitsizenativeview_p.h \
    $$PWD/src/qquicknativeview.h \
    $$PWD/src/qquicknativeview_p.h

SOURCES += \
    $$PWD/src/qquickimagenativeview.cpp \
    $$PWD/src/qquickimplicitsizenativeview.cpp \
    $$PWD/src/qquicknativeview.cpp

android {
    QT *= androidextras

    SOURCES += \
        $$PWD/src/qquicknativeview_android.cpp
} else:ios {
    OBJECTIVE_SOURCES += \
        $$PWD/src/qquicknativeview_ios.mm
}
