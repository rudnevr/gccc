cmake_minimum_required(VERSION 3.6)
project(gccc)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        .idea/gccc.iml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        .vs/gccc/v15/ipch/AutoPCH/d10716f29353ce97/MAIN.ipch
        .vs/gccc/v15/Browse.VC.db
        .vs/ProjectSettings.json
        .vs/slnx.sqlite
        .vs/VSWorkspaceState.json
        .gitignore
        a.exe
        CMakeLists.txt
        hook.o
        input.txt
        "main - Shortcut.lnk"
        main.c
        main.exe
        main.o
        Makefile
        out.exe
        README.md
        up_down.o)

add_executable(gccc ${SOURCE_FILES})