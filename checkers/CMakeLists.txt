cmake_minimum_required(VERSION 3.0.0) # Проверка версии CMake.

project(checkers)				# Название проекта

set(CMAKE_AUTOMOC ON)			# Tell CMake to run moc when necessary:

set(CMAKE_INCLUDE_CURRENT_DIR ON)	# As moc files are generated in the binary dir, tell CMake to always look for includes there:


######################################################################################################################################
find_package(Qt5Widgets REQUIRED)	# Widgets finds its own dependencies (QtGui and QtCore).

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})

add_definitions(${Qt5Widgets_DEFINITIONS})	# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

#FIND_PACKAGE(Qt5Core QUIET)
#FIND_PACKAGE(Qt5Widgets QUIET)
#FIND_PACKAGE(Qt5Gui QUIET)
#if(NOT Qt5Core_FOUND AND NOT Qt5Widgets_FOUND AND NOT Qt5Gui_FOUND)
#	message(SEND_ERROR "Failed to find QT")
#	return()
#endif()
######################################################################################################################################

set(SOURCE_LIB checkfile.cpp checkoneline.cpp checktwoline.cpp func.cpp)		# Тоже самое, но для библиотеки

add_library(checkers STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем  checkers

target_link_libraries(checkers ${Qt5Widgets_LIBRARIES}) # The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore
