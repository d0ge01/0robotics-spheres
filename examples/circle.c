/* Global Library Variables */
int time;

void zr_varinit()
{
  time = 0;

}

void loop(){
    float MyState[12];  // MyState to get Actual Position
    float Blue[] = {1,0,0}; // Axis of Rotation
    float Pink[3];      // Helper 
    float DarkGreen[3]; // Ideal Position
    float Red[3];       // Orbital Distance Vector
    float Orange[3];    // Desired Position 1 sec. from now
    float Velocity[3];  // Desired Velocity
    float Accel[3];     // Desired Acceleration
    float Force[3];     // Desired Force
    float R = .35;
    float RTanTheta = 0.0245; // R*tan(4 degrees)
  
    // So where are we?
    api.getMyZRState(MyState);
     
    // Do the Math
    mathVecCross(Pink,Blue,MyState); // MyState = &MyState[0] = Light Green
    mathVecCross(DarkGreen,Pink,Blue);
    mathVecScale(DarkGreen,DarkGreen,R,true);
    mathVecScale(Red,Pink,RTanTheta,true);
    mathVecAdd(Orange,DarkGreen,Red,3);
    mathVecScale(Orange,Orange,R,true);
    mathVecSubtract(Velocity,Orange,MyState,3);
    mathVecSubtract(Accel,Velocity,&MyState[3],3);
    mathVecScale(Force,Accel,4.45,false);
 
    // Go there...
    //api.setPositionTarget(Orange);
    //api.setVelocityTarget(Velocity);
    api.setForces(Force);
  
}
                          
// To ease scaling use our utility function
void mathVecScale(float res[3], float src[3], float mag, bool norm)
{
    memcpy(res,src,sizeof(float)*3);
    if(norm) mathVecNormalize(res,3);
    res[0]*=mag;
    res[1]*=mag;
    res[2]*=mag;
}       