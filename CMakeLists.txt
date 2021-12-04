set(SUPPORT_BC7E ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/bc7e.o ${CMAKE_CURRENT_BINARY_DIR}/bc7e_avx.o ${CMAKE_CURRENT_BINARY_DIR}/bc7e_sse2.o ${CMAKE_CURRENT_BINARY_DIR}/bc7e_sse4.o ${CMAKE_CURRENT_BINARY_DIR}/bc7e_avx2.o
        COMMAND ispc --pic -g -O2 ${CMAKE_CURRENT_SOURCE_DIR}/bc7e.ispc -o ${CMAKE_CURRENT_BINARY_DIR}/bc7e.o -h ${CMAKE_CURRENT_BINARY_DIR}/bc7e_ispc.h --target=sse2,sse4,avx,avx2 --opt=fast-math --opt=disable-assertions
										 	DEPENDS bc7e.ispc)
# -fno-strict-aliasing shouldn't be necessary, it's here because that is what MSVC uses by default and that's what I've tested with the most.
set(GCC_COMPILE_FLAGS "-fno-strict-aliasing -Wall -Wextra -fopenmp")

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COMPILE_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE  "${CMAKE_C_FLAGS_RELEASE} ${GCC_COMPILE_FLAGS}")
set(CMAKE_C_FLAGS_RELWITHDEBINFO  "${CMAKE_C_FLAGS_RELWITHDEBINFO} ${GCC_COMPILE_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${GCC_COMPILE_FLAGS} -D_DEBUG")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} -DSUPPORT_BC7E=1")

set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} ${GCC_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${GCC_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${GCC_COMPILE_FLAGS} -D_DEBUG")

set (BC7ENC_SRC_LIST ${COMMON_SRC_LIST}
	bc7enc.cpp
	bc7enc.h
	bc7decomp.cpp
	bc7decomp_ref.cpp
	bc7decomp.h
	lodepng.cpp	
	lodepng.h
	lib.cpp
	rgbcx.cpp
	rgbcx.h
	rgbcx_table4.h
	rgbcx_table4_small.h
	utils.cpp
	utils.h
	miniz.h
	dds_defs.h
	ert.cpp
	ert.h
	rdo_bc_encoder.cpp
	rdo_bc_encoder.h
	bc7e.ispc
	)

add_library(bc7enc STATIC ${BC7ENC_SRC_LIST} ${CMAKE_CURRENT_BINARY_DIR}/bc7e.o ${CMAKE_CURRENT_BINARY_DIR}/bc7e_avx.o ${CMAKE_CURRENT_BINARY_DIR}/bc7e_avx2.o ${CMAKE_CURRENT_BINARY_DIR}/bc7e_sse2.o ${CMAKE_CURRENT_BINARY_DIR}/bc7e_sse4.o)

target_include_directories(bc7enc PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(bc7enc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (NOT MSVC)
	target_link_libraries(bc7enc m)
endif()


