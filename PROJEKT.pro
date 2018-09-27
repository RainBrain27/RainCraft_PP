HEADERS       = glwidget.h \
    camara.h \
    baseobject.h \
    cube.h \
    skycube.h
SOURCES       = glwidget.cpp \
                main.cpp \
    camara.cpp \
    baseobject.cpp \
    cube.cpp \
    skycube.cpp

RESOURCES     = textures.qrc

QT           += widgets

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/textures
INSTALLS += target

INCLUDEPATH += "D:/Programieren/Umbgebungen/glm/glm/"
