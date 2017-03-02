#include <math.h>

float **cartesianToPolar(float cartesian[][2]) {
  int points = sizeof(cartesian)/sizeof(cartesian[0]);
  float** polar = 0;
  polar = new float*[points];
  
  for (int i = 0; i < points; i++) {
    polar[i] = new float[2];
    
    float x = cartesian[i][0];
    float y = cartesian[i][1];
    
    float theta = atan2(y, x);
    float r = sqrt(x*x + y*y);
    
    polar[i][0] = r;
    polar[i][1] = theta;
  }
  
  return polar;
}

