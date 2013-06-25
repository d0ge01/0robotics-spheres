/* Global Library Variables */
int time;
bool reachedOther;

void zr_varinit()
{
  time = 0;

}

void mathVecScale(float res[3], float src[3], float mag, bool norm)
{
    memcpy(res,src,sizeof(float)*3);
    if(norm) mathVecNormalize(res,3);
    res[0]*=mag;
    res[1]*=mag;
    res[2]*=mag;
}

bool isCloseEnough(float *MyState, float *Target, float Margin)
{
    bool result = false;
    float diff[3];
    mathVecSubtract(diff, MyState, Target,3);
    float dist = mathVecMagnitude(diff,3);
    if(dist<Margin) 
        result = true;
     
    return result;
}
void ASSERT(int shouldbetrue) {}

void loop(){
    DEBUG(("\nHello Space! Time: %d",time));
    float Diff[3];
    float MyState[12];
    float OtherState[12];
     
    api.getMyZRState(MyState);
    api.getOtherZRState(OtherState);
 
    if(isCloseEnough(MyState, OtherState, .1))
    {
        reachedOther = true;
    }
     
    if(!reachedOther)
    {
        mathVecSubtract(Diff,OtherState, MyState,3);
        Diff[0]*=.25f;
        Diff[1]*=.25f;
        Diff[2]*=.25f;
        api.setVelocityTarget(Diff);
    }
    else
    {
        float Waypoint2[] = {0.0f,-0.5f,-0.5f};
        api.setPositionTarget(Waypoint2);
    }
     
    time++;
}
