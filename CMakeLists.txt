cmake_minimum_required(VERSION 3.10)

project(Garden)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB gardenSrc
	"${CMAKE_CURRENT_SOURCE_DIR}/src/grd/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/grd/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/grd/*.rc"
)

add_executable(${CMAKE_PROJECT_NAME} WIN32 ${gardenSrc})
add_definitions(-DUNICODE)

set(LUAROOT "${CMAKE_SOURCE_DIR}/lua")

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${LUAROOT}/include
)

add_library(luajit SHARED IMPORTED)

set_target_properties(luajit PROPERTIES
	IMPORTED_LOCATION "${LUAROOT}/lib/lua51.dll"
	IMPORTED_IMPLIB "${LUAROOT}/lib/lua51.lib"
	INTERAFCE_INCLUDE_DIRECTORIES "${LUAROOT}/include/"
)

target_link_libraries(${PROJECT_NAME} PRIVATE luajit)
target_compile_definitions(${PROJECT_NAME} PRIVATE LUA_BUILD_AS_DLL)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE luajit)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E echo "Copying data directory..."
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/data
		$<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${LUAROOT}/bin/lua51.dll"
		"$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)

file(COPY img DESTINATION .)