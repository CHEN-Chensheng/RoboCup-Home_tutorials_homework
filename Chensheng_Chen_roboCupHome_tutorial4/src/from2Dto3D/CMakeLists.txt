cmake_minimum_required(VERSION 2.8.3)
project(from2dto3d)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)


# Catkin
find_package(catkin REQUIRED COMPONENTS
  message_generation
  rospy
  std_msgs
  sensor_msgs
  message_filters
  cv_bridge
  tf
  image_geometry
  perception_msgs
)

catkin_package(CATKIN_DEPENDS message_runtime)


include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)


add_executable(from2dto3d from2Dto3D.cpp)
target_link_libraries(from2dto3d
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
  ${PCL_LIBRARIES}
)

install(TARGETS from2dto3d
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

