#version 330 core
out vec4 FragColor;
in vec2 TextureCoordinates;
in vec4 Color;
uniform sampler2D uTexture;
void main()
{
	//FragColor = vec4(texture(uTexture,vec2(1-TextureCoordinates.x,TextureCoordinates.y))) * Color;
	FragColor = Color;
}