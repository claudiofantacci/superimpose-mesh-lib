set(TEST_TARGET_NAME test_scissors)

set(${TEST_TARGET_NAME}_HDR
        ../common/utils.h
)

set(${TEST_TARGET_NAME}_SRC
        main.cpp
)


add_executable(${TEST_TARGET_NAME} ${${TEST_TARGET_NAME}_HDR} ${${TEST_TARGET_NAME}_SRC})

target_link_libraries(${TEST_TARGET_NAME} SuperimposeMesh::SuperimposeMesh)

target_include_directories(${TEST_TARGET_NAME}
                           PRIVATE
                               ${PROJECT_SOURCE_DIR}/test/common)

add_test(NAME ${TEST_TARGET_NAME}
         COMMAND ${TEST_TARGET_NAME}
         WORKING_DIRECTORY $<TARGET_FILE_DIR:${TEST_TARGET_NAME}>)
