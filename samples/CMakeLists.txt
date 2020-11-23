include_directories(${AIOUSB_SOURCE_DIR}/include)

set(AIOUSB_LIBS ${AIOUSB_BINARY_DIR}/aiousb/libaiousb.a m pthread udev)

add_executable(AiousbDioSample AiousbDioSample.cpp)
target_link_libraries(AiousbDioSample ${AIOUSB_LIBS})

add_executable(AiousbDioStreamOutSample AiousbDioStreamOutSample.cpp)
target_link_libraries(AiousbDioStreamOutSample ${AIOUSB_LIBS})

add_executable(AiousbDioStreamInSample AiousbDioStreamInSample.cpp)
target_link_libraries(AiousbDioStreamInSample ${AIOUSB_LIBS})
