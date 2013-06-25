/* Global Library Variables */
int time;

void zr_varinit()
{
  time = 0;

}


void loop(){
    float go[] = {0,0,.13};
    float stop[] = {0,0,-.13};
 
    if(time<5) api.setForces(go);
    if(9<time && time<15) api.setForces(stop);
             
    time++;
}