cmake_minimum_required(VERSION 3.16)
project(program)

set(CMAKE_CXX_STANDARD 14)
SET(PROJEKAT_SOURCE_FILES
	Main.cpp
	Stringovi.cpp
	Lista.cpp
	Torka.cpp
	Interpreter.cpp
	)
	

	
add_executable(run ${PROJEKAT_SOURCE_FILES})


