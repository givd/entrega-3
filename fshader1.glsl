#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec4 color;
IN vec2 v_texcoord;

struct tipusLlum
{
 vec4 LightPosition;
 vec3 Ld;
 float coef_a; // Aqui s'han de definir tots els atributs d'una llum
};

uniform tipusLlum light;

uniform sampler2D texMap;

void main()
{
  gl_FragColor = texture2D(texMap, v_texcoord);
  //gl_FragColor = color;
}

