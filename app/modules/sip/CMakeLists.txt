cmake_minimum_required(VERSION 3.28)

project(siplib VERSION 0.1 LANGUAGES CXX)


add_library(${PROJECT_NAME} STATIC
        logic/modulesip.cpp
        presenter/authmenupresenter.cpp
        logic/modulesip.h
        presenter/authmenupresenter.h
        )

set(PJPROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/utils/pjproject")
set(PJPROJECT_BINARY_DIR "${CMAKE_BINARY_DIR}/utils/pjproject")

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/app/ui/auth/
        ${CMAKE_SOURCE_DIR}/app/model/
        ${CMAKE_CURRENT_SOURCE_DIR}/logic/
    PRIVATE
        ${PJPROJECT_BINARY_DIR}/pjsip/include
        ${PJPROJECT_BINARY_DIR}/pjmedia/include
        ${PJPROJECT_BINARY_DIR}/pjnath/include
        ${PJPROJECT_BINARY_DIR}/pjlib-util/include
        ${PJPROJECT_BINARY_DIR}/pjlib/include

        ${PJPROJECT_SOURCE_DIR}/pjsip/include
        ${PJPROJECT_SOURCE_DIR}/pjmedia/include
        ${PJPROJECT_SOURCE_DIR}/pjnath/include
        ${PJPROJECT_SOURCE_DIR}/pjlib-util/include
        ${PJPROJECT_SOURCE_DIR}/pjlib/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets pjsua2)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
