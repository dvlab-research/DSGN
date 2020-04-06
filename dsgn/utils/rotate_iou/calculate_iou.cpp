// Reference: https://github.com/acmeism/RosettaCodeData/blob/master/Task/Sutherland-Hodgman-polygon-clipping/C/sutherland-hodgman-polygon-clipping.c
// Change some tiny places for using in Python


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef struct { double x, y; } vec_t, *vec;

inline double dot(vec a, vec b)
{
	return a->x * b->x + a->y * b->y;
}

inline double cross(vec a, vec b)
{
	return a->x * b->y - a->y * b->x;
}

inline vec vsub(vec a, vec b, vec res)
{
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	return res;
}

/* tells if vec c lies on the left side of directed edge a->b
 * 1 if left, -1 if right, 0 if colinear
 */
int left_of(vec a, vec b, vec c)
{
	vec_t tmp1, tmp2;
	double x;
	vsub(b, a, &tmp1);
	vsub(c, b, &tmp2);
	x = cross(&tmp1, &tmp2);
	return x < 0 ? -1 : x > 0;
}

int line_sect(vec x0, vec x1, vec y0, vec y1, vec res)
{
	vec_t dx, dy, d;
	vsub(x1, x0, &dx);
	vsub(y1, y0, &dy);
	vsub(x0, y0, &d);
	/* x0 + a dx = y0 + b dy ->
	   x0 X dx = y0 X dx + b dy X dx ->
	   b = (x0 - y0) X dx / (dy X dx) */
	double dyx = cross(&dy, &dx);
	if (!dyx) return 0;
	dyx = cross(&d, &dx) / dyx;
	if (dyx <= 0 || dyx >= 1) return 0;

	res->x = y0->x + dyx * dy.x;
	res->y = y0->y + dyx * dy.y;
	return 1;
}

/* === polygon stuff === */
typedef struct { int len, alloc; vec v; } poly_t, *poly;

poly poly_new()
{
	return (poly)calloc(1, sizeof(poly_t));
}

void poly_free(poly p)
{
	free(p->v);
	free(p);
}

void poly_append(poly p, vec v)
{
	if (p->len >= p->alloc) {
		p->alloc *= 2;
		if (!p->alloc) p->alloc = 4;
		p->v = (vec)realloc(p->v, sizeof(vec_t) * p->alloc);
	}
	p->v[p->len++] = *v;
}

/* this works only if all of the following are true:
 *   1. poly has no colinear edges;
 *   2. poly has no duplicate vertices;
 *   3. poly has at least three vertices;
 *   4. poly is convex (implying 3).
*/
int poly_winding(poly p)
{
	return left_of(p->v, p->v + 1, p->v + 2);
}

void poly_edge_clip(poly sub, vec x0, vec x1, int left, poly res)
{
	int i, side0, side1;
	vec_t tmp;
	vec v0 = sub->v + sub->len - 1, v1;
	res->len = 0;

	side0 = left_of(x0, x1, v0);
	if (side0 != -left) poly_append(res, v0);

	for (i = 0; i < sub->len; i++) {
		v1 = sub->v + i;
		side1 = left_of(x0, x1, v1);
		if (side0 + side1 == 0 && side0)
			/* last point and current straddle the edge */
			if (line_sect(x0, x1, v0, v1, &tmp))
				poly_append(res, &tmp);
		if (i == sub->len - 1) break;
		if (side1 != -left) poly_append(res, v1);
		v0 = v1;
		side0 = side1;
	}
}

poly poly_clip(poly sub, poly clip)
{
	int i;
	poly p1 = poly_new(), p2 = poly_new(), tmp;

	int dir = poly_winding(clip);
	poly_edge_clip(sub, clip->v + clip->len - 1, clip->v, dir, p2);
	for (i = 0; i < clip->len - 1; i++) {
		tmp = p2; p2 = p1; p1 = tmp;
		if(p1->len == 0) {
			p2->len = 0;
			break;
		}
		poly_edge_clip(p1, clip->v + i, clip->v + i + 1, dir, p2);
	}

	poly_free(p1);
	return p2;
}


// sum_area = area1 + area2
// The IoU = Intersection / (sum_area - Intersection) 
double area_sum(double input_arr_1[4][2], double input_arr_2[4][2])
{
	double sum_area = 0;
	double area_1 = 0;
	double area_2 = 0;
	double x = input_arr_1[0][0];
	double y = input_arr_1[0][1];
	double xtemp = 0;
	double ytemp = 0;
	for (int i=1; i<4; i++)
	{
		xtemp = input_arr_1[i][0];
		ytemp = input_arr_1[i][1];
		area_1 += (x*ytemp - y*xtemp);
		x = xtemp;
		y = ytemp;
	}
	area_1 += (x*input_arr_1[0][1] - y*input_arr_1[0][0]);
	area_1 = fabs(area_1/2);

	x = input_arr_2[0][0];
	y = input_arr_2[0][1];
	for (int i=1; i<4; i++)
	{
		xtemp = input_arr_2[i][0];
		ytemp = input_arr_2[i][1];
		area_2 += (x*ytemp - y*xtemp);
		x = xtemp;
		y = ytemp;
	}
	area_2 += (x*input_arr_2[0][1] - y*input_arr_2[0][0]);
	area_2 = fabs(area_2/2);

	sum_area = area_1 + area_2;
	// sum_area = fabs((area_1 + area_2)/2);
	// printf("%g \n", sum_area);
	return sum_area;
}

double calculate_area(double input_arr[][2], int length)
{
	if (length == 0 || length == 1 || length == 2)
		return 0;

	double sum_area = 0;
	double x, y, xtemp, ytemp;
	x = input_arr[0][0];
	y = input_arr[0][1];
	for (int i=0; i < length; i++)
	{
		xtemp = input_arr[i][0];
		ytemp = input_arr[i][1];
		sum_area += (x * ytemp - y * xtemp);
		x = xtemp;
		y = ytemp;
	}
	sum_area += (x * input_arr[0][1] - y * input_arr[0][0]);
	sum_area = fabs(sum_area / 2);
	return sum_area;

}

extern "C" double calculate_iou(double a00, double a01, double a10, double a11, double a20, double a21, double a30, double a31,
	double b00, double b01, double b10, double b11, double b20, double b21, double b30, double b31)
{
	double input_arr_1[4][2];
	double input_arr_2[4][2];

	input_arr_1[0][0] = a00;
	input_arr_1[0][1] = a01;
	input_arr_1[1][0] = a10;
	input_arr_1[1][1] = a11;
	input_arr_1[2][0] = a20;
	input_arr_1[2][1] = a21;
	input_arr_1[3][0] = a30;
	input_arr_1[3][1] = a31;

	input_arr_2[0][0] = b00;
	input_arr_2[0][1] = b01;
	input_arr_2[1][0] = b10;
	input_arr_2[1][1] = b11;
	input_arr_2[2][0] = b20;
	input_arr_2[2][1] = b21;
	input_arr_2[3][0] = b30;
	input_arr_2[3][1] = b31;

	struct timespec start, end;
	int i;
	vec_t c[] = {{input_arr_1[0][0], input_arr_1[0][1]}, {input_arr_1[1][0], input_arr_1[1][1]}, {input_arr_1[2][0], input_arr_1[2][1]}, {input_arr_1[3][0], input_arr_1[3][1]}};
	vec_t s[] = {{input_arr_2[0][0], input_arr_2[0][1]}, {input_arr_2[1][0], input_arr_2[1][1]}, {input_arr_2[2][0], input_arr_2[2][1]}, {input_arr_2[3][0], input_arr_2[3][1]}};
	#define clen (sizeof(c)/sizeof(vec_t))
	#define slen (sizeof(s)/sizeof(vec_t))
	poly_t clipper = {clen, 0, c};
	poly_t subject = {slen, 0, s};
	poly res = poly_clip(&subject, &clipper);
	double res_array[res->len][2];
	if (res->len==0 || res->len == 1 || res->len == 2)
	 	return 0;

	for (int i=0; i<res->len; i++)
	{
		res_array[i][0] = res->v[i].x; res_array[i][1] = res->v[i].y;
	}

	double area_1 = calculate_area(input_arr_1, 4);
	double area_2 = calculate_area(input_arr_2, 4);
	double inter_area = calculate_area(res_array, res->len);

	if (inter_area == 0)
		return 0;	
	poly_free(res);
	return double(inter_area/(area_1 + area_2 - inter_area));
}