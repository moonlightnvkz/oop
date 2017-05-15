cmake_minimum_required(VERSION 3.7)
project(SolitaireKlondike)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        include/model/Card.h
        src/model/CardDeck.cpp include/model/CardDeck.h
        include/model/FoundationStack.h src/model/Foundation.cpp
        include/model/Foundation.h
        include/model/Tableau.h
        src/model/Waste.cpp include/model/Waste.h
        include/model/CardContainer.h
        src/model/FoundationStack.cpp
        src/model/TableauStack.cpp include/model/TableauStack.h
        src/model/CardContainer.cpp src/controller/Controller.cpp
        include/controller/Controller.h src/model/CardContainerIterator.cpp include/model/CardContainerIterator.h)

add_executable(SolitaireKlondike_exe main.cpp)
add_library(SolitaireKlondike_lib SHARED ${SOURCE_FILES})

target_link_libraries(SolitaireKlondike_exe SolitaireKlondike_lib)

add_subdirectory(test)