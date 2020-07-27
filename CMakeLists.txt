cmake_minimum_required(VERSION 3.15)
project(fdf_new C)

set(CMAKE_C_STANDARD 90)

add_executable(fdf_new src/main.c inc/fdf.h src/read_map.c src/ft_atoi_base.c src/hook.c src/mlx_put_line.c src/projection.c src/event_handler.c src/print_image.c)
target_include_directories(fdf_new PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(fdf_new PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(fdf_new PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Libft/inc)
#find_library(FT ft)
set(FT ${CMAKE_CURRENT_SOURCE_DIR}/Libft/libft.a)
target_link_libraries(fdf_new ${FT})

target_include_directories(fdf_new PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/minilibx_macos/inc)
#find_library(MLX mlx)
set(MLX ${CMAKE_CURRENT_SOURCE_DIR}/minilibx_macos/libmlx.a)
target_link_libraries(fdf_new ${MLX})

target_link_libraries(fdf_new "-framework OpenGL")

target_link_libraries(fdf_new "-framework AppKit")