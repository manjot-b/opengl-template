#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Texture.h"

Texture::Texture(const char* filename)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data)
    {
		std::cout << "Failed to load texture: " << filename << std::endl;
    }

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	// tells opengl not to assume any alignment of rows.
    switch (nrChannels)
    {
        case 1: 
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
            break;
        case 2: 
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
            break;
        case 3: 
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;     
    }

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);	
}

unsigned int Texture::getId() const
{
	return id;
}

int Texture::getWidth() const
{
	return width;
}

int Texture::getHeight() const
{
	return height;
}

/**
 *	Sets the current active texture to the one specified in the parameter,
 *	and then binds the texture.
 */
void Texture::bind(GLenum texture) const
{
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, id);	
}
