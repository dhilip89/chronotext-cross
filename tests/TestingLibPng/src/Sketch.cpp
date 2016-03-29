#include "Sketch.h"

#include "gl/TextureShader.h"
#include "gl/TextureAlphaShader.h"

using namespace std;
using namespace chr;
using namespace gl;

void Sketch::setup()
{
  initTextures();

  // ---

  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Sketch::shutdown()
{
  glDeleteTextures(1, &textures[0].id);
  glDeleteTextures(1, &textures[1].id);
  glDeleteTextures(1, &textures[2].id);

  textureBuffer.shutdown();
}

void Sketch::draw()
{
  glClearColor(0, 0, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  // ---

  glm::mat4 projectionMatrix = glm::perspective(60 * D2R, windowInfo.size.x / windowInfo.size.y, 0.1f, 1000.0f);

  glm::mat4 modelViewMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1, -1, 1)); // SCALE
  modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(0, 0, -300)); // DISTANCE
  modelViewMatrix = glm::rotate(modelViewMatrix, 15 * D2R, glm::vec3(1, 0, 0)); // ELEVATION
  modelViewMatrix = glm::rotate(modelViewMatrix, (float) getElapsedSeconds(), glm::vec3(0, 1, 0)); // AZIMUTH

  // ---

  textureBuffer.setShader(textureShader);
  textureShader.applyMVPMatrix(projectionMatrix * modelViewMatrix);
  textureShader.applyColor(1, 1, 1, 1);
  textureBuffer.drawFromCenter(textures[0], 0, 0, 0.333f);

  modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(0, 0, 5));

  textureBuffer.setShader(textureAlphaShader);
  textureAlphaShader.applyMVPMatrix(projectionMatrix * modelViewMatrix);
  textureAlphaShader.applyColor(1, 0.5f, 0, 1);
  textureBuffer.drawInRect(textures[1], math::Rectf(-200, -150, 400, 300));

  modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(0, 0, 5));

  textureBuffer.setShader(textureShader);
  textureShader.applyMVPMatrix(projectionMatrix * modelViewMatrix);
  textureShader.applyColor(1, 1, 1, 1);
  textureBuffer.drawFromCenter(textures[2], 100, 100);
}

void Sketch::initTextures()
{
  textures[0] = loadTexture("6980491_UN1_800_MASK.png", chr::image::FLAGS_POT);
  textures[1] = loadTexture("lys_32.png", image::FLAGS_TRANSLUCENT_INVERSE, true, GL_REPEAT, GL_REPEAT);
  textures[2] = loadTexture("expo67.png");

  // ---

  #if defined(CHR_PLATFORM_EMSCRIPTEN)
    emscripten_webgl_enable_extension(emscripten_webgl_get_current_context(), "EXT_texture_filter_anisotropic");
    emscripten_webgl_enable_extension(emscripten_webgl_get_current_context(), "WEBKIT_EXT_texture_filter_anisotropic");
  #endif

  GLfloat maxAnisotropy;
  glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
}
