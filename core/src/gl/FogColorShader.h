#pragma once

#include "gl/ShaderProgram.h"

namespace chr
{
  namespace gl
  {
    class FogColorShader : public ShaderProgram
    {
    public:
      static const char *vertexShaderSource;
      static const char *fragmentShaderSource;

      GLint fogDensityLocation;
      GLint fogColorLocation;

      bool load();
      bool use();
    };

    extern FogColorShader fogColorShader;
  }
}
