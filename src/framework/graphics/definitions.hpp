#ifndef _DEFINITIONS_HPP_
#define _DEFINITIONS_HPP_

#include "utils/matrix.hpp"

#include <memory>

typedef Matrix<float, 3, 3> Matrix3;
typedef Matrix<float, 4, 4> Matrix4;

class Shader;
class ShaderProgram;
class SpriteBatch;
class Texture2D;

typedef std::shared_ptr<Shader> ShaderPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
typedef std::shared_ptr<SpriteBatch> SpriteBatchPtr;
typedef std::shared_ptr<Texture2D> Texture2DPtr;

#endif