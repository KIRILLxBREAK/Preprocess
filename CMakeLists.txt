cmake_minimum_required(VERSION 3.0.0) # Проверка версии CMake.
				
project(preprocess)			# Название проекта

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


set(SOURCE_EXE main.cpp mainwindow.h mainwindow.cpp)		# Установка переменной со списком исходников для исполняемого файла

include_directories(checkers)	

add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main

add_subdirectory(checkers)	

target_link_libraries(main ${Qt5Widgets_LIBRARIES}) # The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore

target_link_libraries(main checkers)		# Линковка программы с библиотекой

