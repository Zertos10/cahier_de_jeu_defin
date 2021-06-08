QT += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ballon.cpp \
    calcul_courbe_bezier.cpp \
    calcul_distance.cpp \
    database.cpp \
    export_database.cpp \
    graphics_scene-animation/animation/animationTraj.cpp \
    graphics_scene-animation/animation/confAnimation.cpp \
    graphics_scene-animation/graphic_scene/graphic_animation.cpp \
    graphics_scene-animation/graphic_scene/itemcreationscene.cpp \
    graphics_scene-animation/graphic_scene/itemframecreation.cpp \
    graphics_scene-animation/graphic_scene/itemlinetempcreation.cpp \
    graphics_scene-animation/graphic_scene/itemtokencreation.cpp \
    graphics_scene-animation/graphic_scene/playerFrameScene.cpp \
    import_database.cpp \
    lib/Bezier.cpp \
    lib/BezierPoint.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindows/tablesteam.cpp \
    mainwindows/terrainRugby.cpp \
    mainwindows/tracetraj.cpp \
    save_file.cpp \
    sql_request/sql_request_export.cpp \
    sql_request/sql_request_import.cpp \
    sql_request/sqlrequest.cpp \
    trajectoire_entite.cpp

HEADERS += \
    ballon.h \
    calcul_courbe_bezier.h \
    calcul_distance.h \
    database.h \
    export_database.h \
    graphics_scene-animation/animation/animationTraj.h \
    graphics_scene-animation/animation/confAnimation.h \
    graphics_scene-animation/graphic_scene/graphic_animation.h \
    graphics_scene-animation/graphic_scene/itemcreationscene.h \
    graphics_scene-animation/graphic_scene/itemframecreation.h \
    graphics_scene-animation/graphic_scene/itemlinetempcreation.h \
    graphics_scene-animation/graphic_scene/itemtokencreation.h \
    graphics_scene-animation/graphic_scene/playerFrameScene.h \
    import_database.h \
    lib/Bezier.hpp \
    lib/BezierPoint.hpp \
    mainwindow.h \
    mainwindows/tablesteam.h \
    mainwindows/terrainRugby.h \
    mainwindows/tracetraj.h \
    save_file.h \
    sql_request/sql_request_export.h \
    sql_request/sql_request_import.h \
    sql_request/sqlrequest.h \
    trajectoire_entite.h

FORMS += \
    export_database.ui \
    import_database.ui \
    mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressource.qrc
