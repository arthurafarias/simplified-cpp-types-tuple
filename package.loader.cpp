
    #include <Models/ProjectDescriptor.hpp>
    using namespace Models;
    extern ProjectDescriptor project;
    // should be a weak reference that can be overriten by a custom get_project // more versatile but unsafe.
    extern "C" const ProjectDescriptor* get_project()  { return &project; }
  