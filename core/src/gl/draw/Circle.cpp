#include "gl/draw/Circle.h"

namespace chr
{
  namespace gl
  {
    namespace draw
    {
      template <>
      void Circle::fill<GL_CCW>(IndexedVertexBatch<XYZ, GLushort> &batch, Matrix &matrix, float x, float y) const
      {
        float aa = fabsf(a2 - a1);
        int n = ceilf(aa * r / segmentLength) + 1;

        batch.addVertex(matrix.transformPoint(x, y));

        for (int i = 0; i < n; i++)
        {
          float d = fmin(aa, i * segmentLength / r);
          float xx = x + sinf(a1 + d) * r;
          float yy = y + cosf(a1 + d) * r;

          batch.addVertex(matrix.transformPoint(xx, yy));

          if (i < n - 1)
          {
            batch.addIndices(0, i + 1, i + 2);
          }
        }

        batch.incrementIndices(n + 1);
      }

      template <>
      void Circle::fill<GL_CW>(IndexedVertexBatch<XYZ, GLushort> &batch, Matrix &matrix, float x, float y) const
      {
        float aa = fabsf(a2 - a1);
        int n = ceilf(aa * r / segmentLength) + 1;

        batch.addVertex(matrix.transformPoint(x, y));

        for (int i = 0; i < n; i++)
        {
          float d = fmin(aa, i * segmentLength / r);
          float xx = x + sinf(a1 + d) * r;
          float yy = y + cosf(a1 + d) * r;

          batch.addVertex(matrix.transformPoint(xx, yy));

          if (i < n - 1)
          {
            batch.addIndices(i + 1, 0, i + 2);
          }
        }

        batch.incrementIndices(n + 1);
      }

      template <>
      void Circle::fill<GL_CCW>(IndexedVertexBatch<XYZ.RGBA, GLushort> &batch, Matrix &matrix, float x, float y) const
      {
        float aa = fabsf(a2 - a1);
        int n = ceilf(aa * r / segmentLength) + 1;

        batch.addVertex(matrix.transformPoint(x, y), color);

        for (int i = 0; i < n; i++)
        {
          float d = fmin(aa, i * segmentLength / r);
          float xx = x + sinf(a1 + d) * r;
          float yy = y + cosf(a1 + d) * r;

          batch.addVertex(matrix.transformPoint(xx, yy), color);

          if (i < n - 1)
          {
            batch.addIndices(0, i + 1, i + 2);
          }
        }

        batch.incrementIndices(n + 1);
      }

      template <>
      void Circle::fill<GL_CW>(IndexedVertexBatch<XYZ.RGBA, GLushort> &batch, Matrix &matrix, float x, float y) const
      {
        float aa = fabsf(a2 - a1);
        int n = ceilf(aa * r / segmentLength) + 1;

        batch.addVertex(matrix.transformPoint(x, y), color);

        for (int i = 0; i < n; i++)
        {
          float d = fmin(aa, i * segmentLength / r);
          float xx = x + sinf(a1 + d) * r;
          float yy = y + cosf(a1 + d) * r;

          batch.addVertex(matrix.transformPoint(xx, yy), color);

          if (i < n - 1)
          {
            batch.addIndices(i + 1, 0, i + 2);
          }
        }

        batch.incrementIndices(n + 1);
      }
    }
  }
}
