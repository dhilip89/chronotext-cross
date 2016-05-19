#include "Sketch.h"

#include "gl/draw/Cube.h"
#include "gl/Triangulator.h"
#include "shape/Circle.h"

#include "PolyhedronBuilder.h"

using namespace std;
using namespace chr;
using namespace gl;

static bool showTube = false;
static bool showCube = true;

Sketch::Sketch()
{
  std::vector<double> vertices1 = { 0, 0, 0,
                                    2, 0, 0,
                                    0, 2, 0,
                                    2, 2, 0,
                                    0, 0, 2,
                                    2, 0, 2,
                                    0, 2, 2,
                                    2, 2, 2 };

  std::vector<double> vertices2 = { 1, 1, 1,
                                    3, 1, 1,
                                    1, 3, 1,
                                    3, 3, 1,
                                    1, 1, 3,
                                    3, 1, 3,
                                    1, 3, 3,
                                    3, 3, 3 };

  std::vector<int> triangles = { 0, 1, 2,
                                 1, 3, 2,
                                 0, 2, 4,
                                 4, 2, 5,
                                 4, 5, 7,
                                 5, 6, 7,
                                 3, 1, 7,
                                 7, 6, 3,
                                 2, 3, 6,
                                 6, 5, 2,
                                 1, 0, 7,
                                 0, 4, 7 };

  Polyhedron P1;
  PolyhedronBuilder<HalfedgeDS> builder1(vertices1, triangles);
  P1.delegate(builder1);

  Polyhedron P2;
  PolyhedronBuilder<HalfedgeDS> builder2(vertices2, triangles);
  P2.delegate(builder2);

  LOGI << "isClosed: " << P1.is_closed() << " | isValid: " << P1.is_valid() << " | isPureTriangle: " << P1.is_pure_triangle() << endl;
  LOGI << "isClosed: " << P2.is_closed() << " | isValid: " << P2.is_valid() << " | isPureTriangle: " << P2.is_pure_triangle() << endl;

  Nef_polyhedron nef1(P1);
  Nef_polyhedron nef2(P2);

  Nef_polyhedron nef3 = nef1 + nef2;
  Polyhedron result;
  nef3.convert_to_Polyhedron(result);
}

void Sketch::setup()
{
  state.setShader(lambertShader);

  // ---

  Matrix matrix;

  draw::Cube()
    .setSize(100)
    .setFrontFace(GL_CW)
    .append(batch1, matrix);

  matrix
    .setTranslate(37.5f, 37.5f, 37.5f)
    .rotateY(15 * D2R);

  if (showCube)
  {
    draw::Cube()
      .setSize(75)
      .setFrontFace(GL_CW)
      .append(batch2, matrix);
  }
  else if (showTube)
  {
    vector<vector<glm::vec2>> polygons;
    polygons.emplace_back(
      shape::Circle()
        .setSegmentLength(6)
        .setRadius(50)
        .append());
    polygons.emplace_back(
      shape::Circle()
        .setSegmentLength(6)
        .setRadius(40)
        .append());

    Triangulator triangulator;
    triangulator
      .setFrontFace(GL_CW)
      .setTextureScale(100 / 256.0f)
      .add(polygons)
      .extrude(batch2, matrix, -120);
  }
  else
  {
    assert(false);
  }

  // ---

  glDepthMask(GL_TRUE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Sketch::draw()
{
  glClearColor(0.5f, 0.5f, 0.5f, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // ---

  glm::mat4 projectionMatrix = glm::perspective(60 * D2R, windowInfo.width / windowInfo.height, 0.1f, 1000.0f);

  Matrix mvMatrix;
  mvMatrix
    .scale(1, 1, 1)
    .translate(0, 0, -300)
    .rotateY(clock()->getTime())
    .rotateZ(clock()->getTime() * 0.25f);

  auto mvpMatrix = mvMatrix * projectionMatrix;

  // ---

  state
    .setShaderMatrix<MVP>(mvpMatrix)
    .setShaderMatrix<NORMAL>(mvMatrix.getNormalMatrix())
    .apply();

  batch1
    .setShaderColor(0.25f, 0.25f, 0.25f, 1)
    .flush();

  batch2
    .setShaderColor(0.5f, 0, 0, 1)
    .flush();
}