#include <texture.hpp>

Texture::Texture(std::string filepath)
    : m_texture_object{0}, 
        m_texture_width{0}, 
        m_texture_height{0}, 
        m_texture_components{0}
{
    std::unique_ptr<unsigned char> image_data 
        (stbi_load(filepath.c_str(), &m_texture_width, &m_texture_height, &m_texture_components, 0));

    // stbi_load returns null in case of failure
    if (image_data == nullptr)
    {
        std::cout << "Failed to load texture at " << filepath << std::endl;

        // TODO: Better error handling
        exit(-1);
    }

    glGenTextures(1, &m_texture_object);

    // glActiveTexture selects which texture unit subsequent texture state calls will affect.
    // The initial value is GL_TEXTURE0 (texture unit 0), so technically we don't have to call this.
    // But it's good to be explicit.
    glActiveTexture(GL_TEXTURE0);
    
    // Binding our created texture object to GL_TEXTURE_2D means it becomes a 2D texture.
    glBindTexture(GL_TEXTURE_2D, m_texture_object);

    // Set texture wrapping and mipmap filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Creating a storage for a texture and uploading pixels to it is done with glTexImage2D.
    // InternalFormat parameter (Parameter 3) = Tell OpenGL how you want the texture to be stored on the GPU.
    // The External Format is defined by parameters "format", and "type". 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_texture_width, m_texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data.get());

    // OpenGL can automatically generate mipmaps for us by calling glGenerateMipmap. This is typically sufficient for most applications.
    glGenerateMipmap(GL_TEXTURE_2D);

    // Clean up
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::activate()
{
    glBindTexture(GL_TEXTURE_2D, m_texture_object);
}

void Texture::deactivate()
{
    // The texture name 0 refers to the default texture bound at initialization
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::get_width()
{
    return m_texture_width;
}

int Texture::get_height()
{
    return m_texture_height;
}