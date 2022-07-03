#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;
uniform sampler2D theTexture;
uniform bool hasTexture;
void main()
{
	if(hasTexture){
		FragColor = texture(theTexture, TexCoord) * vec4(1.0,1.0,1.0,1.0);
	}
	else{
		FragColor = ourColor;
	}
}