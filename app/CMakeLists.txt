find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(${PROJECT_NAME}
        common/validation/lexicalvalidation.cpp
        common/validation/validation.cpp
        main.cpp
        model/authmenumodel.cpp
        ui/auth/authmenu.cpp
        ui/main_window/mainwindow.cpp
        common/validation/lexicalvalidation.h
        common/validation/validation.h
        model/authmenumodel.h
        ui/auth/authmenu.h
        ui/main_window/mainwindow.h
        ui/main_window/mainwindow.ui)

add_subdirectory(modules/sip/)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/main_window/
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/auth/
        ${CMAKE_CURRENT_SOURCE_DIR}/model/
        ${CMAKE_CURRENT_SOURCE_DIR}/common/validation/
        ${CMAKE_CURRENT_SOURCE_DIR}/modules/sip/logic
        ${CMAKE_CURRENT_SOURCE_DIR}/modules/sip/presenter
        ${CMAKE_CURRENT_SOURCE_DIR}/modules/sip/data)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    siplib
    )


set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
