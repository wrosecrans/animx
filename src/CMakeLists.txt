set(SOURCE_FILES
	"animx.cpp"
	"animx.h"
	"internal/nurbs.h"
	"internal/interpolators.h"
	"internal/math.h"
	"internal/T4DblMatrix.h"
	"internal/T4DblVector.h"
	"internal/Tbezier.h"
	"internal/Tquaternion.h"
	"internal/TrotateXYZ.h"
)

set(MAYA_ANIMATION_INCLUDE ${PROJECT_SOURCE_DIR}/src CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

add_library(${PROJECT_NAME}_shared SHARED ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME}_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}_shared PROPERTIES COMPILE_DEFINITIONS ANIMX_EXPORT)

add_library(${PROJECT_NAME}_static STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME}_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
if (MSVC)
    set_target_properties(${PROJECT_NAME}_static PROPERTIES PREFIX lib)
endif()
set_target_properties(${PROJECT_NAME}_static PROPERTIES COMPILE_DEFINITIONS ANIMX_STATIC)

if(NOT ANIMX_BUILD_SHARED)
    set_target_properties(${PROJECT_NAME}_shared PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()
if(NOT ANIMX_BUILD_STATIC)
    set_target_properties(${PROJECT_NAME}_static PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()

install(FILES animx.h DESTINATION include)

install(TARGETS ${PROJECT_NAME}_shared
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION .
        RUNTIME DESTINATION bin)

install(TARGETS ${PROJECT_NAME}_static
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION .
        RUNTIME DESTINATION bin)
