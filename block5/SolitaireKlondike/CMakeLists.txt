cmake_minimum_required(VERSION 3.7)
project(SolitaireKlondike)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        include/Card.h
        src/CardDeck.cpp include/CardDeck.h
        include/FoundationStack.h src/Foundation.cpp
        include/Foundation.h
        include/Tableau.h
        src/Waste.cpp include/Waste.h
        include/CardContainer.h
        src/FoundationStack.cpp
        src/TableauStack.cpp include/TableauStack.h
        src/CardContainer.cpp)

add_executable(SolitaireKlondike_exe main.cpp)
add_library(SolitaireKlondike_lib SHARED ${SOURCE_FILES})

target_link_libraries(SolitaireKlondike_exe SolitaireKlondike_lib)

add_subdirectory(test)