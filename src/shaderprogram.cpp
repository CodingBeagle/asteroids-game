#include <shaderprogram.hpp>

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader)
    : m_shader_program_object_id{0}
{
    // TODO: Proper error handling missing
    // - What if program creation fails?
    // - What if the supplied shaders aren't really vertex and fragment? Check for type. 
    m_shader_program_object_id = glCreateProgram();

    glAttachShader(m_shader_program_object_id, vertexShader.get_object_id());
    glAttachShader(m_shader_program_object_id, fragmentShader.get_object_id());

    glLinkProgram(m_shader_program_object_id);

    GLint link_status{0};
    glGetProgramiv(m_shader_program_object_id, GL_LINK_STATUS, &link_status);

    if (link_status == GL_FALSE)
    {
        std::cout << "Failed to link shader program." << std::endl;

        GLint log_length {0};

        // Get the length of the link log
        glGetProgramiv(m_shader_program_object_id, GL_INFO_LOG_LENGTH, &log_length);

        if (log_length > 0)
        {
            std::unique_ptr<GLchar[]> info_log(new GLchar[log_length]);

            glGetProgramInfoLog(m_shader_program_object_id, log_length, nullptr, info_log.get());

            std::cout << "****Program Info Log****" << std::endl;
            std::cout << info_log << std::endl;
        }

        exit(-1);
    }
};

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_shader_program_object_id);
    m_shader_program_object_id = 0;
}

void ShaderProgram::activate()
{
    glUseProgram(m_shader_program_object_id);
}

void ShaderProgram::deactivate()
{
    glUseProgram(0);
}