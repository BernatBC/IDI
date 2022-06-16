#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;

const vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;

uniform vec3 posLlum3;
uniform vec3 colLlum1;
uniform vec3 colLlum2;
uniform vec3 colLlum3;

out vec4 FragColor;


vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main()
{
  vec3 fnormal2 = normalize(fnormal);

  vec3 L1 = normalize(vec3(vec4(0, 0, 0, 1.0)) - fvertex);
  vec3 L2 = normalize(vec3(View*vec4(10, 3, 5, 1.0)) - fvertex);
  vec3 L3 = normalize(vec3(View*vec4(posLlum3, 1.0)) - fvertex);

  vec3 fcolor = Ambient() + Difus(fnormal2, L1, colLlum1) + Difus(fnormal2, L2, colLlum2) + Difus(fnormal2, L3, colLlum3) + Especular(fnormal2, L1, fvertex, colLlum1) + Especular(fnormal2, L2, fvertex, colLlum2) + Especular(fnormal2, L3, fvertex, colLlum3);
  FragColor = vec4(fcolor,1);
}
