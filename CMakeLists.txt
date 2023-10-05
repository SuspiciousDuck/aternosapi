cmake_minimum_required(VERSION 3.0.0)
project(aternosapi)
include(${CMAKE_CURRENT_SOURCE_DIR}/FindQuickJS.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "-O3")

find_package(cpr REQUIRED)
find_package(cryptopp REQUIRED)
find_package(QuickJS REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(nlohmann_json REQUIRED)
find_quickjs()
configure_quickjs()

include_directories(src)
file(GLOB files_aternos "src/*.cpp" "src/*.c")
file(GLOB headers "src/*.h" "src/*.hpp")

add_library(aternosapi SHARED ${files_aternos})
target_include_directories(aternosapi PUBLIC ${QUICKJSPP_INCLUDE_DIRS})
target_link_libraries(aternosapi PUBLIC ${QUICKJS_LIBRARY} ${LIBXML2_LIBRARIES} cpr::cpr cryptopp::cryptopp)
set_target_properties(aternosapi PROPERTIES
    PUBLIC_HEADER "${headers}"
)

install(TARGETS aternosapi LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/aternosapi PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/aternosapi)
