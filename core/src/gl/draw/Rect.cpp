#include "gl/draw/Rect.h"

using namespace chr::math;

namespace chr
{
  namespace gl
  {
    namespace draw
    {
      Rect& Rect::setBounds(const math::Rectf &bounds)
      {
        this->bounds = bounds;
        return *this;
      }

      Rect& Rect::setBounds(const glm::vec2 &upperLeft, const glm::vec2 &lowerRight)
      {
        bounds = Rectf(upperLeft, lowerRight);
        return *this;
      }

      Rect& Rect::setBounds(float left, float top, float width, float height)
      {
        bounds = Rectf(left, top, width, height);
        return *this;
      }

      Rect& Rect::setColor(const glm::vec4 &color)
      {
        this->color = color;
        return *this;
      }

      Rect& Rect::setColor(float r, float g, float b, float a)
      {
        color = { r, g, b, a };
        return *this;
      }

      template <>
      void Rect::append<GL_CCW>(IndexedVertexBatch<XYZ, GLushort> &batch, Matrix &matrix) const
      {
        matrix.addTransformedQuad<GL_TRIANGLES, GL_CCW>(Quad<XYZ>(bounds.x1, bounds.y1, bounds.x2, bounds.y2), batch);
      }

      template <>
      void Rect::append<GL_CW>(IndexedVertexBatch<XYZ, GLushort> &batch, Matrix &matrix) const
      {
        matrix.addTransformedQuad<GL_TRIANGLES, GL_CW>(Quad<XYZ>(bounds.x1, bounds.y1, bounds.x2, bounds.y2), batch);
      }

      template <>
      void Rect::append<GL_CCW>(IndexedVertexBatch<XYZ.RGBA, GLushort> &batch, Matrix &matrix) const
      {
        matrix.addTransformedQuad<GL_TRIANGLES, GL_CCW>(Quad<XYZ.RGBA>(bounds.x1, bounds.y1, bounds.x2, bounds.y2, color), batch);
      }

      template <>
      void Rect::append<GL_CW>(IndexedVertexBatch<XYZ.RGBA, GLushort> &batch, Matrix &matrix) const
      {
        matrix.addTransformedQuad<GL_TRIANGLES, GL_CW>(Quad<XYZ.RGBA>(bounds.x1, bounds.y1, bounds.x2, bounds.y2, color), batch);
      }

      template <>
      void Rect::append<GL_CCW>(IndexedVertexBatch<XYZ.N.RGBA, GLushort> &batch, Matrix &matrix) const
      {
        matrix.addTransformedQuad<GL_TRIANGLES, GL_CCW>(Quad<XYZ.N.RGBA>(bounds.x1, bounds.y1, bounds.x2, bounds.y2, glm::vec3(0, 0, +1), color), batch);
      }

      template <>
      void Rect::append<GL_CW>(IndexedVertexBatch<XYZ.N.RGBA, GLushort> &batch, Matrix &matrix) const
      {
        matrix.addTransformedQuad<GL_TRIANGLES, GL_CW>(Quad<XYZ.N.RGBA>(bounds.x1, bounds.y1, bounds.x2, bounds.y2, glm::vec3(0, 0, -1), color), batch);
      }

      // ---

      template <>
      void Rect::append<GL_CCW>(IndexedVertexBatch<XYZ, GLushort> &batch) const
      {
        batch
          .addVertex(bounds.x1, bounds.y1)
          .addVertex(bounds.x1, bounds.y2)
          .addVertex(bounds.x2, bounds.y2)
          .addVertex(bounds.x2, bounds.y1);

        batch
          .addIndices(0, 1, 2, 2, 3, 0)
          .incrementIndices(4);
      }

      template <>
      void Rect::append<GL_CW>(IndexedVertexBatch<XYZ, GLushort> &batch) const
      {
        batch
          .addVertex(bounds.x1, bounds.y1)
          .addVertex(bounds.x1, bounds.y2)
          .addVertex(bounds.x2, bounds.y2)
          .addVertex(bounds.x2, bounds.y1);

        batch
          .addIndices(0, 3, 2, 2, 1, 0)
          .incrementIndices(4);
      }

      template <>
      void Rect::append<GL_CCW>(IndexedVertexBatch<XYZ.RGBA, GLushort> &batch) const
      {
        batch
          .addVertex(bounds.x1, bounds.y1, 0, color)
          .addVertex(bounds.x1, bounds.y2, 0, color)
          .addVertex(bounds.x2, bounds.y2, 0, color)
          .addVertex(bounds.x2, bounds.y1, 0, color);

        batch
          .addIndices(0, 1, 2, 2, 3, 0)
          .incrementIndices(4);
      }

      template <>
      void Rect::append<GL_CW>(IndexedVertexBatch<XYZ.RGBA, GLushort> &batch) const
      {
        batch
          .addVertex(bounds.x1, bounds.y1, 0, color)
          .addVertex(bounds.x1, bounds.y2, 0, color)
          .addVertex(bounds.x2, bounds.y2, 0, color)
          .addVertex(bounds.x2, bounds.y1, 0, color);

        batch
          .addIndices(0, 3, 2, 2, 1, 0)
          .incrementIndices(4);
      }
    }
  }
}
