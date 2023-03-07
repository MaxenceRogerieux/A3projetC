cmake_minimum_required(VERSION 3.13)
project(A3projetC)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories("CDM v2.12.36.4 WHQL Certified")

add_executable(A3projetC
        "CDM v2.12.36.4 WHQL Certified/ftd2xx.h"

        consigne.c
        consigne.h
        define.h
        regulation.c
        regulation.h
        visualisationC.c
        visualisationC.h
        visualisationT.c
        visualisationT.h
        simulateur.c
        simulateur.h
        autotests.c
        autotests.h
        test_simulateur.c
        )
