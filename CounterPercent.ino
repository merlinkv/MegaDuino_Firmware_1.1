
void lcdSpinner() {
    if (millis() - timeDiff2 > 1000) {   // check switch every 50ms 
        timeDiff2 = millis();           // get current millisecond count
        #ifdef LCD16          
          lcd.setCursor(15,1);
          lcd.print(indicators[spinpos++]);
        #endif
        #ifdef LCD20          
          lcd.setCursor(19,1);
          lcd.print(indicators[spinpos++]);
        #endif        
        #ifdef OLED1306
           setXY(15,1);sendChar(indicators[spinpos++]);                 
        #endif
        if (spinpos > 3) {   
          spinpos = 0;
        }
    } 
}

void lcdTime() {
    if (millis() - timeDiff2 > 1000) {   // check switch every second 
        timeDiff2 = millis();           // get current millisecond count
        #ifdef LCD16
            if (lcdsegs % 10 != 0) {itoa(lcdsegs%10,PlayBytes,10);lcd.setCursor(15,1);lcd.print(PlayBytes);} // ultima cifra 1,2,3,4,5,6,7,8,9
            else 
               if (lcdsegs % CNTRBASE != 0){itoa(lcdsegs%CNTRBASE,PlayBytes,10);lcd.setCursor(14,1);lcd.print(PlayBytes);} // es 10,20,30,40,50,60,70,80,90,110,120,..
               else 
                  if (lcdsegs % (CNTRBASE*10) != 0) {itoa(lcdsegs%(CNTRBASE*10)/CNTRBASE*100,PlayBytes,10);lcd.setCursor(13,1);lcd.print(PlayBytes);} // es 100,200,300,400,500,600,700,800,900,1100,..
                  else {lcd.setCursor(13,1);lcd.print("000");} // es 000,1000,2000,...
           lcdsegs++;
        #endif
        #ifdef LCD20
            if (lcdsegs % 10 != 0) {itoa(lcdsegs%10,PlayBytes,10);lcd.setCursor(19,1);lcd.print(PlayBytes);} // ultima cifra 1,2,3,4,5,6,7,8,9
            else 
               if (lcdsegs % CNTRBASE != 0){itoa(lcdsegs%CNTRBASE,PlayBytes,10);lcd.setCursor(18,1);lcd.print(PlayBytes);} // es 10,20,30,40,50,60,70,80,90,110,120,..
               else 
                  if (lcdsegs % (CNTRBASE*10) != 0) {itoa(lcdsegs%(CNTRBASE*10)/CNTRBASE*100,PlayBytes,10);lcd.setCursor(17,1);lcd.print(PlayBytes);} // es 100,200,300,400,500,600,700,800,900,1100,..
                  else {lcd.setCursor(17,1);lcd.print("000");} // es 000,1000,2000,...
           lcdsegs++;
        #endif        
        #ifdef OLED1306
            #ifdef XY2force
              if (lcdsegs % 10 != 0) {itoa(lcdsegs%10,input,10);sendStrXY(input,15,0);} // ultima cifra 1,2,3,4,5,6,7,8,9
              else 
                 if (lcdsegs % CNTRBASE != 0){itoa((lcdsegs%CNTRBASE)/10,input,10);input[1]='0';input[2]=0;sendStrXY(input,14,1);} // es 10,20,30,40,50,60,70,80,90,110,120,..
                 else 
                    if (lcdsegs % (CNTRBASE*10) != 0) {itoa((lcdsegs% (CNTRBASE*10))/CNTRBASE,input,10);input[1]='0';input[2]='0';input[3]=0;sendStrXY(input,13,1);} // es 100,200,300,400,500,600,700,800,900,1100,..
                    else {sendStrXY("000",13,1);} // es 000,1000,2000,...
  
             lcdsegs++;             
            #else
              if (lcdsegs % 10 != 0) {setXY(15,1);sendChar(48+lcdsegs%10);} // ultima cifra 1,2,3,4,5,6,7,8,9
              else 
                 if (lcdsegs % CNTRBASE != 0){setXY(14,1);sendChar(48+(lcdsegs%CNTRBASE)/10);sendChar('0');} // es 10,20,30,40,50,60,70,80,90,110,120,..
                 else 
                    if (lcdsegs % (CNTRBASE*10) != 0) {setXY(13,1);sendChar(48+(lcdsegs% (CNTRBASE*10))/CNTRBASE);sendChar('0');sendChar('0');} // es 100,200,300,400,500,600,700,800,900,1100,..
                    else {setXY(13,1);sendChar('0');sendChar('0');sendChar('0');} // es 000,1000,2000,...
  
             lcdsegs++; 
           #endif   
        #endif
    }
}

void lcdPercent() {  
    newpct=(100 * bytesRead)/filesize;                   
    if (currpct ==100){
        currpct= 0;
        #ifdef LCD16  
          lcd.setCursor(9,1);
          lcd.print(newpct);lcd.print("%");  
          //lcdSpinner(); 
        #endif
        #ifdef LCD20  
          lcd.setCursor(11,1);
          lcd.print(newpct);lcd.print("%");  
          //lcdSpinner(); 
        #endif        
        #ifdef OLED1306
          //strcat_P(PlayBytes,PSTR("%"));
          #ifdef XY2force
            if (newpct <10) {itoa(newpct,input,10);input[1]='%'; input[2]=0;sendStrXY(input,8,0);}
            else
              if (newpct <100){itoa(newpct,input,10);input[2]='%'; input[3]=0;sendStrXY(input,8,0);}
              else {sendStrXY("100%",8,0);}
                       
          #else
            if (newpct <10) {setXY(8,1);sendChar(48+newpct%10);}
            else
              if (newpct <100){setXY(8,1);sendChar(48+newpct/10); sendChar(48+newpct%10);}
              else {setXY(8,1);sendChar('1');sendChar('0');sendChar('0');}
              
            sendChar('%');sendChar(' ');
          #endif
        #endif
    }
    if ((newpct >currpct)&& (newpct % 1 == 0)) {
         #ifdef LCD16            
            lcd.setCursor(9,1);
            lcd.print(newpct);lcd.print("%"); 
         #endif
         #ifdef LCD20
            lcd.setCursor(11,1);
            lcd.print(newpct);lcd.print("%"); 
         #endif                       
        #ifdef OLED1306
          #ifdef XY2force
            if (newpct <10) {itoa(newpct,input,10);input[1]='%'; input[2]=0;sendStrXY(input,8,0);}
            else
              if (newpct <100){itoa(newpct,input,10);input[2]='%'; input[3]=0;sendStrXY(input,8,0);}
              else {sendStrXY("100%",8,0);}
                     
          #else
            if (newpct <10) {setXY(8,1);sendChar(48+newpct%10);}
            else
              if (newpct <100){setXY(8,1);sendChar(48+newpct/10); sendChar(48+newpct%10);}
              else {setXY(8,1);sendChar('1');sendChar('0');sendChar('0');}
              
            sendChar('%');
          #endif
        #endif
        currpct = newpct;
    } 
}
