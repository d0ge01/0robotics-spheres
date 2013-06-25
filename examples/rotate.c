/* Global Library Variables */
bool reachedOther;

void zr_varinit()
{

}

void mathVecScale(float res[3], float src[3], float mag, bool norm)
{
    memcpy(res,src,sizeof(float)*3);
    if(norm) mathVecNormalize(res,3);
    res[0]*=mag;
    res[1]*=mag;
    res[2]*=mag;
}

void ASSERT(int shouldbetrue) {}

void loop(){
    float MyState[12];
    float OtherState[12];
 
    api.getMyZRState(MyState);
    api.getOtherZRState(OtherState);
 
    float dir[3];
    mathVecSubtract(dir,OtherState,MyState,3);
    mathVecNormalize(dir,3);
     
    api.setAttitudeTarget(dir);
 
    float dotProd = mathVecInner(dir,&MyState[6],3);
    if(dotProd>.985)
    {
        api.setPositionTarget(OtherState);
    }
}