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

static const uint8_t slave_address = 0x04;
uint8_t historico [3][29];

MUTEX_DECL(mtx1);
static WORKING_AREA(waThread_LCD, 128);
static WORKING_AREA(waThread_I2C, 128);


static msg_t Thread_LCD(void *p)
{
  (void)p;
  chRegSetThreadName("SerialPrint");

  while (TRUE)
  {
		int counter = 0;
		for (int i = 0; i < 29; i++){
				if (historico[counter][i] == 'u') return -1;
				chMtxLock(&mtx1);

				sdPut(&SD1, (uint8_t)0x7C);
				sdPut(&SD1, (uint8_t)0x18);
				sdPut(&SD1, (uint8_t)0x20);
				chThdSleepMilliseconds(100);

				sdPut(&SD1, (uint8_t)0x7C);
				sdPut(&SD1, (uint8_t)0x19);
				sdPut(&SD1, (uint8_t)0x20);
				chThdSleepMilliseconds(100);
				chprintf((BaseSequentialStream *)&SD1, "%c", historico[counter][i]);

				//chprintf((BaseSequentialStream *)&SD1, "%c", result);
				//chprintf((BaseSequentialStream *)&SD1, "                  ");
				chMtxUnlock();
		}
		counter++;
		if (counter > 2) counter = 0;
	}
  return 0;
}


static msg_t Thread_I2C(void *p)
{
  (void)p;
  chRegSetThreadName("SerialPrintI2C");
  uint8_t request = 0;
	uint8_t result;

  // Some time to allow slaves initialization
  chThdSleepMilliseconds(5000);

  while (TRUE)
  {
		//chprintf((BaseSequentialStream *)&SD1, "%c", 	historico[2][0]);
		//	chprintf((BaseSequentialStream *)&SD1, "%c", result);
    // Request values
		int counter = 0;

		chMtxLock(&mtx1);
		for (request = 0; request<29 ; request++){
			i2cMasterTransmitTimeout(&I2C0, slave_address, &request, 1, &result, 1, MS2ST(1000));
			historico[counter][request] = result;
			chprintf((BaseSequentialStream *)&SD1, "%c", historico[counter][request]);
			chThdSleepMilliseconds(200);
		}
		counter++;
		if (counter > 2)
			counter = 0;
    chMtxUnlock();

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
	historico[0][0] = 'u';
	historico[1][0] = 'u';
	historico[2][0] = 'u';

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
