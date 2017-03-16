/* Ejemplo de uso de los puertos paralelos en DE2
 * Este programa realiza lo siguiente:
 * 1. Visualiza el valor de los interruptores SW en los LED rojos LEDR
 * 2. Visualiza el valor de los pulsadores KEY[3..1] en los LED verdes LEDG
 * 3. Visualiza un patr�n que va girando en los displays 7-segmentos HEX
 * 4. Al pulsar los KEY[3..1], el valor de los interruptores SW se toma como patr�n
*/

#include "system.h"

int main(void)
{
	/* Declarar los punteros a registros de I/O como volatile (volatile significa que 
 	* que tanto las instrucciones de lectura como las de escritura se pueden utilizar
 	* para acceder a estas posiciones en lugar de realizar accesos a memoria
	*/
	volatile int * red_LED_ptr 	= (int *) RED_LEDS_BASE; // direcci�n LED rojos

	volatile int * green_LED_ptr = (int *) GREEN_LEDS_BASE; // direcci�n LED verdes
	volatile int * HEX3_HEX0_ptr = (int *) HEX3_HEX0_BASE; // direcci�n HEX3_HEX0
	volatile int * HEX7_HEX4_ptr = (int *) HEX7_HEX4_BASE; // direcci�n HEX7_HEX4 
	volatile int * SW_switch_ptr = (int *) SWITCHES_BASE; // direcci�n SW
	volatile int * KEY_ptr = (int *) PUSHBUTTONS_BASE; // direcci�n pulsadores KEY

	int HEX_bits = 0x0000000F; // patr�n para los display HEX
	int SW_value, KEY_value, delay_count;

	printf("Hola desde Nios II\n");

	while(1)
	{
		SW_value = *(SW_switch_ptr); // leer el valor de los interruptores SW
		*(red_LED_ptr) = SW_value; // encender los LED rojos
		KEY_value = *(KEY_ptr); // leer el valor de los pulsadores KEY
		*(green_LED_ptr) = KEY_value;// encender los LED verdes
		if (KEY_value != 0)// mirar si se ha pulsado alg�n KEY
		{
			HEX_bits = SW_value;// establecer el patr�n con el valor de SW
			while (*KEY_ptr);// esperar a que se vuelva a pulsar alg�n KEY
		}
		*(HEX3_HEX0_ptr) = HEX_bits;// visualizar patr�n en HEX3 ... HEX0
		*(HEX7_HEX4_ptr) = HEX_bits;// visualizar patr�n en HEX7 ... HEX4

		/* girar el patr�n mostrado en los displays HEX */
		if (HEX_bits & 0x80000000)
			HEX_bits = (HEX_bits << 1) | 1;
		else
			HEX_bits = HEX_bits << 1;

		for (delay_count = 100000; delay_count != 0; --delay_count); //retardo
	}
}
