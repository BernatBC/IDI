#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

out vec3 fvertex;

out vec4 vertSCO;
out vec3 NormSCO;

out vec3 fmatamb;
out vec3 fmatdiff;
out vec3 fmatspec;
out float fmatshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;
uniform vec3 posFocus;
uniform vec3 colorFocus;
uniform vec3 colorFocusAmb;

uniform int f;

// Valors per als components que necessitem del focus de llum
//vec3 colorFocus = vec3(0.8, 0.8, 0.8);

//vec3 posFocus = vec3(1, 0, 1);  // en SCA

out vec3 fcolor;

void main()
{

  fmatamb = matamb;
  fmatdiff = matdiff;
  fmatspec = matspec;
  fmatshin = matshin;

  fvertex = vertex;

  	mat3 NM = inverse( transpose( mat3(view*TG) ) );
  NormSCO = NM * normal;
  vertSCO = view * TG * vec4(vertex, 1.0);

  gl_Position = proj * vertSCO;
}
