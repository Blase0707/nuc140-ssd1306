/**
 * SSD1306 OLED Driver Usage Example for Nuvoton NUC140
 * 
 * This file demonstrates how to use the SSD1306 driver on Nuvoton NUC140
 */

#include <stdio.h>
#include "NUC100Series.h"
#include "ssd1306_nuc140.h"
#include "fonts.h"

/* System Clock Configuration */
void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    
    /* Enable Internal RC 22.1184MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_OSC22M_EN_Msk);
    CLK_WaitClockReady(CLK_CLKSTATUS_OSC22M_STB_Msk);
    
    /* Switch HCLK clock source to Internal RC */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));
    
    /* Enable external XTAL 12MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk);
    CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk);
    
    /* Set core clock to 50MHz */
    CLK_SetCoreClock(50000000);
    
    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);
    
    /* Select UART module clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));
    
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    
    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFP = SYS_GPB_MFP_PB0_UART0_RXD | SYS_GPB_MFP_PB1_UART0_TXD;
    
    /* I2C0 pins are configured in SSD1306_I2C_Init() */
}

/* UART0 Initialization */
void UART0_Init(void)
{
    /* Reset UART0 */
    SYS_ResetModule(UART0_RST);
    
    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}

/* I2C0 IRQ Handler - MUST be implemented in your main code */
void I2C0_IRQHandler(void)
{
    /* Call SSD1306's I2C handler */
    SSD1306_I2C0_IRQHandler();
}

/* Main Function */
int main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();
    
    /* Init System, IP clock and multi-function I/O */
    SYS_Init();
    
    /* Init UART0 for printf */
    UART0_Init();
    
    /* Lock protected registers */
    SYS_LockReg();
    
    printf("\n\n");
    printf("+---------------------------------------------+\n");
    printf("|  SSD1306 OLED Display Driver for NUC140    |\n");
    printf("|  I2C0: SDA=PA8, SCL=PA9                     |\n");
    printf("+---------------------------------------------+\n");
    
    /* Initialize SSD1306 OLED */
    printf("Initializing SSD1306...\n");
    if(SSD1306_Init() == 0)
    {
        printf("ERROR: SSD1306 not found!\n");
        printf("Please check:\n");
        printf("  1. OLED connections (VCC, GND, SDA, SCL)\n");
        printf("  2. I2C address (0x78 or 0x7A)\n");
        printf("  3. Pull-up resistors on SDA and SCL\n");
        while(1);  /* Stop here if OLED not detected */
    }
    printf("SSD1306 initialized successfully!\n\n");
    
    while(1)
    {
        /* Clear screen */
        SSD1306_Fill(SSD1306_COLOR_BLACK);

        SSD1306_GotoXY(5, 0);
        SSD1306_Puts("Hello world!", &Font_7x10, SSD1306_COLOR_WHITE);
        SSD1306_DrawLine(0, 12, 128, 12, SSD1306_COLOR_WHITE);

        SSD1306_GotoXY(0, 20);
        SSD1306_Puts("This is a demo of", &Font_7x10, SSD1306_COLOR_WHITE);

        SSD1306_GotoXY(0, 35);
        SSD1306_Puts("SSD1306 display on", &Font_7x10, SSD1306_COLOR_WHITE);

        SSD1306_GotoXY(0, 50);
        SSD1306_Puts("Nu-LB-NUC140 board", &Font_7x10, SSD1306_COLOR_WHITE);
        
        /* Update display */
        SSD1306_UpdateScreen();
        
        /* Small delay */
        CLK_SysTickDelay(20000);
    }
}
