#include "Texture.h"

Texture::Texture() : width(0), height(0), format_image(GL_RGBA), format_tex(GL_RGBA), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR),Filter_Max(GL_LINEAR) {
	glGenTextures(1, &idTex);
}

void Texture::generate(const char* path) {
	
	stbi_set_flip_vertically_on_load(false);
	glBindTexture(GL_TEXTURE_2D, idTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data) {
		if (nrChannels == 1)
			format_image = GL_RED;
		else if (nrChannels == 3)
			format_image = GL_RGB;
		else if (nrChannels == 4)
			format_image = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format_tex, width, height, 0, format_image, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);

	}
	else {
		std::cout << " echec de lecture de texture a l'adresse : " << path << std::endl;
	}
}
void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, idTex);
}