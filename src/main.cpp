#include "primitive.h"
#include "object.h"
#include"camera.h"
#include"integrator.h"
#include <iostream>
#include "math.h"
using namespace dragon;
int main() {
	Scene s;
	PerspectiveCamera c(Point3f(0, 0, -40), Point3f(0, 0, 0), 39, 1e-2f, 1000.f, 1200, 1200);
	PMaterial glass(new GlassMat(Vec3f(0.5, 0.5, 0.5), Vec3f(0.7, 0.7, 0.7), 1.6, 1.35));
	PMaterial red(new MatteMat(Vec3f(1.f, 0.f, 0.f), Vec3f(1.f, 1.f, 1.f), 10));
	PMaterial green(new MatteMat(Vec3f(0.f, 1.f, 0.f), Vec3f(1.f, 1.f, 1.f), 10));
	PMaterial check(new CheckMat(Vec3f(0.f, 1.f, 0.f), Vec3f(1.f, 1.f, 1.f), Vec2f(0.2,0.2),10));
	PMaterial blue(new MatteMat(Vec3f(0.f, 0.f, 1.f), Vec3f(1.f, 1.f, 1.f), 10));
	PLight L1(new DirectionLight(Vec3f(0, 0, 1), RGB(0.7, 0.7, 0.7)));
	PLight L2(new DirectionLight(Vec3f(0, 0, -1), RGB(0.5, 0.5, 0.5)));
	PObject s1(new Sphere(Point3f(0.f, 0.f, 0.f), 5, glass));
	PObject s2(new Sphere(Point3f(10.f, 0.f, -8.f), 5, red));
	PObject s3(new Sphere(Point3f(0.f, 10.f, -3.f), 5, green));
	PObject s4(new Sphere(Point3f(-6.f, 0.f, 5.f), 5, blue));
	PObject f(new Floor(Point3f(0, 0, 15), 40, 40, Vec3f(0, 0, 0), check));
	PObject f1(new Floor(Point3f(0, 0, 5), 20, 20, Vec3f(90, 0, 0), green));
	s.objs.push_back(f);
	//s.objs.push_back(f1);
	s.lights.push_back(L1);
	s.lights.push_back(L2);
	s.objs.push_back(s1);
	s.objs.push_back(s2);
	s.objs.push_back(s3);
	s.objs.push_back(s4);
	PathIntegrator it(4);
//	PhongIntegrator it;
	//Point3f pos(40, 0, 0);
	//for (int i = 0; i < 180;i++) {
	//	c.position = RotateY(-i)(pos);
	//	c.ReBuild();
	//	it.Render(s, c);
	//	c.film->Write(i);
	//}
	it.Render(s, c);
	c.film->Write(556);
	return 0;
}