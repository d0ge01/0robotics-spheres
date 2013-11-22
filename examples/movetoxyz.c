/**
 * Il codice fa spostare il satellite alle coordinate X Y Z {0.5, 0.3, -0.4}
 * Il codice per spostarsi usa l'API: setPositionTarget( [3] );
 * Il codice utilizza la funzione: DEBUG(()); per stampare il tempo di rilascio del codice.
*/
int time;
 
void init() {
	time = 0;
}
 
void loop() {
	float obbiettivo[3] = {0.5, 0.3, -0.4};
	api.setPositionTarget( obbiettivo );
	DEBUG(("Tempo di rilascio: %d \n", time));
	time++;
}
