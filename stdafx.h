#pragma once




//---------------------------------------------//


#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include <CL/cl.h>
#include <CL/cl_gl.h>


//---------------------------------------------//

#include <GL/glew.h>
#include <GLFW/glfw3.h>


//---------------------------------------------//


#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

//---------------------------------------------//

#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <boost/functional/hash/hash.hpp>
#include <boost/lexical_cast.hpp>

//---------------------------------------------//

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <exception>
#include <time.h>
#include <typeinfo>
#include <cstdlib>
#include <cassert>
#include <stdexcept>
#include <sstream>
#include <typeinfo>
#include <algorithm>
#include <iomanip>
#include <exception>
#include <cstdint>



//---------------------------------------------//

#include <crypt/Blowfish.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/CommonDialogs/ColourPicker/ColourPicker.h>
#include <CEGUI/CEGUI.h>
#include <FreeImage.h>



//---------------------------------------------//

#include <util/view.hpp>
#include <util/math_helper.hpp>
#include <util/string_helper.hpp>
#include <util/file_helper.hpp>
#include <util/utils.hpp>

//---------------------------------------------//

#include <texture/texture.hpp>

//---------------------------------------------//


#include <base/base_data.hpp>
#include <base/base_component.hpp>
#include <base/base_module.hpp>
#include <base/base_state_saver.hpp>
#include <base/base_resource_loader.hpp>
#include <base/base_entity_instance.hpp>
#include <error/error.hpp>


//---------------------------------------------//

#include <shader/shader.hpp>



//---------------------------------------------//

#include <light/light.hpp>



//---------------------------------------------//

#include <filters/basic_filter.hpp>
#include <filters/fxaa.hpp>
#include <filters/g_buffer.hpp>

//---------------------------------------------//


#include <components/general_entity_info_component.hpp>
#include <components/data_component.hpp>

//---------------------------------------------//

#include <ui/ui_util.hpp>
#include <controller/controls_source.hpp>
#include <ui/ui_manager.hpp>
#include <camera_implementation/camera.hpp>
#include <controls.hpp>

//---------------------------------------------//

#include <entity/entity.hpp>

//---------------------------------------------//

#include <entity_instance/entity_instance.hpp>

//---------------------------------------------//

#include <settings/scene_info.hpp>
#include <resource_loader.hpp>
#include <technique.hpp>

//---------------------------------------------//

#include <data_manager.hpp>


//---------------------------------------------//

#include <raytracer/glsl_raytracer.hpp>
#include <CL/cl_util.hpp>
#include <CL/cl_context.hpp>
#include <CL/cl_program.hpp>
#include <CL/cl_kernel.hpp>
#include <raytracer/ray_tracer_scene_builder.hpp>
#include <raytracer/cl_raytracer.hpp>

//---------------------------------------------//

#include <pipeline.hpp>
#include <application.hpp>

//---------------------------------------------//