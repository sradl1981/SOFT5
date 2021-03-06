project (soft-storage-plugins-hdf5 C CXX)

set (CMAKE_THREAD_PREFER_PTHREAD TRUE)
set (CMAKE_AUTOMOC TRUE)

include_directories (${soft-storage-hdf5_INCLUDE_DIRS})
set (LINK_LIBS ${LINK_LIBS} ${soft-storage-hdf5_LIBS})

aux_source_directory (. SRC_LIST)
add_definitions(-DQT_PLUGIN)
add_library (${PROJECT_NAME} SHARED ${SRC_LIST})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_constexpr)
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})

set(${PROJECT_NAME}_INCLUDE_DIRS
  ${soft-storage-hdf5_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}
  CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)


install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${STORAGE_PLUGINS_INSTALL_DIR}
  LIBRARY DESTINATION ${STORAGE_PLUGINS_INSTALL_DIR})

install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_INSTALL_PREFIX}/${STORAGE_PLUGINS_INSTALL_DIR}/lib${PROJECT_NAME}.so ${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}/lib${PROJECT_NAME}.so )")
install(CODE "MESSAGE(\"-- Created symlink: ${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}/lib${PROJECT_NAME}.so -> ${CMAKE_INSTALL_PREFIX}/${STORAGE_PLUGINS_INSTALL_DIR}/lib${PROJECT_NAME}.so  \")")
