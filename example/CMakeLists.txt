#Compile the example executable
add_executable(utilc-file-example utilc-file-example.c)
include_directories(../include/)
target_link_libraries(utilc-file-example utilc-file)
