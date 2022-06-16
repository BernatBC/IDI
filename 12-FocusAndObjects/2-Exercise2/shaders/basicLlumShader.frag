#version 330 core

//in vec3 fcolor;
out vec4 FragColor;

in vec3 fmatamb;
in vec3 fmatdiff;
in vec3 fmatspec;
in float fmatshin;

in vec4 vertSCO;
in vec3 NormSCO;

in vec3 fvertex;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;
uniform vec3 posFocus;
uniform vec3 colorFocus;

uniform int f;

vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

vec3 Ambient() {
    return llumAmbient * fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
    // Fixeu-vos que SOLS es retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * fmatdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus)
{
    // Fixeu-vos que SOLS es retorna el terme especular!
    // Assumim que els vectors estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular

    float shine = pow(max(0.0, dot(R, V)), fmatshin);
    return (fmatspec * colFocus * shine);
}

void main()
{
  vec3 L1 = vec3(vec4(0, 0, 0, 1.0) ) - vec3( view * TG * vec4 (fvertex, 1.0) );
  vec3 L2 = vec3(view * vec4(posFocus, 1.0) ) - vec3( view * TG * vec4 (fvertex, 1.0) );

	L1 = normalize (L1);
  L2 = normalize (L2);

	vec3 NormSCO2 = normalize (NormSCO);

  vec3 fcolor = Ambient() + Difus(NormSCO2, L1, colorFocus) + Difus(NormSCO2, L2, colorFocus) + Especular(NormSCO2, L1, vertSCO ,colorFocus) + Especular(NormSCO2, L2, vertSCO ,colorFocus);

  FragColor = vec4(fcolor,1);
}
