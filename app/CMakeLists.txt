find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(${PROJECT_NAME}

        # Common
        common/validation/lexicalvalidation.cpp
        common/validation/validation.cpp
        common/validation/lexicalvalidation.h
        common/validation/validation.h
        common/exceptions/server_unavailable_exception.h common/exceptions/server_unavailable_exception.cpp
        common/exceptions/invalid_credentials_exception.h common/exceptions/invalid_credentials_exception.cpp
        common/errors/auth_error.h
        common/errors/auth_error.cpp
        common/validation/regex_patterns.h
        common/errors/auth_error.h common/errors/auth_error.cpp
        common/errors/call_error.h common/errors/call_error.cpp
        common/states/call_state.h

        # Main

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
        ui/view/call_menu/call_menu.h ui/view/call_menu/call_menu.cpp
        ui/presenter/call_menu_presenter.h ui/presenter/call_menu_presenter.cpp
        ui/model/call_menu_model.h ui/model/call_menu_model.cpp

        # Domain

        domain/entities/contact.cpp
        domain/entities/contact.h
        domain/entities/auth_credits.h
        domain/entities/auth_credits.cpp
        domain/interfaces/auth_repository.h domain/interfaces/auth_repository.cpp
        domain/controllers/auth/auth_controller.h domain/controllers/auth/auth_controller.cpp
        domain/entities/sip_uri.h
        domain/entities/sip_uri.cpp
        domain/entities/call_session.h
        domain/entities/call_session.cpp
        domain/controllers/calls/call_controller.h domain/controllers/calls/call_controller.cpp
        domain/interfaces/call_repository.h domain/interfaces/call_repository.cpp
        ui/view/setting/setting_menu.h ui/view/setting/setting_menu.cpp
        ui/presenter/setting_menu_presenter.h ui/presenter/setting_menu_presenter.cpp
        ui/model/setting_menu_model.h ui/model/setting_menu_model.cpp
        domain/controllers/setting/setting_controller.h domain/controllers/setting/setting_controller.cpp
        domain/interfaces/setting_repository.h domain/interfaces/setting_repository.cpp
        domain/entities/pbx_auth_credits.h domain/entities/pbx_auth_credits.cpp
        )


target_link_libraries(VoIP PRIVATE Qt6::Core)
add_subdirectory(data)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/common/validation/
        ${CMAKE_CURRENT_SOURCE_DIR}/common/errors/
        ${CMAKE_CURRENT_SOURCE_DIR}/common/states/
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/model
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/presenter
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/view/auth
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/view/main_window
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/view/contact_list
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/view/setting
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/view/call_menu
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/controllers/auth
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/controllers/calls
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/controllers/contacts
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/controllers/setting
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/interfaces
        ${CMAKE_CURRENT_SOURCE_DIR}/domain/entities
        ${CMAKE_CURRENT_SOURCE_DIR}/data/repositories/auth/
        ${CMAKE_CURRENT_SOURCE_DIR}/data/repositories/auth/
        ${CMAKE_CURRENT_SOURCE_DIR}/data/repositories/calls/
        ${CMAKE_CURRENT_SOURCE_DIR}/data/repositories/setting/

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
