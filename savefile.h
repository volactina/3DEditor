#ifndef SAVEFILE_H
#define SAVEFILE_H

#include "lib.h"
#include "parameters.h"

static void savefile() {
	ori_x[tot_things] = save_x;
	ori_y[tot_things] = save_y;
	ori_z[tot_things] = save_z;
	ori_dir[tot_things] = save_dir;
	tot_unit[tot_things] = 0;
	for (int i = 0; i < totcube; i++) {
		if (creating_cube[i].exist) {
			u[tot_things][tot_unit[tot_things]].type = 0;
			u[tot_things][tot_unit[tot_things]].x = creating_cube[i].x;
			u[tot_things][tot_unit[tot_things]].y = creating_cube[i].y;
			u[tot_things][tot_unit[tot_things]].z = creating_cube[i].z;
			u[tot_things][tot_unit[tot_things]].texture_num = creating_cube[i].texture_num;
			u[tot_things][tot_unit[tot_things]].size = CREATING_CUBE_SIZE;
			tot_unit[tot_things]++;
		}
	}
	if (tot_unit[tot_things] > 0) tot_things++;
	if ((fopen_s(&f,r,"w"))!=0) printf_s("%s\n",r);
    printf_s("file %s opened\n",r);
	fprintf_s(f, "%d\n", tot_things);
	for (int i = 0; i < tot_things; i++) {
		fprintf_s(f, "%d %lf %lf %lf %lf\n", tot_unit[i],ori_x[i],ori_y[i],ori_z[i],ori_dir[i]);
		for (int j = 0; j < tot_unit[i]; j++){
			if (u[i][j].type == 0) {
				fprintf_s(f, "%d %lf %lf %lf %lf %d\n", u[i][j].type, u[i][j].x, u[i][j].y, u[i][j].z, u[i][j].size, u[i][j].texture_num);
			}
			if (u[i][j].type == 1) {
				fprintf_s(f, "%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %d\n", u[i][j].type,
					                                                                  u[i][j].p1x, u[i][j].p1y, u[i][j].p1z, 
					                                                                  u[i][j].p2x, u[i][j].p2y, u[i][j].p2z, 
					                                                                  u[i][j].p3x, u[i][j].p3y, u[i][j].p3z, 
					                                                                  u[i][j].p4x, &u[i][j].p4y, u[i][j].p4z, 
					                                                                  u[i][j].texture_num);
			}
		}
	}
	fclose(f);
	return;
}

#endif