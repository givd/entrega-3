#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

struct Llum
{
    int tipus;

    vec3 color;
    float at_a;
    float at_b;
    float at_c;

    vec4 position;
    vec3 direction;
    float angle;
};

struct Material {
    vec4 Ka;
    vec4 Ks;
    vec4 Kd;
    float cre;
};

IN vec4 vPosition;
IN vec4 vColor;
IN vec2 vCoordTexture;
uniform mat4 model_view;
uniform mat4 projection;

OUT vec4 color;
OUT vec2 v_texcoord;

uniform Llum llum;
uniform Material material;

void main()
{
  gl_Position = projection * model_view *  vPosition;
  //color = vColor;
  color = vec4(llum.color.x, llum.color.y, llum.color.z, 1.0);
  v_texcoord = vCoordTexture;
}
