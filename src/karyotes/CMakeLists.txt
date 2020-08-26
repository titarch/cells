add_subdirectory(particles)
add_subdirectory(viruses)
add_subdirectory(codons)

set(karyotes_src_files
        Cell.h LoopCell.cpp LoopCell.h)
add_library(karyotes ${karyotes_src_files})

target_link_libraries(karyotes PRIVATE particles viruses codons)