set(particles_src_files
        Particle.h Food.cpp Food.h)
add_library(particles ${particles_src_files})
set_target_properties(particles PROPERTIES LINKER_LANGUAGE CXX)
