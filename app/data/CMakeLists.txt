cmake_minimum_required(VERSION 3.28)

project(siplib VERSION 0.1 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
        services/SIP/module_sip.cpp
        services/SIP/module_sip.h
        repositories/auth/auth_repository_impl.h
        repositories/auth/auth_repository_impl.cpp
)

set(PJPROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/utils/pjproject")
set(PJPROJECT_BINARY_DIR "${CMAKE_BINARY_DIR}/utils/pjproject")

target_include_directories(${PROJECT_NAME}
   PUBLIC
       ${CMAKE_CURRENT_SOURCE_DIR}/../domain/interfaces/
       ${CMAKE_CURRENT_SOURCE_DIR}/../domain/entities/
       ${CMAKE_CURRENT_SOURCE_DIR}/../common/errors
       ${CMAKE_CURRENT_SOURCE_DIR}/services/SIP
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
target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core pjsua2)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
