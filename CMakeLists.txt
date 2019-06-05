cmake_minimum_required(VERSION 3.2)


 message(STATUS "Looking for Qt5")
 find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Xml)
 message(STATUS "Using Qt ${Qt5_VERSION}")

find_package(ROOT REQUIRED)
message(STATUS "Using ROOT ${ROOT_VERSION}")

if(NOT Qt5_FOUND)
  return()
endif()


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

#add_directory(/home/alice/alice/new-alpide-software/DataBaseSrc)

set(SRCS

  main.cpp
  mainwindow.cpp
)

add_executable(db ${SRCS})
#add_library(alucms SHARED ${SRCS})




target_link_libraries(db curl xml2 Qt5::Gui Qt5::Core Qt5::Widgets alpide ${ROOT_LIBRARIES} pthread)


target_include_directories(db PUBLIC . ${ROOT_INCLUDE_DIRS} /usr/include/libxml2 /home/alice/alice/new-alpide-software/ /home/alice/alice/new-alpide-software/DataBaseSrc/ /home/alice/alice/new-alpide-software/inc/ /home/alice/alice/new-alpide-software/MosaicSrc/libpowerboard/include /home/alice/alice/new-alpide-software/MosaicSrc/libmosaic/include /home/alice/alice/new-alpide-software/exe)



install(TARGETS db 
  RUNTIME DESTINATION bin)


