cmake_minimum_required(VERSION 3.10)
project(SportShopApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем строгие флаги компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

# Настройки FTXUI
set(FTXUI_BUILD_DOCS OFF)
set(FTXUI_BUILD_TESTS OFF)
set(FTXUI_BUILD_EXAMPLES OFF)

# Подключаем FTXUI
add_subdirectory(FTXUI)

# Создаем исполняемый файл
add_executable(SportShopApp 
    app/src/main/main.cpp
)

# Линковка библиотек FTXUI
target_link_libraries(SportShopApp 
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)

# Указываем include директории
target_include_directories(SportShopApp PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/app/include
)