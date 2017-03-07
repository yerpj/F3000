/******************/
/* F3000 emulator */
/******************/

//inputs
Motp=A5;
Motm=A6;
STOP=A7;
START=B1;

//outputs
Came=B3;
Shifter=B4;
Rapportp=B5;
Rapportm=B6;
Neutre=B7;

var Gear=1;
var motorAngle=355;
var motorAngleNSet=0;
var IsInNeutral=0;
var motorDir="A";
var motorStepDuration_ms=5;
var Rp=0;  //flag.increments when Rapportp is rised
var Rm=0;  //flag.increments when Rapportm is rised


function onInit()
{
  USB.setConsole(true);
  digitalWrite(LED2,1);
  init();
}

function init()
{
  pinMode(Motp,'input_pulldown');
  pinMode(Motm,'input_pulldown');
  pinMode(STOP,'input_pulldown');
  pinMode(START,'input_pulldown');
  pinMode(Came,'output');
  digitalWrite(Came,0);
  pinMode(Shifter,'output');
  digitalWrite(Shifter,0);
  pinMode(Rapportp,'output');
  digitalWrite(Rapportp,0);
  pinMode(Rapportm,'output');
  digitalWrite(Rapportm,0);
  pinMode(Neutre,'output');
  digitalWrite(Neutre,0);
}

function N()
{
  return digitalRead(Neutre);
}

function A()
{
  return motorAngle;
}

function motorhandle()
{
  if( digitalRead(Motp) && !digitalRead(Motm) )
  {//dir A == UP
    motorDir="A";
    motorAngle--;
    if(motorAngle<0)
      motorAngle=359;
    //console.log(motorAngle);
  }
  else if( digitalRead(Motm) && !digitalRead(Motp) )
  {//dir B == DOWN
    motorDir="B";
    motorAngle++;
    if(motorAngle>359)
      motorAngle=0;
    //console.log(motorAngle);
  }
  else if( !digitalRead(Motm) && !digitalRead(Motp) )
  {//moteur à l'arret
    if( digitalRead(Neutre) && Gear!=0)
    {
      Gear=0;
      console.log("Gear="+Gear);
      Rp=0;
      Rm=0;
    }
    else if(Rp)
    {
      if(Gear==0)
        Gear=2;
      else if(Gear<5)
        Gear++;
      Rp=0;
      console.log("Gear="+Gear);
    }
    else if(Rm)
    {
      if(Gear==0)
        Gear=1;
      else if(Gear>1)
        Gear--;
      Rm=0;
      console.log("Gear="+Gear);
    }
  }
  //outputs management
  if( digitalRead(Motm) || digitalRead(Motp) )
  {
    //CAME handle
    if( motorAngle>345 || motorAngle<15 || (motorAngle>165 && motorAngle<195) )
    {
      if(!digitalRead(Came))
      {
        console.log(motorDir+" "+motorAngle+" "+"C");
        digitalWrite(Came,1);
        /*if(Rp)
        {
          if(Gear==0)
            Gear=2;
          else if(Gear<5)
            Gear++;
          Rp=0;
        }
        else if(Rm)
        {
          if(Gear==0)
            Gear=1;
          else if(Gear>1)
            Gear--;
          Rm=0;
        }*/
        //console.log("Gear="+Gear);
      }
    }
    else
    {
      if(digitalRead(Came))
      {
        console.log(motorDir+" "+motorAngle+" "+"c");
        digitalWrite(Came,0);
      }
    }
    //SHIFTER handle
    if((motorAngle>50 && motorAngle<130) || (motorAngle>230 && motorAngle<310))
    {
      if(!digitalRead(Shifter))
      {
        console.log(motorDir+" "+motorAngle+" "+"S");
        digitalWrite(Shifter,1);
      }
    }
    else
    {
      if(digitalRead(Shifter))
      {
        console.log(motorDir+" "+motorAngle+" "+"s");
        digitalWrite(Shifter,0);
      }
    }
    if(motorDir=="A")
    {
      //RAPPORT+ handle
      if( (motorAngle>120 && motorAngle<165) || (motorAngle>300 && motorAngle<345) )
      {
        if(!digitalRead(Rapportp))
        {
          console.log(motorDir+" "+motorAngle+" "+"R+");
          digitalWrite(Rapportp,1);
          Rp++;
        }
      }
      else
      {
        if(digitalRead(Rapportp))
        {
          console.log(motorDir+" "+motorAngle+" "+"r+");
          digitalWrite(Rapportp,0);
        }
      }
      //NEUTRE handle
      if(digitalRead(Neutre))
      {
        if( ((motorAngle>180 && motorAngle<190) || (motorAngle>0 && motorAngle<10)) && Gear!=0 )
        {
          digitalWrite(Neutre,0);
          console.log(motorDir+" "+motorAngle+" "+"na1");
        }
        if( ((motorAngle>80 && motorAngle<90) || (motorAngle>260 && motorAngle<270)) && Gear==1 )
        {//mise à 0 du neutre lorsqu'on passe de la 1 à la 2
          digitalWrite(Neutre,0);
          console.log(motorDir+" "+motorAngle+" "+"na2");
        }
        if( ((motorAngle>90 && motorAngle<180) || (motorAngle>270 && motorAngle<360)) && Gear==0 )
        {
          digitalWrite(Neutre,0);
          console.log(motorDir+" "+motorAngle+" "+"na3");
        }
      }
      else
      {//if( ((motorAngle>250 && motorAngle<270) || (motorAngle>70 && motorAngle<90)) && Gear==1 )
        if( ((motorAngle>270 && motorAngle<290) || (motorAngle>90 && motorAngle<110)) && Gear==1 )
        {
          digitalWrite(Neutre,1);
          console.log(motorDir+" "+motorAngle+" "+"Na");
        }
      }
    }
    else
    {
      //RAPPORT- handle
      if( (motorAngle>195 && motorAngle<240) || (motorAngle>15 && motorAngle<60) )
      {
        if(!digitalRead(Rapportm))
        {
          console.log(motorDir+" "+motorAngle+" "+"R-");
          digitalWrite(Rapportm,1);
          Rm++;
        }
      }
      else
      {
        if(digitalRead(Rapportm))
        {
          console.log(motorDir+" "+motorAngle+" "+"r-");
          digitalWrite(Rapportm,0);
        }
      }
      //NEUTRE handle
      if(digitalRead(Neutre))
      {
        if( ((motorAngle>350 && motorAngle<360) || (motorAngle>170 && motorAngle<180)) && Gear!=0 )
        {
          digitalWrite(Neutre,0);
          console.log(motorDir+" "+motorAngle+" "+"nb1");
        }
        if( ((motorAngle>270 && motorAngle<280) || (motorAngle>90 && motorAngle<100)) && Gear==2 )
        {//mise à 0 du neutre lorsqu'on passe de la 2 à la 1
          digitalWrite(Neutre,0);
          console.log(motorDir+" "+motorAngle+" "+"nb2");
        }
        if( ((motorAngle>0 && motorAngle<90) || (motorAngle>180 && motorAngle<270)) && Gear==0 )
        {
          digitalWrite(Neutre,0);
          console.log(motorDir+" "+motorAngle+" "+"nb3");
        }
      }
      else
      {//if( ((motorAngle>90 && motorAngle<110) || (motorAngle>270 && motorAngle<290)) && Gear==2 )
        if( ((motorAngle>70 && motorAngle<90) || (motorAngle>250 && motorAngle<270)) && Gear==2 )
        {
          digitalWrite(Neutre,1);
          console.log(motorDir+" "+motorAngle+" "+"Nb");
        }
      }
    }
  }
}
init();
setInterval(motorhandle,motorStepDuration_ms);

//save();