#include <Models/Target.hpp>
#include <Models/Project.hpp>

auto example = Models::Target()
                   .name_set("tuple")
                   .version_set("1.0.0")
                   .type_set("executable")
                   .sources_append({"src/main.cpp"})
                   .options_append({"-fPIE", "-fstack-protector-all", "-O0", "-g"})
                   .link_libraries_append({"m"})
                   .include_directories_append({"src"})
                   .create();

auto project = Models::Project().add(example).create();