set(codons_src_files
        Codon.h Codon.cpp LoopCodon.cpp LoopCodon.h)
add_library(codons ${codons_src_files})
target_link_libraries(codons PRIVATE)
