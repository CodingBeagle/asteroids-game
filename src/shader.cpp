#include <shader.hpp>

Shader::Shader(GLuint shader_type, std::string shader_source_code)
    : m_shader_object_id{0}
{
    // TODO: Proper error handling for this entire class
    m_shader_object_id = glCreateShader(shader_type);

    const char *shader_source_c_str = shader_source_code.c_str();

    glShaderSource(m_shader_object_id, 1, &shader_source_c_str, nullptr);

    glCompileShader(m_shader_object_id);

    // glGetShaderiv can be used to return a parameter from a shader object.
    // Here we get the compilation status.
    GLint compilation_status;
    glGetShaderiv(m_shader_object_id, GL_COMPILE_STATUS, &compilation_status);

    if (compilation_status != GL_TRUE) 
    {
        std::cout << "Failed to compile shader" << std::endl;

        print_compilation_log();

        exit(-1);
    }
}

Shader::~Shader()
{
    glDeleteShader(m_shader_object_id);
    m_shader_object_id = 0;
}

GLuint Shader::get_object_id()
{
    return m_shader_object_id;
}

void Shader::print_compilation_log()
{
    GLint log_length = 0;

    // Get the length of the info log
    glGetShaderiv(m_shader_object_id, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 0)
    {
        // glGetShaderInfoLog will return the info log for our shader object
        GLsizei info_log_character_length = 0;

        std::unique_ptr<GLchar[]> log_content(new GLchar[log_length]);

        glGetShaderInfoLog(m_shader_object_id, log_length, &info_log_character_length, log_content.get());

        std::cout << "Shader Info Log:" << std::endl;
        std::cout << log_content << std::endl;

        exit(-1);
    }
}