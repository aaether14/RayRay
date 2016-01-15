cmake_minimum_required(VERSION 3.0)



project(RayRay)
set (RayRay_VERSION_MAJOR 1)
set (RayRay_VERSION_MINOR 0)


#-------------------------------------------------------



#Basic



if(UNIX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(UNIX)


include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/common")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
include (cotire)





#--------------------------------------------------------



#Sources


file(GLOB_RECURSE Sources *.cpp *.hpp *.c *.h)
ADD_EXECUTABLE(RayRay  ${Sources})




#--------------------------------------------------------




#OpenGL



   find_package(OpenGL REQUIRED)
   
   
  include_directories(${OPENGL_INCLUDE_DIRS})
  target_link_libraries(RayRay ${OPENGL_LIBRARIES})



#-------------------------------------------------------


#OpenCL


find_package(OpenCL REQUIRED)


  include_directories(${OpenCL_INCLUDE_DIRS})
  target_link_libraries(RayRay ${OpenCL_LIBRARIES})



#-------------------------------------------------------


#GLEW


 find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
	  target_link_libraries(RayRay ${GLEW_LIBRARIES})



#-------------------------------------------------------


#GLFW


 find_package(PkgConfig REQUIRED)
  pkg_search_module(GLFW REQUIRED glfw3)
   include_directories(${GLFW_INCLUDE_DIRS})
    target_link_libraries(RayRay ${GLFW_STATIC_LIBRARIES})


#------------------------------------------------------


#GLM


find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})


#------------------------------------------------------


#Boost

find_package(Boost COMPONENTS system filesystem python thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(RayRay ${Boost_LIBRARIES})


#------------------------------------------------------


#CEGUI


 find_package(CEGUI REQUIRED)
    include_directories(${CEGUI_INCLUDE_DIR})
    target_link_libraries(RayRay ${CEGUI_LIBRARY})


#-----------------------------------------------------


#FreeImage


find_package(FreeImage REQUIRED)
include_directories(${FREEIMAGE_INCLUDE_DIRS})
target_link_libraries(RayRay ${FREEIMAGE_LIBRARIES})


#-----------------------------------------------------


#Python

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(RayRay ${PYTHON_LIBRARIES})



#----------------------------------------------------


set_target_properties(RayRay PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "stdafx.h")
cotire(RayRay)






