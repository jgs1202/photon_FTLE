int getX(int id, int side) {
	return id - (id / side) * side;
}

int getY(int id, int side) {
	return id / side;
}

__kernel void setPhotons(__global float* photonPosition2D, __global float* photonDirection2D,
	__global float* photonColor2D, __global float* photonGradDirection2D, __global float* photonIrradiance2D,
	int side, int phaseNum)
{
    int position = get_global_id(0), coordinate;
    int y = getY(position, side);
    int x = getX(position, side, y);

    for (int phi=0; phi<phaseNum; ++phi) {
    	coordinate = ((x + y * side) * phaseNum + phi) * 3;
    	photonPosition2D[coordinate] = x;
    	photonPosition2D[coordinate + 1] = y;
    	photonPosition2D[coordinate + 2] = 0;
    	photonDirection2D[coordinate + 0] = cos(2 * M_PI / phaseNum * phi);
    	photonDirection2D[coordinate + 1] = sin(2 * M_PI / phaseNum * phi);
    	photonDirection2D[coordinate + 2] = 0;

    	photonColor2D[coordinate + 0] = 1.;
    	photonColor2D[coordinate + 1] = 1.;
    	photonColor2D[coordinate + 2] = 1.;
    	photonGradDirection2D[coordinate + 0] = 0.;
    	photonGradDirection2D[coordinate + 1] = 0.;
    	photonGradDirection2D[coordinate + 2] = 0.;
    	photonIrradiance2D[coordinate] = 1.;
    }

}