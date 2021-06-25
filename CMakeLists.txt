cmake_minimum_required(VERSION 3.0.0)
project(stockSimulator VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)
include(CTest)
enable_testing()
set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED)
FIND_PACKAGE(FLTK REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
include_directories(src headers ${CURL_INCLUDE_DIR})
add_executable(stockSimulator
    main.cpp
    headers/akcije.hpp
    headers/akcijeGui.hpp
    src/akcijeGui.cpp
    headers/datum.hpp
    src/datum.cpp
    headers/grafik.hpp
    src/grafik.cpp
    headers/gui.hpp
    src/gui.cpp
    headers/konzola.hpp
    src/konzola.cpp
    headers/parser.hpp
    src/parser.cpp
    headers/podaci.hpp
    src/podaci.cpp
    headers/sqlBaza.hpp
    src/sqlBaza.cpp
    headers/sveca.hpp
    headers/tabela.hpp
    src/tabela.cpp
    headers/transakcije.hpp
    headers/transakcijeGui.hpp
    src/transakcijeGui.cpp
)
target_link_libraries(stockSimulator ${CURL_LIBRARIES} -lsqlite3 ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES})
configure_file(baza.db baza.db COPYONLY)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)