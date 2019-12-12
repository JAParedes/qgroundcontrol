LinuxBuild {
    DEFINES += HAVE_QT_X11 HAVE_QT_EGLFS HAVE_QT_WAYLAND
} else:MacBuild {
    DEFINES += HAVE_QT_MAC
} else:iOSBuild {
    DEFINES += HAVE_QT_IOS
} else:WindowsBuild {
    DEFINES += HAVE_QT_WIN32
    LIBS += opengl32.lib
} else:AndroidBuild {
    DEFINES += HAVE_QT_ANDROID
}

SOURCES += \
    libs/gst-plugins-good/ext/qt/gstplugin.cc \
    libs/gst-plugins-good/ext/qt/gstqtglutility.cc \
    libs/gst-plugins-good/ext/qt/gstqsgtexture.cc \
    libs/gst-plugins-good/ext/qt/gstqtsink.cc \
    libs/gst-plugins-good/ext/qt/gstqtsrc.cc \
    libs/gst-plugins-good/ext/qt/qtwindow.cc \
    libs/gst-plugins-good/ext/qt/qtitem.cc

HEADERS += \
    libs/gst-plugins-good/ext/qt/gstqsgtexture.h \
    libs/gst-plugins-good/ext/qt/gstqtgl.h \
    libs/gst-plugins-good/ext/qt/gstqtglutility.h \
    libs/gst-plugins-good/ext/qt/gstqtsink.h \
    libs/gst-plugins-good/ext/qt/gstqtsrc.h \
    libs/gst-plugins-good/ext/qt/qtwindow.h \
    libs/gst-plugins-good/ext/qt/qtitem.h
