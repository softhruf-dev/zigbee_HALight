/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : pin_mux.c
**     Project     : mrbkw01
**     Processor   : MKW01Z128CHN4
**     Component   : PinSettings
**     Version     : Component 01.002, Driver 1.1, CPU db: 3.00.000
**     Compiler    : IAR ARM C Compiler
**     Date/Time   : 2013-12-10, 14:58, # CodeGen: 7
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         GPIO                - void pin_mux_GPIO(uint32_t instance);
**         I2C                 - void pin_mux_I2C(uint32_t instance);
**         RTC                 - void pin_mux_RTC(uint32_t instance);
**         SPI                 - void pin_mux_SPI(uint32_t instance);
**         UART                - void pin_mux_UART(uint32_t instance);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file pin_mux.c
** @version 1.1
** @brief
**
*/
/*!
**  @addtogroup pin_mux_module pin_mux module documentation
**  @{
*/

/* MODULE pin_mux. */

#include "fsl_device_registers.h"
#include "fsl_port_hal.h"
#include "fsl_sim_hal.h"
#include "fsl_gpio_hal.h"
#include "pin_mux.h"

void configure_gpio_pins(uint32_t instance)
{
  switch(instance) {    
    case 0:
      /* SW1 */
      PORT_HAL_SetMuxMode(PORTA, 4u, kPortMuxAsGpio);
	  /* LED1 */
      PORT_HAL_SetMuxMode(PORTA, 19u, kPortMuxAsGpio);
      break;
    case 1:
      /* LED3 */
      PORT_HAL_SetMuxMode(PORTB, 0u, kPortMuxAsGpio);
      break;
    case 2: 
      break;
	case 3:
      /* SW2 */
      PORT_HAL_SetMuxMode(PORTD, 5u, kPortMuxAsGpio);
      /* SW3 */
      PORT_HAL_SetMuxMode(PORTD, 6u, kPortMuxAsGpio);  
      /* SW4 */
      PORT_HAL_SetMuxMode(PORTD, 7u, kPortMuxAsGpio);   
	  break;
    case 4:						
	  /* LED2 */
      PORT_HAL_SetMuxMode(PORTE, 16u, kPortMuxAsGpio);	
	  /* LED4 */
      PORT_HAL_SetMuxMode(PORTE, 17u, kPortMuxAsGpio);	  
      break;	
    default:
      break;
  }
}

void configure_spi_pins(uint32_t instance)
{
  switch(instance) {    
    case 0:       
      /* SPI0 CS */
      PORT_HAL_SetMuxMode(PORTD, 0u, kPortMuxAsGpio);
      GPIO_HAL_SetPinDir(GPIOD, 0u, kGpioDigitalOutput);
      /* SPI0 CLK */
      PORT_HAL_SetMuxMode(PORTC, 5u, kPortMuxAlt2);
      /* SPI0 MOSI */
      PORT_HAL_SetMuxMode(PORTC, 6u, kPortMuxAlt2);
      /* SPI0 MISO */
      PORT_HAL_SetMuxMode(PORTC, 7u, kPortMuxAlt2);
      break;
    default:
      break;
  }
}

void configure_uart_pins(uint32_t instance)
{
}

void configure_lpsci_pins(uint32_t instance)
{
  switch(instance) {    
    case 0:
      /* UART0 RX */
      PORT_HAL_SetMuxMode(PORTA, 1u, kPortMuxAlt2);
      /* UART0 TX */
      PORT_HAL_SetMuxMode(PORTA, 2u, kPortMuxAlt2);

      /* UART0 RX */
      //PORT_HAL_SetMuxMode(PORTD, 6u, kPortMuxAlt3);
      /* UART0 TX */
      //PORT_HAL_SetMuxMode(PORTD, 7u, kPortMuxAlt3);      
      break;
    default:
      break;
  }
}

/* Setup SPI pins to communicate with wireless modem */
void configure_spi_pins_for_modem(uint32_t instance)
{
  switch(instance) {
    case 0:                          /* SPI0 */
      /* PORTE_PCR19 */
      PORT_HAL_SetMuxMode(PORTC,6u,kPortMuxAlt2); /* MISO */
      /* PORTE_PCR18 */
      PORT_HAL_SetMuxMode(PORTC,7u,kPortMuxAlt2); /* MOSI */
      /* PORTE_PCR17 */
      PORT_HAL_SetMuxMode(PORTC,5u,kPortMuxAlt2); /* SCK */
      /* PORTE_PCR16 */
      PORT_HAL_SetMuxMode(PORTD,0u,kPortMuxAlt2); /* PCS0 */
      break;
    default:
      break;
  }
}

void configure_xcvr_pins(void)
{ 
  /* XCVR DIO0 */
  PORT_HAL_SetMuxMode(PORTC, 4u, kPortMuxAsGpio);
  GPIO_HAL_SetPinDir(GPIOC, 4u, kGpioDigitalInput);
        
  /* XCVR DIO1 */
  PORT_HAL_SetMuxMode(PORTC, 3u, kPortMuxAsGpio);
  GPIO_HAL_SetPinDir(GPIOC, 3u, kGpioDigitalInput);
  
  /* XCVR DIO4 */
  PORT_HAL_SetMuxMode(PORTD, 4u, kPortMuxAsGpio);
  GPIO_HAL_SetPinDir(GPIOD, 4u, kGpioDigitalInput);
  
  /* XCVR CLKIN */
  PORT_HAL_SetMuxMode(PORTA, 18u, kPortMuxAsGpio);
  GPIO_HAL_SetPinDir(GPIOA, 18u, kGpioDigitalInput);

  /* XCVR RESET */
  PORT_HAL_SetMuxMode(PORTE, 30u, kPortMuxAsGpio);
  GPIO_HAL_SetPinDir(GPIOE, 30u, kGpioDigitalOutput);    
}

/* END pin_mux. */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
