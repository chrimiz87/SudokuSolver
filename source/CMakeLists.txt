####
## object libraries
####

add_library( Cell OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/Cell.cc )
target_include_directories( Cell PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_library( NineCell OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/NineCell.cc )
target_include_directories( NineCell PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_library( Ternary OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/Ternary.cc )
target_include_directories( Ternary PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_library( Grid OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/Grid.cc )
target_include_directories( Grid PRIVATE ${PROJECT_SOURCE_DIR}/include )

####
## static libraries
####

add_library( NineCellLibrary STATIC $<TARGET_OBJECTS:NineCell> $<TARGET_OBJECTS:Cell> )
target_include_directories( NineCellLibrary INTERFACE ${PROJECT_SOURCE_DIR}/include )

add_library( GridLibrary STATIC $<TARGET_OBJECTS:Grid> $<TARGET_OBJECTS:Ternary> $<TARGET_OBJECTS:NineCell> $<TARGET_OBJECTS:Cell> )
target_include_directories( GridLibrary INTERFACE ${PROJECT_SOURCE_DIR}/include )
