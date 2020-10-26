import os
import shutil
import inspect
import subprocess

from pathlib import Path

PROJECT_PATH = os.path.dirname(os.getcwd())

VCPKG_PATH = f'{PROJECT_PATH}/vcpkg/vcpkg.exe'
VCPKG_GIT_CMD = f'git clone https://github.com/microsoft/vcpkg {os.path.join(PROJECT_PATH, "vcpkg")}'
VCPKG_BOOTSTRAP = f'{PROJECT_PATH}/vcpkg/bootstrap-vcpkg.bat'

ALLOWED_DIRS = ["src", ".git"]
ALLOWED_FILES = [".txt" ".cpp", ".bat", ".hpp", ".h",
                 ".json", ".md", ".py", ".gitignore", ".gitattributes"]


def remove_build_files():
    root = os.getcwd()

    for item in os.listdir(root):
        path = os.path.join(root, item)

        if os.path.isdir(path):
            if item not in ALLOWED_DIRS:
                shutil.rmtree(path)

        elif os.path.isfile(path):
            if item in ALLOWED_FILES:
                continue

            suffix = Path(path).suffix

            if suffix not in ALLOWED_FILES:
                os.remove(path)


def gen_cmake_script() -> str:
    script: str = """
    cmake_minimum_required(VERSION 3.16.0)
    set(CMAKE_TOOLCHAIN_FILE \"../vcpkg/scripts/buildsystems/vcpkg.cmake\")
    
    project(Ubiorbitapi_r2_loader)
    
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(VERSION 1.0.0)
    
    file(GLOB_RECURSE CPP_HPP_FILES \"src/*.cpp\" \"src/*.hpp\" \"src/*.h\")
    add_library(Ubiorbitapi_r2_loader SHARED ${CPP_HPP_FILES})
    
    set_target_properties(Ubiorbitapi_r2_loader PROPERTIES OUTPUT_NAME \"ubiorbitapi_r2_loader\")
    
    find_package(string_theory CONFIG REQUIRED)
    target_link_libraries(Ubiorbitapi_r2_loader PRIVATE string_theory)
    
    find_package(cereal CONFIG REQUIRED)
    target_include_directories(Ubiorbitapi_r2_loader PRIVATE cereal)
    
    find_package(date CONFIG REQUIRED)
    target_include_directories(Ubiorbitapi_r2_loader PRIVATE date::date date::date-tz)
    
    find_path(PLOG_INCLUDE_DIRS \"plog/Appenders/AndroidAppender.h\")
    target_include_directories(Ubiorbitapi_r2_loader PRIVATE ${PLOG_INCLUDE_DIRS}) 
    
    find_package(fmt CONFIG REQUIRED)
    target_link_libraries(Ubiorbitapi_r2_loader PRIVATE fmt::fmt fmt::fmt-header-only)
    
    target_include_directories(Ubiorbitapi_r2_loader PRIVATE ${CMAKE_SOURCE_DIR})
    target_precompile_headers(Ubiorbitapi_r2_loader PUBLIC \"src/pch.h\")
    
    target_compile_definitions(Ubiorbitapi_r2_loader PRIVATE WIN32_LEAN_AND_MEAN)
    target_compile_definitions(Ubiorbitapi_r2_loader PRIVATE NOMINMAX)
    """

    return script


def execute(cmd: str):
    result = subprocess.run(cmd)

    if result.stderr is not None and len(result.stderr) > 0:
        raise Exception(str(result.stderr))


def main():
    remove_build_files()

    if not os.path.isfile(VCPKG_PATH):
        execute(VCPKG_GIT_CMD)
        execute(VCPKG_BOOTSTRAP)

    execute(f'{VCPKG_PATH} install string-theory')
    execute(f'{VCPKG_PATH} install cereal')
    execute(f'{VCPKG_PATH} install date')
    execute(f'{VCPKG_PATH} install plog')
    execute(f'{VCPKG_PATH} install fmt')

    cmake_script = gen_cmake_script()

    cmake_file = open('CMakeLists.txt', 'w+')
    cmake_file.write(inspect.cleandoc(cmake_script))


if __name__ == "__main__":
    main()
