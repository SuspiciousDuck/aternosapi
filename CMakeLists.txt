cmake_minimum_required(VERSION 3.0.0)
project(aternosapi)
include(${CMAKE_CURRENT_SOURCE_DIR}/FindQuickJS.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

find_package(cpr REQUIRED)
find_package(cryptopp REQUIRED)
find_package(QuickJS REQUIRED)
find_package(LibXml2 REQUIRED)
find_quickjs()
configure_quickjs()

include_directories(src)
file(GLOB files_aternos CONFIGURE_DEPENDS "src/*.h" "src/*.cpp" "src/*.c")

add_executable(scraper ${files_aternos})
target_include_directories(scraper PRIVATE ${QUICKJSPP_INCLUDE_DIRS})
target_link_libraries(scraper PRIVATE ${QUICKJS_LIBRARY} ${LIBXML2_LIBRARIES} cpr::cpr cryptopp::cryptopp)