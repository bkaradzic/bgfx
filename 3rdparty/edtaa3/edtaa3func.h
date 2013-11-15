#ifndef EDTAA3_H_HEADER_GUARD
#define EDTAA3_H_HEADER_GUARD

extern void computegradient(double *img, int w, int h, double *gx, double *gy);
extern void edtaa3(double *img, double *gx, double *gy, int w, int h, short *distx, short *disty, double *dist);

#endif // EDTAA3_H_HEADER_GUARD
