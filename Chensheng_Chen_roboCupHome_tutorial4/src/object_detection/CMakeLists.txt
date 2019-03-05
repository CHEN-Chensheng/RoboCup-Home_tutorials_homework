cmake_minimum_required(VERSION 2.8.3)
project(object_detection)


set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS  
  roscpp
  rospy
  std_msgs
  darknet_ros_msgs
  cv_bridge
  image_transport
  tf
  image_geometry
  perception_msgs
)
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)
find_package(darknet_ros_msgs REQUIRED)

#add_message_files(FILES ObjectDetection.msg)
#add_service_files(FILES DetectObject.srv)
#generate_messages(DEPENDENCIES std_msgs)



catkin_package()
## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}  
)







#add_message_files(
#   DIRECTORY msg
#   FILES

#   BoundingBoxes.msg
#)

##include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(
  ${PCL_INCLUDE_DIRS}
)


## Declare a cpp executable
#add_executable(object_clustering src/ObjectClustering.cpp)
add_executable(object_detection src/object_recognition.cpp)
#add_executable(detection src/object_recognition.cpp)
## Specify libraries to link a library or executable target against
target_link_libraries(object_detection ${catkin_LIBRARIES} ${OpenCV_LIBS} ${PCL_LIBRARIES})
#target_link_libraries(detection ${catkin_LIBRARIES} ${OpenCV_LIBS} ${PCL_LIBRARIES})
#target_link_libraries(object_classifier ${catkin_LIBRARIES} ${OpenCV_LIBS} ${PCL_LIBRARIES})




