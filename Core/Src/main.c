//WHERE IS THE LED CONNECTED?
//PORT:A
//PIN:5
#define PERIPH_BASE (0X40000000UL)//UL is unsigned link

#define AHB1PERIPH_OFFSET (0X00020000)
#define AHB1PERIPH_BASE (PERIPH_BASE+AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET (0X0000) //0's doesnt matter coz it will take 8 o's
#define GPIOA_BASE (AHB1PERIPH_BASE+GPIOA_OFFSET)



#define RCC_OFFSET (0X3800)
#define RCC_BASE (AHB1PERIPH_BASE+RCC_OFFSET)

#define RCC_AHB1ENR_OFFSET (0x30UL)
#define RCC_AHB1ENR_BASE (*(volatile unsigned int *)(RCC_BASE+RCC_AHB1ENR_OFFSET))


#define MODE_R_OFFSET (0X00UL)
#define GPIOA_MODE_R *(volatile unsigned int *)(GPIOA_BASE+MODE_R_OFFSET)


#define ODR_OFFSET (0x14)//OUTPUT DATA REGISTER
#define ODR_BASE *(volatile unsigned int *)(GPIOA_BASE+ODR_OFFSET)

#define GPIOAEN (1U<<0)//shift 1 to position 0 ie 0x 0000 0001

#define PIN5_H (1U<<5)
#define LED_PIN_H PIN5_H
#define PIN5_L ~(1U<<5)
#define LED_PIN_L PIN5_L


/*
 * (1U<<10) // set bit 10 to 1
 * &=~(1U<<11)//ANDing the value in the 11 bit we get proper value
 * */
//this can be used for simpler projects
void delay(volatile unsigned int time) {
    while (time--) {
        for (volatile int i = 0; i < 1000; i++) {
            // just waste time
        }
    }
}


int main(void){
	/*
	 * 1.Enable clock access to GPIOA*/
RCC_AHB1ENR_BASE |=GPIOAEN ;
	 /* 2.Set PA5 as output high */
GPIOA_MODE_R  |=(1U<<10);
GPIOA_MODE_R &=~(1U<<11);

while(1){
	//set pa5 high
	ODR_BASE |=LED_PIN_H;
	delay(5000);
	ODR_BASE &=LED_PIN_L;
	delay(5000);
}
}


