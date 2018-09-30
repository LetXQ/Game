TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/json/json_internalarray.inl \
    ../src/json/json_internalmap.inl \
    ../src/json/json_reader.cpp \
    ../src/json/json_value.cpp \
    ../src/json/json_valueiterator.inl \
    ../src/json/json_writer.cpp \
    ../test.cpp \
    ../src/config/mapconfig.cpp \
    ../src/obj_move/astar.cpp \
    ../src/common/lock.cpp

HEADERS += \
    ../include/json/autolink.h \
    ../include/json/config.h \
    ../include/json/features.h \
    ../include/json/forwards.h \
    ../include/json/json.h \
    ../include/json/reader.h \
    ../include/json/value.h \
    ../include/json/writer.h \
    ../src/json/json_batchallocator.h \
    ../include/config/mapconfig.h \
    ../include/common/singleton.h \
    ../include/common/common_def.h \
    ../include/common/common_func.h \
    ../include/common/world_pos.h \
    ../include/obj_move/astar.h \
    ../include/common/lock.h

DISTFILES += \
    ../src/json/sconscript
