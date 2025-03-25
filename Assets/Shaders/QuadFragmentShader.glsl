#version 330 core
out vec4 FragColor;
in vec2 TextureCoordinates;
uniform sampler2D uTexture;
uniform vec4 uColor;
void main()
{
	FragColor = vec4(texture(uTexture,vec2(1-TextureCoordinates.x,TextureCoordinates.y))) * uColor;
}