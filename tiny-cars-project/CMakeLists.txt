
cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME ex56)
set(PROJECT_FILES main.cpp Edge.cpp glutWindow.cpp Polygon.cpp Edge.h glutWindow.h mesh.h Polygon.h Triangle.h Vector2D.h mesh.cpp Gate.h Curves.h)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

IF (WIN32)
    message(STATUS ">>> Win32")
    add_compile_definitions(USE_FREEGLUT)

    set(GLUT_INTERFACE_DIRS  ../glutInterface)
    set(GLUT_INTERFACE_LIB_DIRS  ../glutInterface/cmake-build-debug)
    include_directories(${GLUT_INTERFACE_DIRS})

    IF (MSVC)
        message(STATUS "+Visual studio")
        set(GLUT_DIR F:/freeglut-3.0.0)
        set(CMAKE_PREFIX_PATH FREEGLUT)

        set(FREEGLUT_INCLUDE_DIRS F:/freeglut-3.0.0/include)
        set(FREEGLUT_LIBRARY_DIRS F:/freeglut-3.0.0/cmake-build-debug/lib)
        set(FREEGLUT_LIBRARIES libfreeglut_static.a)

        find_package(OPENGL REQUIRED)

        include_directories(${FREEGLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLUT_INTERFACE_DIRS})
        link_directories(${FREEGLUT_LIBRARY_DIRS} ${OPENGL_LIBRARY_DIRS} ${GLUT_INTERFACE_LIB_DIRS})
        add_definitions(${FREEGLUT_DEFINITIONS} ${OPENGL_DEFINITIONS})
        add_executable(${PROJECT_NAME} ${PROJECT_FILES})
        target_link_libraries(${PROJECT_NAME} ${FREEGLUT_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} glutInterface.lib)
    ENDIF(MSVC)

    IF(MINGW)
        message(STATUS "+MinGW")
        link_directories(${GLUT_INTERFACE_LIB_DIRS})
        add_executable(${PROJECT_NAME} ${PROJECT_FILES})
        target_link_libraries(${PROJECT_NAME} -lOpenGL32 -lglu32 -lfreeglut)
    ENDIF(MINGW)
ENDIF (WIN32)

