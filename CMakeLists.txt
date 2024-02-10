cmake_minimum_required(VERSION 3.5)
project(aternosapi)

find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(cryptopp REQUIRED)
find_library(quickjs NAMES libquickjs.so libquickjs.a PATH_SUFFIXES "quickjs" REQUIRED)
message(WARNING "Note: you may need to patch quickjs so that it compiles with -fPIC")

include_directories(src include)
file(GLOB files_test "src/test/*.cpp" "src/test/*.c")
file(GLOB files_aternos "src/*.cpp" "src/*.c")
file(GLOB headers "include/aternosapi/*.h" "include/aternosapi/*.hpp")

add_library(aternosapi SHARED ${files_aternos})
target_link_directories(aternosapi PUBLIC include/)
target_link_libraries(aternosapi PUBLIC ${quickjs} LibXml2::LibXml2 cpr::cpr cryptopp::cryptopp)
set_target_properties(aternosapi PROPERTIES
    PUBLIC_HEADER "${headers}"
)

add_executable(test ${files_test})
target_link_directories(test PUBLIC include/)
target_link_libraries(test PUBLIC aternosapi)

install(TARGETS aternosapi LIBRARY DESTINATION lib/aternosapi PUBLIC_HEADER DESTINATION include/aternosapi)
