/* Global Library Variables */
/* Questo praticamente ricava la posizione dello spheres rosso ,
   e gli va addosso occupando lo stesso spazio ( ossia le stesse
   cordinate, nella realtà è impossibile, in quanto si scontrebbero
   ( evitato dal sistema di sicurezza CA che però nella freemode del
   simulatore è disattivato ) */
float myVar[3];
int time;

void zr_varinit()
{
  myVar[0] = 0;
  myVar[1] = 0;
  myVar[2] = 0.13;
	time = 0;

}

void ASSERT(int shouldbetrue) {}

void loop()
{
	DEBUG(("\nDebug!, time: %d", time));
	
	float OtherState[12];
  api.getOtherZRState(OtherState);
  api.setPositionTarget(OtherState);
	
  time++;
  return;
}
