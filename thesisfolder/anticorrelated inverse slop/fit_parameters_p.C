#include "fit_parameters_p.h"

// must follow the order of files in the directory, adjust the size of arrays accordingly
double parameter_point[15][15];
double parameter_flat[15][15];
double parameter_steeper[15][15];

// phenix-p-AuAu-200-2004
parameter_point[0][0] = {0,0};
parameter_flat[0][0] = {0,0};
parameter_steeper[0][0] = {0,0};

parameter_point[0][1] = {0,0};
parameter_flat[0][1] = {0,0};
parameter_steeper[0][1] = {0,0};

parameter_point[0][2] = {0,0};
parameter_flat[0][2] = {0,0};
parameter_steeper[0][2] = {0,0};

parameter_point[0][3] = {0,0};
parameter_flat[0][3] = {0,0};
parameter_steeper[0][3] = {0,0};

parameter_point[0][4] = {0,0};
parameter_flat[0][4] = {0,0};
parameter_steeper[0][4] = {0,0};

parameter_point[0][5] = {0,0};
parameter_flat[0][5] = {0,0};
parameter_steeper[0][5] = {0,0};

parameter_point[0][6] = {0,0};
parameter_flat[0][6] = {0,0};
parameter_steeper[0][6] = {0,0};

parameter_point[0][7] = {0,0};
parameter_flat[0][7] = {0,0};
parameter_steeper[0][7] = {0,0};

parameter_point[0][8] = {0,0};
parameter_flat[0][8] = {0,0};
parameter_steeper[0][8] = {0,0};

parameter_point[0][9] = {0,0};
parameter_flat[0][9] = {0,0};
parameter_steeper[0][9] = {0,0};

parameter_point[0][10] = {0,0};
parameter_flat[0][10] = {0,0};
parameter_steeper[0][10] = {0,0};

// phenix-p-AuAu-200
parameter_point[1][0] = {0,0};
parameter_flat[1][0] = {0,0};
parameter_steeper[1][0] = {0,0};

parameter_point[1][1] = {0,0};
parameter_flat[1][1] = {0,0};
parameter_steeper[1][1] = {0,0};

parameter_point[1][2] = {0,0};
parameter_flat[1][2] = {0,0};
parameter_steeper[1][2] = {0,0};

parameter_point[1][3] = {0,0};
parameter_flat[1][3] = {0,0};
parameter_steeper[1][3] = {0,0};

parameter_point[1][4] = {0,0};
parameter_flat[1][4] = {0,0};
parameter_steeper[1][4] = {0,0};

//phenix-p-dAu-200
parameter_point[2][0] = {0,0};
parameter_flat[2][0] = {0,0};
parameter_steeper[2][0] = {0,0};

parameter_point[2][1] = {0,0};
parameter_flat[2][1] = {0,0};
parameter_steeper[2][1] = {0,0};

parameter_point[2][2] = {0,0};
parameter_flat[2][2] = {0,0};
parameter_steeper[2][2] = {0,0};

parameter_point[2][3] = {0,0};
parameter_flat[2][3] = {0,0};
parameter_steeper[2][3] = {0,0};

parameter_point[2][4] = {0,0};
parameter_flat[2][4] = {0,0};
parameter_steeper[2][4] = {0,0};

//phenix-p-pp-200
parameter_point[3][0] = {0,0};
parameter_flat[3][0] = {0,0};
parameter_steeper[3][0] = {0,0};

//phenix-pbar-AuAu-200-2004
parameter_point[4][0] = {0,0};
parameter_flat[4][0] = {0,0};
parameter_steeper[4][0] = {0,0};

parameter_point[4][1] = {0,0};
parameter_flat[4][1] = {0,0};
parameter_steeper[4][1] = {0,0};

parameter_point[4][2] = {0,0};
parameter_flat[4][2] = {0,0};
parameter_steeper[4][2] = {0,0};

parameter_point[4][3] = {0,0};
parameter_flat[4][3] = {0,0};
parameter_steeper[4][3] = {0,0};

parameter_point[4][4] = {0,0};
parameter_flat[4][4] = {0,0};
parameter_steeper[4][4] = {0,0};

parameter_point[4][5] = {0,0};
parameter_flat[4][5] = {0,0};
parameter_steeper[4][5] = {0,0};

parameter_point[4][6] = {0,0};
parameter_flat[4][6] = {0,0};
parameter_steeper[4][6] = {0,0};

parameter_point[4][7] = {0,0};
parameter_flat[4][7] = {0,0};
parameter_steeper[4][7] = {0,0};

parameter_point[4][8] = {0,0};
parameter_flat[4][8] = {0,0};
parameter_steeper[4][8] = {0,0};

parameter_point[4][9] = {0,0};
parameter_flat[4][9] = {0,0};
parameter_steeper[4][9] = {0,0};

parameter_point[4][10] = {0,0};
parameter_flat[4][10] = {0,0};
parameter_steeper[4][10] = {0,0};

//phenix-pbar-AuAu-200
parameter_point[5][0] = {0,0};
parameter_flat[5][0] = {0,0};
parameter_steeper[5][0] = {0,0};

parameter_point[5][1] = {0,0};
parameter_flat[5][1] = {0,0};
parameter_steeper[5][1] = {0,0};

parameter_point[5][2] = {0,0};
parameter_flat[5][2] = {0,0};
parameter_steeper[5][2] = {0,0};

parameter_point[5][3] = {0,0};
parameter_flat[5][3] = {0,0};
parameter_steeper[5][3] = {0,0};

parameter_point[5][4] = {0,0};
parameter_flat[5][4] = {0,0};
parameter_steeper[5][4] = {0,0};

//phenix-pbar-dAu-200
parameter_point[6][0] = {0,0};
parameter_flat[6][0] = {0,0};
parameter_steeper[6][0] = {0,0};

parameter_point[6][1] = {0,0};
parameter_flat[6][1] = {0,0};
parameter_steeper[6][1] = {0,0};

parameter_point[6][2] = {0,0};
parameter_flat[6][2] = {0,0};
parameter_steeper[6][2] = {0,0};

parameter_point[6][3] = {0,0};
parameter_flat[6][3] = {0,0};
parameter_steeper[6][3] = {0,0};

parameter_point[6][4] = {0,0};
parameter_flat[6][4] = {0,0};
parameter_steeper[6][4] = {0,0};

//phenix-pbar-pAl-200
parameter_point[7][0] = {0,0};
parameter_flat[7][0] = {0,0};
parameter_steeper[7][0] = {0,0};

parameter_point[7][1] = {0,0};
parameter_flat[7][1] = {0,0};
parameter_steeper[7][1] = {0,0};

parameter_point[7][2] = {0,0};
parameter_flat[7][2] = {0,0};
parameter_steeper[7][2] = {0,0};

parameter_point[7][3] = {0,0};
parameter_flat[7][3] = {0,0};
parameter_steeper[7][3] = {0,0};

//phenix-pbar-pAu-200
parameter_point[8][0] = {0,0};
parameter_flat[8][0] = {0,0};
parameter_steeper[8][0] = {0,0};

parameter_point[8][1] = {0,0};
parameter_flat[8][1] = {0,0};
parameter_steeper[8][1] = {0,0};

parameter_point[8][2] = {0,0};
parameter_flat[8][2] = {0,0};
parameter_steeper[8][2] = {0,0};

parameter_point[8][3] = {0,0};
parameter_flat[8][3] = {0,0};
parameter_steeper[8][3] = {0,0};

parameter_point[8][4] = {0,0};
parameter_flat[8][4] = {0,0};
parameter_steeper[8][4] = {0,0};

parameter_point[8][5] = {0,0};
parameter_flat[8][5] = {0,0};
parameter_steeper[8][5] = {0,0};

//phenix-pbar-pp-200
parameter_point[9][0] = {0,0};
parameter_flat[9][0] = {0,0};
parameter_steeper[9][0] = {0,0};

//phenix-proton-3HeAu-200
parameter_point[10][0] = {0,0};
parameter_flat[10][0] = {0,0};
parameter_steeper[10][0] = {0,0};

parameter_point[10][1] = {0,0};
parameter_flat[10][1] = {0,0};
parameter_steeper[10][1] = {0,0};

parameter_point[10][2] = {0,0};
parameter_flat[10][2] = {0,0};
parameter_steeper[10][2] = {0,0};

parameter_point[10][3] = {0,0};
parameter_flat[10][3] = {0,0};
parameter_steeper[10][3] = {0,0};

parameter_point[10][4] = {0,0};
parameter_flat[10][4] = {0,0};
parameter_steeper[10][4] = {0,0};

//phenix-proton-CuAu-200
parameter_point[11][0] = {0,0};
parameter_flat[11][0] = {0,0};
parameter_steeper[11][0] = {0,0};

parameter_point[11][1] = {0,0};
parameter_flat[11][1] = {0,0};
parameter_steeper[11][1] = {0,0};

parameter_point[11][2] = {0,0};
parameter_flat[11][2] = {0,0};
parameter_steeper[11][2] = {0,0};
