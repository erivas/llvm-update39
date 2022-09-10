add_library(Update39 MODULE
    update39.cpp
)
target_compile_features(Update39 PRIVATE cxx_range_for cxx_auto_type)
set_target_properties(Update39 PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)
