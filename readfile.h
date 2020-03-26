#ifndef READFILE_H
#define READFIEL_H

#include "lib.h"
#include "parameters.h"

static void readfile()
{
	if ((fopen_s(&f,r,"r"))!=0) printf_s("%s\n",r);
    printf_s("file %s opened\n",r);
	fscanf_s(f, "%d", &tot_things);
	for (int i = 0; i < tot_things; i++) {
		fscanf_s(f, "%d%lf%lf%lf%lf", &tot_unit[i],&ori_x[i],&ori_y[i],&ori_z[i],&ori_dir[i]);
		for (int j = 0; j < tot_unit[i]; j++) {
			fscanf_s(f, "%d", &u[i][j].type);
			switch (u[i][j].type) {
			case 0: {
				fscanf_s(f, "%lf%lf%lf%lf%d", &u[i][j].x, &u[i][j].y, &u[i][j].z, &u[i][j].size, &u[i][j].texture_num);
				break;
			}
			case 1: {
				fscanf_s(f, "%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%d", &u[i][j].p1x, &u[i][j].p1y, &u[i][j].p1z, 
					                                                  &u[i][j].p2x, &u[i][j].p2y, &u[i][j].p2z, 
					                                                  &u[i][j].p3x, &u[i][j].p3y, &u[i][j].p3z, 
					                                                  &u[i][j].p4x, &u[i][j].p4y, &u[i][j].p4z, 
					                                                                     &u[i][j].texture_num);
				break;
			}
			default:
				printf("no such type!!\n");
				return;
			}
		}
	}
	fclose(f);
}

#endif
