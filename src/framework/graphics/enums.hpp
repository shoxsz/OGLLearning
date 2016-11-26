#ifndef _ENUMS_HPP_
#define _ENUMS_HPP_

enum Type{
    Array = GL_ARRAY_BUFFER,
    Index = GL_ELEMENT_ARRAY_BUFFER
}

enum AccessType{
    Static = GL_STATIC_DRAW,
    Dynamic = GL_DYNAMIC_DRAW
}

enum Wrapping{
    Repeat = GL_REPEAT,
    MirroredRepeat = GL_MIRRORED_REPEAT,
    ClampToEdge = GL_CLAMP_TO_EDGE,
    ClampToBorder = GL_CLAMP_TO_BORDER
}

enum Filtering{
    Nearest = GL_NEAREST,
    Linear = GL_LINEAR,
    NearestMipmap = GL_NEAREST_MIPMAP_NEAREST,
    LinearMipmap = GL_LINEAR_MIPMAP_LINEAR
}

enum ImageFormat{
    RGBA = GL_RGBA,
    RGB = GL_RGB
}

#endif