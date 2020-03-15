#version 430 core

uniform vec3 objectColor;
uniform vec3 lightDir;
uniform sampler2D objectTex;

uniform sampler2D tek;
uniform sampler2D tek2;


in vec3 interpNormal;
in vec2 texPosition;
in vec2 vertexTexCoord1;
in vec2 vertexTexCoord2;


void main()
{
	vec3 normal = normalize(interpNormal);
	float diffuse = max(dot(normal, -lightDir), 0.0);

        //vec4 textureColor = texture2D(tek, vertexTexCoord1);
 	vec4 textureColor2 = texture2D(tek2, vertexTexCoord2);
	vec4 textureColor = texture2D(objectTex, vec2(texPosition.x, 1 - texPosition.y));


	gl_FragColor = vec4(textureColor.rgb * diffuse, 1.0);
        
}
