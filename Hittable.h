#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

class HitRecord
{
public:
    void SetFaceNormal(const Ray& r, const Vec3& outwardNormal)
    {
        bFrontFace = Dot(r.Direction(), outwardNormal) < 0;     // 들어오는지, 나가는지 판별
        Normal = bFrontFace ? outwardNormal : -outwardNormal;
    }

    Point3 P;           // 어디에 충돌했는가
    Vec3 Normal;        // 그 표면은 어느 방향인가
    double T;           // Ray를 따라 얼마나 이동했는가
    bool bFrontFace;    // 앞면 OR 뒷면
};

class Hittable
{
public:
    virtual ~Hittable() = default;
    virtual bool Hit(const Ray& r, double rayTMin, double rayTMax, HitRecord& rec) const = 0;
};

#endif