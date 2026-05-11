cmake_minimum_required(VERSION 3.29)
project(Proyecto_Matematicas_Discretas_S1_2026 C)
# TPDO: Probar compilacion con gcc porque la profe no va a usar cmake xd
set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Proyecto_Matematicas_Discretas_S1_2026
    estructuras.h
    main.c)
