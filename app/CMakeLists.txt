find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(${PROJECT_NAME}

        # Common
        common/validation/lexicalvalidation.cpp
        common/validation/validation.cpp
        common/validation/lexicalvalidation.h
        common/validation/validation.h

        main.cpp

        # UI
        ui/model/auth_menu_model.cpp
        ui/model/auth_menu_model.h
        ui/presenter/auth_menu_presenter.cpp
        ui/presenter/auth_menu_presenter.h
        ui/view/auth/auth_menu.cpp
        ui/view/auth/auth_menu.h
        ui/view/main_window/main_window.cpp
        ui/view/main_window/main_window.h
        ui/view/main_window/mainwindow.ui

        # Domain
        domain/entities/call_session.h
        domain/entities/contact.cpp
        domain/entities/contact.h


        domain/entities/auth_credits.h
        domain/entities/auth_credits.cpp
        domain/interfaces/auth_repository.h domain/interfaces/auth_repository.cpp
        domain/controllers/auth/auth_controller.h domain/controllers/auth/auth_controller.cpp
        common/exceptions/invalid_credentials_exception.h common/exceptions/invalid_credentials_exception.cpp
        common/exceptions/server_unavailable_exception.h common/exceptions/server_unavailable_exception.cpp

        common/errors/auth_error.h common/errors/auth_error.cpp
        )


target_link_libraries(VoIP PRIVATE Qt6::Core)
add_subdirectory(data)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/common/validation/
        ${CMAKE_CURRENT_SOURCE_DIR}/common/errors/
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/model
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/presenter
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/view/auth
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/view/main_window
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/view/contact_list
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/controllers/auth
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/controllers/calls
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/controllers/contacts
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/interfaces
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/entities
        ${CMAKE_CURRENT_SOURCE_DIR}/data/repositories/auth/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    siplib
    )


set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
