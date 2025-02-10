//PALMY_FRAGMENT_SHADER
#version 330 core
out vec4 FragColor;
in vec2 TextureCoordinates;
uniform sampler2D uTexture;

void main()
{
	FragColor = vec4(texture(uTexture,TextureCoordinates));
}