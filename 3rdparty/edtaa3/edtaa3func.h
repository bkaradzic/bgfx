#ifndef __EDTAA3_H__
#define __EDTAA3_H__

extern void computegradient(double *img, int w, int h, double *gx, double *gy);
extern void edtaa3(double *img, double *gx, double *gy, int w, int h, short *distx, short *disty, double *dist);

#endif // __EDTAA3_H__
