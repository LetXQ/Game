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
    ../src/common/lock.cpp \
    ../src/config/bt_parse.cpp \
    ../src/obj/astar.cpp \
    ../src/bt/bt_node.cpp \
    ../src/bt/bt_node_factory.cpp \
    ../src/bt/bt_action_node.cpp \
    ../src/bt/bt_condition_node.cpp \
    ../src/bt/bt_control_node.cpp \
    ../src/bt/bt_proxy.cpp \
    ../src/bt_node/action/bt_attack_node.cpp \
    ../src/bt_node/condition/bt_find_target_node.cpp \
    ../src/bt_node/action/bt_attack_node.cpp \
    ../src/bt_node/action/bt_sleep_node.cpp \
    ../src/bt_node/action/bt_walk_node.cpp \
    ../src/bt/bt_decorator_node.cpp

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
    ../include/common/lock.h \
    ../include/config/bt_parse.h \
    ../include/obj/astar.h \
    ../include/bt/bt_node.h \
    ../include/bt/bt_proxy.h \
    ../include/bt/bt_node_factory.h \
    ../include/bt/bt_control_node.h \
    ../include/bt/bt_action_node.h \
    ../include/bt/bt_condition_node.h \
    ../include/bt/bt_create_node_funcs.h \
    ../include/bt_node/action/bt_attack_node.h \
    ../include/bt_node/condition/bt_find_target_node.h \
    ../src/bt_node/action/bt_sleep_node.h \
    ../src/bt_node/action/bt_walk_node.h \
    ../src/bt_node/action/bt_attack_node.h \
    ../include/bt_node/action/bt_sleep_node.h \
    ../include/bt_node/action/bt_walk_node.h \
    ../include/bt/bt_decorator_node.h \
    ../include/common/common_json_func.h \
    ../include/common/random.h

DISTFILES += \
    ../src/json/sconscript
