#include <filehelper.h>

std::string read_text_file(std::string filepath)
{
    std::ifstream file_handle(filepath);
    std::string file_content;

    // TODO: Need proper error handling mechanism here
    if (file_handle.is_open())
    {
        std::stringstream buffer;
        buffer << file_handle.rdbuf();
        file_content = std::string(buffer.str());
        file_handle.close();
    }

    return file_content;
}