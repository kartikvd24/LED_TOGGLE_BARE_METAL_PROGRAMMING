# 🔦 LED Toggle Using Register Addresses on STM32 (Bare-Metal)

This project demonstrates how to toggle an LED connected to **Pin A5** on an STM32 microcontroller using direct memory access (register-level programming) in Embedded C.

---

## 🧠 Code Overview

```c
#define PERIPH_BASE (0x40000000UL) // Base address for all peripherals (UL: Unsigned Long)
#define AHB1PERIPH_OFFSET (0x00020000)
#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)
PERIPH_BASE: The base memory address of peripheral registers in STM32.

AHB1PERIPH_OFFSET: Offset to reach AHB1 peripheral space.

AHB1PERIPH_BASE: Final base address of AHB1 peripheral registers.

c
Copy
Edit
#define GPIOA_OFFSET (0x0000)
#define GPIOA_BASE (AHB1PERIPH_BASE + GPIOA_OFFSET)
GPIOA has no offset in AHB1, so it starts at AHB1 base.

c
Copy
Edit
#define RCC_OFFSET (0x3800)
#define RCC_BASE (AHB1PERIPH_BASE + RCC_OFFSET)
RCC (Reset and Clock Control) base register.

c
Copy
Edit
#define RCC_AHB1ENR_OFFSET (0x30UL)
#define RCC_AHB1ENR_BASE (*(volatile unsigned int *)(RCC_BASE + RCC_AHB1ENR_OFFSET))
RCC_AHB1ENR enables clocks for AHB1 peripherals. We modify this register to enable GPIOA.

c
Copy
Edit
#define MODE_R_OFFSET (0x00UL)
#define GPIOA_MODE_R (*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))
GPIOA_MODE_R is the register to configure pin mode (input, output, etc.).

c
Copy
Edit
#define ODR_OFFSET (0x14)
#define ODR_BASE (*(volatile unsigned int *)(GPIOA_BASE + ODR_OFFSET))
ODR is the Output Data Register. It controls the output state of the pins.

c
Copy
Edit
#define GPIOAEN (1U << 0) // Bit 0 controls clock for GPIOA
#define PIN5_H (1U << 5)  // Bit 5 high (set PA5)
#define PIN5_L ~(1U << 5) // Bit 5 low (clear PA5)
#define LED_PIN_H PIN5_H
#define LED_PIN_L PIN5_L
⏱️ Delay Function
c
Copy
Edit
void delay(volatile unsigned int time) {
    while (time--) {
        for (volatile int i = 0; i < 1000; i++) {
            // Waste time (not accurate)
        }
    }
}
Basic software delay loop. Not very precise but useful for simple tasks.

🔁 Main Function
c
Copy
Edit
int main(void) {
    // 1. Enable clock access to GPIOA
    RCC_AHB1ENR_BASE |= GPIOAEN;

    // 2. Set PA5 as output
    GPIOA_MODE_R |= (1U << 10);  // Set bit 10
    GPIOA_MODE_R &= ~(1U << 11); // Clear bit 11

    while (1) {
        ODR_BASE |= LED_PIN_H;  // Turn LED ON (PA5 HIGH)
        delay(5000);
        ODR_BASE &= LED_PIN_L;  // Turn LED OFF (PA5 LOW)
        delay(5000);
    }
}
📌 Hardware Setup
MCU: STM32 (e.g., STM32F401, STM32F103, etc.)

LED Connection:

Port: GPIOA

Pin: PA5

Circuit: Connect an LED in series with a resistor to PA5 and GND.

⚠️ Notes
This is bare-metal C code — no HAL or CMSIS used.

Ensure correct startup and linker files for the target STM32 board.

This example is good for learning low-level MCU programming and register access.

📘 License
This project is open-source and free to use under the MIT License.

yaml
Copy
Edit

---

Let me know if you want:
- A diagram or register map,
- HAL-based version for comparison,
- Or an actual `.zip` file to download.
