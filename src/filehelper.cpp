#include <filehelper.h>

std::string read_text_file(std::string filepath)
{
    std::ifstream vertex_shader_file(filepath);
    std::string vertex_shader_source_code;

    // TODO: Need proper error handling mechanism here
    if (vertex_shader_file.is_open())
    {
        std::stringstream buffer;
        buffer << vertex_shader_file.rdbuf();
        vertex_shader_source_code = std::string(buffer.str());
    }

    return vertex_shader_source_code;
}