#version 460

uniform mat4 MVP;
uniform int sequenceIndex;
in vec3 vPos;


out vec3 vcColor;


layout(std430, binding = 3) buffer sequences
{
    ivec2 reflectionSequences[];
};

struct Lens{
    float curvatureRadius;
    float thickness;
    float ior;
    float apertureRadius;
    float center;
};

layout(std430, binding = 4) buffer lensSystem
{
    Lens lenses[];
};

struct Intersection{
    vec3 position;
    vec3 normal;
};

Intersection intersectLens(inout Lens lens, vec3 position, vec3 direction)  {
    vec3 D = position - vec3(0, 0, lens.center - lens.curvatureRadius);
    float B = dot(D, direction);
    float C = dot(D, D) - lens.curvatureRadius * lens.curvatureRadius;
    float B2_C = B * B - C;
    if (B2_C < 0) {
        return Intersection(vec3(-1), vec3(-1));
    }
    float sgn = (lens.curvatureRadius * direction.z) > 0 ? 1 : -1;
    float t = sqrt(B2_C) * sgn - B;
    vec3 intersectionPosition = direction * t + position;
    return Intersection(intersectionPosition, normalize(intersectionPosition - vec3(0, 0, lens.center - lens.curvatureRadius)));
}

vec3 refract(inout Intersection intersection, vec3 direction, float iorIn, float iorOut){
    float cosi = clamp(dot(direction, intersection.normal), -1.0f, 1.0f);
    vec3 n = intersection.normal;
    if (cosi < 0) {
        cosi = -cosi;
    } else {
        float temp = iorIn;
        iorIn = iorOut;
        iorOut = temp;
        n = -intersection.normal;
    }
    float eta = iorIn / iorOut;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? vec3(0, 0, 0) : eta * direction + (eta * cosi - sqrt(k)) * n;
}

vec3 reflect(inout Intersection intersection, vec3 direction){
    return direction - 2.0f * dot(direction, intersection.normal) * intersection.normal;
}

float trace(inout Lens lens, inout vec3 tracedPosition, vec3 tracedDirection, float ior, inout float maxRelativeDistanceToOpticalAxis){
    if (lens.ior == 0) {
        return 0;
    }
    Intersection intersection = intersectLens(lens, tracedPosition, tracedDirection);
    tracedPosition = intersection.position;

    tracedDirection = refract(intersection, tracedDirection, ior, lens.ior);

    float distanceToOpticalAxis = length(vec2(intersection.position.x, intersection.position.y));
    float relativeDistanceToOpticalAxis = distanceToOpticalAxis / lens.apertureRadius;
    maxRelativeDistanceToOpticalAxis = max(maxRelativeDistanceToOpticalAxis, relativeDistanceToOpticalAxis);

    return lens.ior;
}

void main(){
    const float startDistance = 200;

    vec3 tracedPosition = vPos * 15 + vec3(0.0, 0.0, 200.0);
    vec3 tracedDirection = vec3(0, 0, -1);
    float ior = 1;
    float maxRelativeDistanceToOpticalAxis = 0;

    int firstReflectionIndex = reflectionSequences[sequenceIndex][0];
    int secondReflectionIndex = reflectionSequences[sequenceIndex][1];

    for (int i=0;i < firstReflectionIndex; i++){
        ior = trace(lenses[i], tracedPosition, tracedDirection, ior, maxRelativeDistanceToOpticalAxis);
    }

    Intersection intersection = intersectLens(lenses[firstReflectionIndex], tracedPosition, tracedDirection);
    tracedDirection = reflect(intersection, tracedDirection);

    for (int i=firstReflectionIndex;i > secondReflectionIndex; i--){
        ior = trace(lenses[i], tracedPosition, tracedDirection, ior, maxRelativeDistanceToOpticalAxis);
    }

    intersection = intersectLens(lenses[secondReflectionIndex], tracedPosition, tracedDirection);
    tracedDirection = reflect(intersection, tracedDirection);

    for (int i=secondReflectionIndex;i < lenses.length();i++){
        ior = trace(lenses[i], tracedPosition, tracedDirection, ior, maxRelativeDistanceToOpticalAxis);
    }

    float t = (-tracedPosition.z) / tracedDirection.z;
    vec3 positionOnPlane = tracedPosition + tracedDirection * t;

    gl_Position = MVP * vec4(positionOnPlane, 1);
    float rayLeft = maxRelativeDistanceToOpticalAxis > 1 ? 1:0;
    float rayStayed = maxRelativeDistanceToOpticalAxis <= 1 ? 1:0;
    vcColor = vec3(0, rayStayed, 0);
}