/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.
    This file is part of ChibiOS/RT.
    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.
    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

static  uint8_t result=0 ;
static const uint8_t slave_address = 0x04;
char tyh[31]="TyH";
char pos[31]="pos";
int count_tyh=0;

int j=0;
int i=50;

MUTEX_DECL(mtx1);

static WORKING_AREA(waThread_LCD, 128);
static msg_t Thread_LCD(void *p)
{
  (void)p;
  chRegSetThreadName("SerialPrint");

  while (TRUE)
  {
		// decorado
		chThdSleepMilliseconds(2000);
		sdPut(&SD1, (uint8_t)0x7C);
		sdPut(&SD1, (uint8_t)0x18);
		sdPut(&SD1, 0);
		chThdSleepMilliseconds(100);

		sdPut(&SD1, (uint8_t)0x7C);
		sdPut(&SD1, (uint8_t)0x19);
		sdPut(&SD1, 60);
		chThdSleepMilliseconds(100);
		chMtxLock(&mtx1);
		chprintf((BaseSequentialStream *)&SD1, "     X      Y      Z");
		chMtxUnlock();
		chThdSleepMilliseconds(2000);
		sdPut(&SD1, (uint8_t)0x7C);
		sdPut(&SD1, (uint8_t)0x18);
		sdPut(&SD1, 0);
		chThdSleepMilliseconds(100);

		sdPut(&SD1, (uint8_t)0x7C);
		sdPut(&SD1, (uint8_t)0x19);
		sdPut(&SD1, 30);
		chThdSleepMilliseconds(100);
		chMtxLock(&mtx1);
		chprintf((BaseSequentialStream *)&SD1, "     T     H");
		chMtxUnlock();
		//escribe pocision
		int count3=0;
		for(int ia=0; ia<=100; ia++){
			chThdSleepMilliseconds(2000);
			sdPut(&SD1, (uint8_t)0x7C);
			sdPut(&SD1, (uint8_t)0x18);
			sdPut(&SD1, ia);
			chThdSleepMilliseconds(100);

			sdPut(&SD1, (uint8_t)0x7C);
			sdPut(&SD1, (uint8_t)0x19);
			sdPut(&SD1, 50);
			chThdSleepMilliseconds(100);
			chMtxLock(&mtx1);
			chprintf((BaseSequentialStream *)&SD1, "%c", tyh[count3]);
			chMtxUnlock();
			count3=count3+1;
			ia=ia+6;
			if (count3==15){
				count3=0;
			}
		}
		//escribe temperatura y humedad
		int count2=19;
		for(int ia=0; ia<=100; ia++){
			chThdSleepMilliseconds(2000);
			sdPut(&SD1, (uint8_t)0x7C);
			sdPut(&SD1, (uint8_t)0x18);
			sdPut(&SD1, ia);
			chThdSleepMilliseconds(100);

			sdPut(&SD1, (uint8_t)0x7C);
			sdPut(&SD1, (uint8_t)0x19);
			sdPut(&SD1, 20);
			chThdSleepMilliseconds(100);
			chMtxLock(&mtx1);
			chprintf((BaseSequentialStream *)&SD1, "%c", tyh[count2]);
			chMtxUnlock();
			count2=count2+1;
			ia=ia+6;
			if (count2==32){
				count2=19;
			}
		}
		sdPut(&SD1, (uint8_t)0x7C);
		sdPut(&SD1, (uint8_t)0x00);
    //chprintf((BaseSequentialStream *)&SD1, "%c", result);

    chThdSleepMilliseconds(500);
    //chprintf((BaseSequentialStream *)&SD1, "                  ");

  }
  return 0;
}

static WORKING_AREA(waThread_I2C, 128);
static msg_t Thread_I2C(void *p)
{
  (void)p;
  chRegSetThreadName("SerialPrintI2C");
  uint8_t request = 0;

  // Some time to allow slaves initialization
  chThdSleepMilliseconds(2000);

  while (TRUE)
  {
    // Request values
    chMtxLock(&mtx1);
    i2cMasterTransmitTimeout(&I2C0, slave_address, &request, 1,
                             &result, 2, MS2ST(1000));


    chMtxUnlock();
		//llena el espacio de memoria para la temepratura y para la humedad

		if((char)result=='p'){
			count_tyh=0;
		}
		if((char)result=='t'){
			count_tyh=19;
		}
		tyh[count_tyh]=result;
		count_tyh=count_tyh+1;

		if(count_tyh>=32){
			count_tyh=0;
		}
		chThdSleepMilliseconds(1500); // <-- aquí espera


    if (request == 5)
      request = 0;
    else
      request++;

    chThdSleepMilliseconds(2000);

  }
  return 0;
}

/*
 * Application entry point.
 */
int main(void)
{
  halInit();
  chSysInit();

  // Initialize Serial Port and Mutex
  sdStart(&SD1, NULL);
  chMtxInit(&mtx1);

  /*
   * LCD initialization.
   */
  chThdCreateStatic(waThread_LCD, sizeof(waThread_LCD), NORMALPRIO, Thread_LCD, NULL);

  /*
   * I2C initialization.
   */
  I2CConfig i2cConfig;
	//i2cConfig.ic_speed=100000;
  i2cStart(&I2C0, &i2cConfig);

  chThdCreateStatic(waThread_I2C, sizeof(waThread_I2C), HIGHPRIO, Thread_I2C, NULL);


  /*
   * Events servicing loop.
   */
  chThdWait(chThdSelf());

  return 0;
}
