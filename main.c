/*
	Author:		Salvatore Criscione
	Email:		not.salvatore@logorroici.org
	License:	GPL

                    .,-:;//;:=,
               . :H@@@MM@M#H/.,+%;,             
            ,/X+ +M@@M@MM%=,-%HMMM@X/,
          -+@MM; $M@@MH+-,;XMMMM@MMMM@+-
         ;@M@@M- XM@X;. -+XXXXXHHH@M@M#@/.
       ,%MM@@MH ,@%=             .---=-=:=,.
       =@#@@@MX.,                -%HX$$%%%:;
      =-./@M@M$                   .;@MMMM@MM:   
      X@/ -$MM/                    . +MM@@@M$   <Salvatore Criscione :D>
     ,@M@H: :@:                    . =X#@@@@-
     ,@@@MMX, .                    /H- ;@M@M=
     .H@@@@M@+,                    %MM+..%#$.
      /MMMM@MMH/.                  XM@MH; =;
       /%+%$XHH@$=              , .H@@@@MX,
        .=--------.           -%H.,@@@@@MX,
        .%MM@@@HHHXX$$$%+- .:$MMX =M@@MM%.
          =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=
            =%@M@M#@$-.=$@MM@@@M; %M%=
              ,:+$+-,/H#MMMMMMM@= =,
                    =++%%%%+/:-. 
*/
int time;		// Tempo, usato per vedere quanti loop fa
float res[3];

void init() {
	time = 0;	// Imposto tempo = 0
	res[0] = 0;
	res[1] = 0;
	res[2] = 0;

}


void ottieniXYZ(float ret[3], float myState[12]) {
	ret[0] = myState[0];
	ret[1] = myState[1]; 
	ret[2] = myState[2];
}

void ottieniSpinta(float ret[3], float now[3], float target[3]) {
	ret[0] = ((target[0] - now[0] ) / 2 );
	ret[1] = ((target[1] - now[1] ) / 2 );
	ret[2] = ((target[2] - now[2] ) / 2 );
}

void ottieniSpintaInversa(float ret[3], float now[3], float target[3]) {
	ret[0] = -1 * ((target[0] - now[0] ) / 2 );
	ret[1] = -1 * ((target[1] - now[1] ) / 2 );
	ret[2] = -1 * ((target[2] - now[2] ) / 2 );
}
bool vicino(float now[3], float target[3], float error) {
	bool reached = false;
	
	reached = (target[0] - now[0] ) < error;
	reached = reached && (( target[1] - now[1] ) < error );
	reached = reached && (( target[2] - now[2] ) < error );
	return reached;
}

void sommaVettori(float ret[3], float pow[3]) {
	ret[0] += pow[0];
	ret[1] += pow[1];
	ret[2] += pow[2];
}

bool verificaNullo(float ret[3]) {
	if ( ret[0] == 0 && ret[1] == 0 && ret[2] == 0 )
		return true;
	else
		return false;
}


void loop() {
	float miaPosizione[12];		// Posizione mia
	
	// 4 punti destinazione
	float punto1[] = { -.5, -.5, 0};
	float punto2[] = { -.5, .5, 0};
	float punto3[] = { .5, -.5, 0};
	float punto4[] = { .5, .5, 0};
	
	float now[3];
	float spinta[3];	

	// prendo la mia posizione
	api.getMyZRState(miaPosizione);
	
	ottieniXYZ(now, miaPosizione);

	if ( !vicino(now, punto1, 0.3 ))
		ottieniSpinta(spinta, now, punto1);
	else
		if ( !verificaNullo(res) )
			ottieniSpintaInversa(spinta, now, punto1);

	DEBUG(("Tempo di rilascio: %d X:%f Y:%f Z: %f", time, now[0], now[1], now[2]));
	if (!verificaNullo(spinta))
		api.setForces(spinta);
	sommaVettori(res, spinta);
}
