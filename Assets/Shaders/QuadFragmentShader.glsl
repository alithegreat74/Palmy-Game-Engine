#version 330 core
out vec4 FragColor;
in vec2 TextureCoordinates;
in vec4 Color;
uniform sampler2D uTexture[32];
flat in int TextureNumber;
void main()
{
	if(TextureNumber < 0 || TextureNumber >= 32)
		FragColor = Color;
	else
		FragColor = vec4(texture(uTexture[TextureNumber],vec2(1-TextureCoordinates.x, TextureCoordinates.y))) * Color;

}