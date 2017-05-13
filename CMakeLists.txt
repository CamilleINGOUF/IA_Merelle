CMAKE_MINIMUM_REQUIRED( VERSION 3.0 )
project( merelle )
set( CMAKE_CXX_STANDARD 14)

set( CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14 ${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

find_package( PkgConfig REQUIRED )
pkg_check_modules( Pkg
  REQUIRED libglog cpputest )
INCLUDE_DIRECTORIES( ${Pkg_INCLUDE_DIRS} )

ADD_EXECUTABLE( merelle.out
src/merelle.cpp
src/merelle.cpp
src/move.cpp
src/position.cpp)
TARGET_LINK_LIBRARIES( merelle.out ${Pkg_LIBRARIES} )
