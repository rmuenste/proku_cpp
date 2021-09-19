#ifndef PROKU_RENDER_CAMERA_HPP
#define PROKU_RENDER_CAMERA_HPP

#include <cmath>
#include "triangle.hpp"


class Vector4
{
public:
  union
  {
    float v[4];
    struct
    {
      float x,y,z,w;
    };
  };

  Vector4()
  {
  }

  explicit Vector4(float _x, float _y, float _z, float _w = float(1))
    : x(_x), y(_y), z(_z), w(_w)
  {
  }

  Vector4 normal3() const
  {
    float l = std::sqrt(x*x+y*y+z*z);
    return Vector4(x/l, y/l, z/l);
  }

  Vector4& operator+=(const Vector4& _other)
  {
    for(int i(0); i < 4; ++i)
      v[i] += _other.v[i];
    return *this;
  }

  Vector4& operator-=(const Vector4& _other)
  {
    for(int i(0); i < 4; ++i)
      v[i] -= _other.v[i];
    return *this;
  }

  Vector4& operator*=(const float& _alpha)
  {
    for(int i(0); i < 4; ++i)
      v[i] *= _alpha;
    return *this;
  }

  Vector4& operator/=(const float& _alpha)
  {
    // This works only for floating point numbers
    return this->operator*=(1.0f /_alpha);
  }
};

/// vector scalar multiplication operator (left)
inline Vector4 operator*(const float& _alpha, const Vector4& _vec)
{
  return (Vector4(_vec)) *= _alpha;
}

/// vector scalar multiplication operator (right)
inline Vector4 operator*(const Vector4& _vec, const float& _alpha)
{
  return (Vector4(_vec)) *= _alpha;
}

/// vector scalar division operator
inline Vector4 operator/(const Vector4& _vec, const float& _alpha)
{
  return (Vector4(_vec)) /= _alpha;
}

/// vector addition operator
inline Vector4 operator+(const Vector4& _left, const Vector4& _right)
{
  return (Vector4(_left)) += _right;
}

/// vector subtraction operator
inline Vector4 operator-(const Vector4& _left, const Vector4& _right)
{
  return (Vector4(_left)) -= _right;
}

/// vector-base dot-product
inline float dot3(const Vector4& _a, const Vector4& _b)
{
  return _a.x*_b.x + _a.y*_b.y + _a.z*_b.z;
}

/// vector-base dot-product
inline float dot(const Vector4& _a, const Vector4& _b)
{
  return dot3(_a,_b) + _a.w * _b.w;
}

/// 3D cross product
inline Vector4 cross3(const Vector4& _a, const Vector4& _b)
{
  return Vector4(
    _a.v[1]*_b.v[2] - _a.v[2]*_b.v[1],
    _a.v[2]*_b.v[0] - _a.v[0]*_b.v[2],
    _a.v[0]*_b.v[1] - _a.v[1]*_b.v[0]);
}


class Quaternion
{
public:
  union
  {
    float v[4];
    struct
    {
      /// imaginary components
      float x,y,z;
      /// real component
      float w;
    };
  };

  /// default constuctor
  Quaternion()
  {
  }

  /// yaw-pitch-roll constructor
  explicit Quaternion(float _yaw, float _pitch, float _roll)
  {
    float cy = std::cos(_yaw / float(2));
    float sy = std::sin(_yaw / float(2));
    float cp = std::cos(_pitch / float(2));
    float sp = std::sin(_pitch / float(2));
    float cr = std::cos(_roll / float(2));
    float sr = std::sin(_roll / float(2));

    // yxz-order
    x = cy*sp*cr + sy*cp*sr;
    y = sy*cp*cr - cy*sp*sr;
    z = cy*cp*sr - sy*sp*cr;
    w = cy*cp*cr + sy*sp*sr;
  }

  /// Rotates a vector
  Vector4 rotate_vector(const Vector4& _vec) const
  {
    float a =  w*_vec.x + y*_vec.z - z*_vec.y;
    float b =  w*_vec.y - x*_vec.z + z*_vec.x;
    float c =  w*_vec.z + x*_vec.y - y*_vec.x;
    float d = -x*_vec.x - y*_vec.y - z*_vec.z;

    return Vector4(
       a*w - b*z + c*y - d*x,
       a*z + b*w - c*x - d*y,
      -a*y + b*x + c*w - d*z);
  }
}; // class Quaternion


class Matrix4
{
public:
  float m[4][4];
  
  Matrix4()
  {
  }

  explicit Matrix4(const Quaternion& _quat)
  {
    m[0][0] = _quat.w*_quat.w + _quat.x*_quat.x - _quat.y*_quat.y - _quat.z*_quat.z;
    m[0][1] = float(2)*(_quat.x*_quat.y - _quat.w*_quat.z);
    m[0][2] = float(2)*(_quat.w*_quat.y + _quat.x*_quat.z);
    m[1][0] = float(2)*(_quat.w*_quat.z + _quat.x*_quat.y);
    m[1][1] = _quat.w*_quat.w - _quat.x*_quat.x + _quat.y*_quat.y - _quat.z*_quat.z;
    m[1][2] = float(2)*(_quat.y*_quat.z - _quat.w*_quat.x);
    m[2][0] = float(2)*(_quat.x*_quat.z - _quat.w*_quat.y);
    m[2][1] = float(2)*(_quat.w*_quat.x + _quat.y*_quat.z);
    m[2][2] = _quat.w*_quat.w - _quat.x*_quat.x - _quat.y*_quat.y + _quat.z*_quat.z;
    m[0][3] = m[1][3] = m[2][3] = float(0);
    m[3][0] = m[3][1] = m[3][2] = float(0);
    m[3][3] = float(1);
  }

  void set_identity()
  {
    for(int i(0); i < 4; ++i)
      for(int j(0); j < 4; ++j)
        m[i][j] = (i == j ? float(1) : float(0));
  }

  void set_null()
  {
    for(int i(0); i < 4; ++i)
      for(int j(0); j < 4; ++j)
        m[i][j] = float(0);
  }
  void set_look_at(const Vector4& _eye, const Vector4& _dir, const Vector4& _up)
  {
    Vector4 c = float(-1) * _dir.normal3();
    Vector4 a = cross3(_up, c).normal3();
    Vector4 b = cross3(c, a).normal3();
    m[0][0] = a.x;
    m[0][1] = a.y;
    m[0][2] = a.z;
    m[0][3] = -dot3(a, _eye);
    m[1][0] = b.x;
    m[1][1] = b.y;
    m[1][2] = b.z;
    m[1][3] = -dot3(b, _eye);
    m[2][0] = c.x;
    m[2][1] = c.y;
    m[2][2] = c.z;
    m[2][3] = -dot3(c, _eye);
    m[3][0] = float(0);
    m[3][1] = float(0);
    m[3][2] = float(0);
    m[3][3] = float(1);
  }

  void set_target_cam(const Vector4& _target, const float _dist, const Quaternion& _quat)
  {
    Vector4 dir = _quat.rotate_vector(Vector4(float(0), float(0), float(-1)));
    Vector4 up  = _quat.rotate_vector(Vector4(float(0), float(1), float(0)));
    Vector4 eye = _target - _dist * dir;
    set_look_at(eye, dir, up);
  }

  void set_target_cam(const Vector4& _target, const float _dist, const float _yaw = float(0.0),
    const float _pitch = float(0.0), const float _roll = float(0.0))
  {
    set_target_cam(_target, _dist, Quaternion(_yaw, _pitch, _roll));
  }

  void set_perspective(const float _fovy, const float _aspect, const float _znear, const float _zfar)
  {
    float cot = float(1) / std::cos(float(0.5) * _fovy);
    float den = -float(1) / (_znear - _zfar);
    set_null();
    m[0][0] = cot / _aspect;
    m[1][1] = cot;
    m[2][2] = _znear * den;
    m[2][3] = _znear * _zfar * den;
    m[3][2] = -float(1);
  }

  void set_viewport(const float _width, const float _height)
  {
    set_identity();
    m[0][0] = m[0][3] = _width * 0.5f;
    m[1][1] = -_height * 0.5f;
    m[1][3] =  _height * 0.5f;
  }
};

/// vector scalar multiplication operator (left)
inline Vector4 operator*(const Matrix4& _mat, const Vector4& _vec)
{
  Vector4 vo;
  for(int i(0); i < 4; ++i)
  {
    vo.v[i] = 0.0f;
    for(int j(0); j< 4; ++j)
      vo.v[i] += _mat.m[i][j] * _vec.v[j];
  }
  return vo;
}

class Camera
{
private:
  Matrix4 mat_view, mat_proj, mat_port;

  Vector4 p2v(const Point& p) const
  {
    return Vector4(p.x, p.y, p.z, 1.0f);
  }

  void v2p(Point& p, const Vector4& v) const
  {
    p.x = v.x;
    p.y = v.y;
    p.z = v.z;
  }

public:
  Camera()
  {
    mat_view.set_identity();
    mat_proj.set_identity();
    mat_port.set_identity();
  }

  void set_selfie_cam(float x, float y, float z, float dist, float yaw, float pitch, float roll)
  {
    assert(dist > 0.01f);
    mat_view.set_target_cam(Vector4(x, y, z, 0.0f), dist, yaw, pitch, roll);
  }

  void set_projection(int width, int height, float fovy = 1.3f, float znear = 1.0f, float zfar = 50.0f)
  {
    assert(width  > 4);
    assert(height > 4);
    assert(fovy   > 0.1f);
    assert(znear > 0.001f);
    assert(zfar > znear + 0.1f);

    mat_proj.set_perspective(fovy, float(width) / float(height), znear, zfar);
    mat_port.set_viewport(float(width), float(height));
  }

  Triangle transform(const Triangle& tria) const
  {
    Triangle t;
    for(int i(0); i < 3; ++i)
    {
      v2p(t.vertex[i], mat_view * p2v(tria.vertex[i]));
    }
    return t;
  }

  Triangle project(const Triangle& tria) const
  {
    Triangle t;
    for(int i(0); i < 3; ++i)
    {
      Vector4 v = mat_proj * p2v(tria.vertex[i]);
      v /= v.w;
      v2p(t.vertex[i], mat_port * v);
    }
    return t;
  }
};

#endif // PROKU_RENDER_CAMERA_HPP