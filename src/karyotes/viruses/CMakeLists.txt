set(viruses_src_files Virus.h Virus.cpp)
add_library(viruses ${viruses_src_files})
set_target_properties(viruses PROPERTIES LINKER_LANGUAGE CXX)
