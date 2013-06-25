/* Global Library Variables */
int time;

void zr_varinit()
{
    time = 0;

}

void ASSERT(int shouldbetrue) {}

void loop(){
    DEBUG(("\nHello Space! Time: %d",time));
    float Diff[3];
    float MyState[12];
    float OtherState[12];
     
    api.getMyZRState(MyState);
    api.getOtherZRState(OtherState);
    mathVecSubtract(Diff,OtherState, MyState,3);
    api.setVelocityTarget(Diff);
     
    time++;
}
