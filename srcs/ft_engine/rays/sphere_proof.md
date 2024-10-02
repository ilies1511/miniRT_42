/*
//Wikipedia line sphere intersection step by step:
point px: intersection point
double t: scalar for ray->direct to reach the intersection point and
	the var we want

// ray formular with px beeing a point on the ray
1:	ray->origin + t * ray.direct = px
// sphere formular with px beeing on the surface of the sphere
2:	|| px - sph.origin || = sph.rad
// substitude px in 2 by 1 since px should meet both formulars
-> || (ray->origin + t * ray.direct) - sph.origin || = sph.rad
// start solving for t:
-> || ray->origin - sph.origin + t * ray.direct  || = sph.rad
// vec ori_diff = ray->origin - sph.origin
-> || ori_diff + t * ray->direct  || = sph.rad
-> sqr(dot(ori_diff + t * ray->direct, ori_diff + t * ray.direct)) = sph.rad
// square both sides to get rid of sqrt
->dot(ori_diff + t * ray->direct, ori_diff + t * ray.direct) = sph.rad^2
//distributive law
->dot(ori_diff, ori_diff + t * ray->direct) + dot(t * ray.direct, ori_diff + t * ray.direct) = sph.rad^2
//distributive law
->dot(ori_diff, ori_diff) + dot(ori_diff, t * ray->direct) + dot(t * ray.direct, ori_diff) + dot(t * ray.direct, t * ray.direct) = sph.rad^2
->dot(ori_diff, ori_diff) + 2 * dot(ori_diff, t * ray->direct) + dot(t * ray.direct, t * ray.direct) = sph.rad^2
->dot(ori_diff, ori_diff) + 2 * t * dot(ori_diff, ray->direct) + t^2 * dot(ray.direct, ray.direct) = sph.rad^2
// form quadratic formular
//at^2 + tb + c = 0
//-sph.rad^2
->dot(ori_diff, ori_diff) + t * 2 * dot(ori_diff, ray->direct) + t^2 * dot(ray.direct, ray.direct) - sph.rad^2 = 0
->t^2 * dot(ray->direct, ray.direct) + 2 * t * dot(ori_diff, ray.direct) + dot(ori_diff, ori_diff) - sph.rad^2 = 0
// double	dot_direct = dot(ray->dircet, ray.direct)
// double	dot_diff_direct = dot(ori_diff, ray->direct);
// double	dot_diff = dot(ori_diff, ori_diff);
// a = dot_direct
// b =  2 *dot_diff_direct
// c = dot_diff - sph.rad^2
// t = (-b +- sqrt(b^2 - 4 * a * c)) / 2a
// double sqr_dot_diff_direct = dot_direct * dot_direct
-> t = -2*dot_diff_direct +- sqrt(sqr_dot_diff_direct - 4 * dot_direct * (dot_diff - sph.rad^2)) / (2 * dot_direct)
*/
