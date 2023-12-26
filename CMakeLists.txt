cmake_minimum_required(VERSION 3.5)
project(aternosapi)

find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(cryptopp REQUIRED)
find_library(quickjs NAMES libquickjs.so libquickjs.a PATH_SUFFIXES "quickjs" REQUIRED)

include_directories(src)
file(GLOB files_aternos "src/*.cpp" "src/*.c")
file(GLOB headers "src/*.h" "src/*.hpp")

add_library(aternosapi SHARED ${files_aternos})
target_link_libraries(aternosapi PUBLIC ${quickjs} LibXml2::LibXml2 cpr::cpr cryptopp::cryptopp)
set_target_properties(aternosapi PROPERTIES
    PUBLIC_HEADER "${headers}"
)

install(TARGETS aternosapi LIBRARY DESTINATION lib/aternosapi PUBLIC_HEADER DESTINATION include/aternosapi)
