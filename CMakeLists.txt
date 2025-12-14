cmake_minimum_required(VERSION 3.10)

project(Garden)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB gardenSrc
	"${CMAKE_CURRENT_SOURCE_DIR}/src/grd/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/grd/*.cpp"
)

add_executable(${CMAKE_PROJECT_NAME} WIN32 ${gardenSrc})
add_definitions(-DUNICODE)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (WIN32)
	target_link_libraries(${CMAKE_PROJECT_NAME} user32 gdi32)
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E echo "Copying Data Directory..."
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/data
		$<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)