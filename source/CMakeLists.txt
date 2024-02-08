
add_library( Cell ${CMAKE_CURRENT_SOURCE_DIR}/Cell.cc )
target_include_directories( Cell INTERFACE ${PROJECT_SOURCE_DIR}/include
			    PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_library( NineCell ${CMAKE_CURRENT_SOURCE_DIR}/NineCell.cc )
target_include_directories( NineCell INTERFACE ${PROJECT_SOURCE_DIR}/include
			    PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_library( Ternary ${CMAKE_CURRENT_SOURCE_DIR}/Ternary.cc )
target_include_directories( Ternary INTERFACE ${PROJECT_SOURCE_DIR}/include
			    PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_library( Grid ${CMAKE_CURRENT_SOURCE_DIR}/Grid.cc )
target_include_directories( Grid INTERFACE ${PROJECT_SOURCE_DIR}/include
			    PRIVATE ${PROJECT_SOURCE_DIR}/include )
