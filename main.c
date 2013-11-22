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

bool reached;
void init() {
	time = 0;
	reached = false;
}

bool isCloseEnough(float *MyState, float *Target, float Margin) {
    /* Verifica che si e abbastanza vicini, ossia entro il margine 
     * che e' float ( reale ).
     */
    bool result = false;
    float diff[3];
    mathVecSubtract(diff, MyState, Target,3);
    float dist = mathVecMagnitude(diff,3);
    if(dist<Margin) 
        result = true;
    return result;
}

void rightAxis(float *v1, float *v2) {
	v1[0] = v2[0] + 1; 	// Aggiungo 1 per ottenere il giusto asse
	v1[1] = v2[1];
	v1[2] = v2[2];
}
void loop() {
	// States
	/*
	myState[0] (oppure myState[POS_X]): Posizione sul piano rispetto all'asse X.
	myState[1] (oppure myState[POS_Y]): Posizione sul piano rispetto all'asse Y.
	myState[2] (oppure myState[POS_Z]): Posizione sul piano rispetto all'asse Z.
	myState[3] (oppure myState[VEL_X]): Velocit? di spostamento sull'asse X.
	myState[4] (oppure myState[VEL_Y]): Velocit? di spostamento sull'asse Y.
	myState[5] (oppure myState[VEL_Z]): Velocit? di spostamento sull'asse Z.
	myState[6]: X del vettore di puntamento.
	myState[7]: Y del vettore di puntamento.
	myState[8]: Z del vettore di puntamento.
	myState[9]: Rotazione sull'asse X.
	myState[10]: Rotazione sull'asse Y.
	myState[11]: Rotazione sull'asse Z.
	*/
	float MyState[12];
	float OtherState[12];
	
	// Physics variables
	float R = .35;
    	float RTanTheta = 0.0245; // R*tan(4)
	
	// Vector buffers
	float Axis[3];
	float Helper[3];
	float Ideal[3];
	float Orbital[3];
	float OneSec[3];
	float Velocity[3];
	float Accel[3];
	float Force[3];
	
	api.getMyZRState(MyState);
    	api.getOtherZRState(OtherState);
	  
	
	rightAxis(Axis, OtherState);
	mathVecCross(Helper,Axis,MyState); 
	mathVecCross(Ideal,Helper,Axis);
	if(isCloseEnough(MyState, OtherState, 0.5)) {
        	reached = true;
    	}
	
	if(!reached)
		mathVecAdd(Ideal,Helper,OtherState, 3);
	else
		mathVecSubtract(Ideal,Helper,OtherState, 3);
	
	mathVecScale(Ideal,Ideal,R,true);
	mathVecScale(Orbital,Helper,RTanTheta,true);
	mathVecAdd(OneSec,Ideal,Orbital,3);
	mathVecScale(OneSec,OneSec,R,true);
	mathVecSubtract(Velocity,OneSec,MyState,3);
	mathVecSubtract(Accel,Velocity,&MyState[3],3);
	mathVecScale(Force,Accel,4.45,false);

	api.setPositionTarget(OneSec);		// imposto il target
	api.setVelocityTarget(Velocity);	// imposto la velocita'
	api.setForces(Force);			// Imposto la spinta 
  
}

void mathVecScale(float res[3], float src[3], float mag, bool norm) {
	memcpy(res,src,sizeof(float)*3);
	if(norm)
		mathVecNormalize(res,3);
	res[0]*=mag;
	res[1]*=mag;
	res[2]*=mag;
}   
