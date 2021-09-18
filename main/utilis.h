void saturate(float *x,float up, float down);
void resetSpdError();
void resetAngError();
void PID_Speed();
void PID_angle();

void resetSpdError()
{
  e_spd     = 0;
  ePrev_spd = 0;
  E_spd     = 0;
  dE_spd    = 0;
}

void resetAngError()
{
  e_ang     = 0;
  ePrev_ang = 0;
  E_ang     = 0;
  dE_ang    = 0;
}

void PID_Speed()
{
  e_spd = reqSpdValue - angularSpeed;
  E_spd = E_spd + e_spd;
  dE_spd = e_spd - ePrev_spd;
  float ctrlInput = (kp_spd * e_spd) + (ki_spd * E_spd) + (kd_spd * dE_spd); // ctrl action.

    // Saturation.
  if (ctrlInput > 80)
    ctrlInput = 80;
    
  // Ctrl Action and direction control
 if (dirFlag == 1) // CW
  {
    motor.rotate(ctrlInput,CW);
  }
  else
   {
    motor.rotate(ctrlInput,CCW);
    } 
  ePrev_spd = e_spd;
  }

  
void PID_angle(){
  e_ang = reqAngValue - yaw;  // proportinal erroe
  E_ang = E_ang + e_ang;      // integrator error
  dE_ang = e_ang - ePrev_ang; // d/dt error

  float ctrlInputAng = 15*((float)5/(float)30) * e_ang + (1 * dE_ang);  
  
  //saturation  
  saturate(&ctrlInputAng,2, -2) ;
  // Control action
  motor.rotate(ctrlInputAng*10,1);

  // equating errors.
  ePrev_ang = e_ang;
}

void saturate(float *x,float up, float down)
{
  if (*x>up){
    *x = up ;
  }
  else if(*x<down){
    *x =-down ;
  }
}
