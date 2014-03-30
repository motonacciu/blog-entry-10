cmake_minimum_required (VERSION 2.8) 
project (blog) 

# CHECKs if a C++11 compiler is available
if(CMAKE_COMPILER_IS_GNUCXX)
	execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
	if (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
		message(STATUS "C++11 activated.")
		add_definitions("-std=c++11")
	else ()
		message(FATAL_ERROR "C++11 needed. Therefore a gcc compiler with a version higher than 4.3 is needed.")   
	endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	add_definitions("-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

include_directories(${CMAKE_SOURCE_DIR})

# set a temporary dir for Flex and Yacc generated files 
set(TMP_DIR "generated")

# make a dir to store the temporary files 
file(MAKE_DIRECTORY ${TMP_DIR})

find_package(BISON REQUIRED)
set(BisonOutput ${TMP_DIR}/parser.cpp ${CMAKE_SOURCE_DIR}/parser.h)
set(BisonSpecFile parser.y)
if(BISON_FOUND)
    add_custom_command(
		OUTPUT ${BisonOutput}
		COMMAND ${BISON_EXECUTABLE}
				--defines=${CMAKE_SOURCE_DIR}/parser.h
        		--output=${TMP_DIR}/parser.cpp
				${BisonSpecFile}
		DEPENDS ${BisonSpecFile}
		COMMENT "Generating ${BisonOutput}"
		VERBATIM
    )
endif()

find_package(FLEX REQUIRED)
set(FlexOutput ${TMP_DIR}/lexer.cpp)
set(FlexSpecFile lexer.ll)
if(FLEX_FOUND)
    add_custom_command(
      	OUTPUT ${FlexOutput}
      	COMMAND ${FLEX_EXECUTABLE}
            	--outfile=${FlexOutput}
				${FlexSpecFile}
		DEPENDS ${FlexSpecFile} ${BisonOutput}
		COMMENT "Generating ${FlexOutput}"
		VERBATIM
    )
endif()

add_executable(main1 ${CMAKE_CURRENT_SOURCE_DIR}/main1.cpp)

add_executable(main2 ${CMAKE_CURRENT_SOURCE_DIR}/main2.cpp ${BisonOutput} ${FlexOutput})
