# LED Toggle Using Register-Level Programming (STM32)

This project toggles an onboard LED connected to **GPIOA Pin 5** of an STM32 microcontroller by directly accessing memory-mapped registers using macros. It avoids using HAL or CMSIS libraries and focuses purely on register-level embedded C.

---

## 🔧 GPIO Configuration Details

- **LED Connection:**
  - **Port:** GPIOA
  - **Pin:** 5

---

## 📦 Memory Region Macros Explained

### `#define PERIPH_BASE (0x40000000UL)`
- **Purpose:** Starting base address for peripheral registers in STM32.
- **UL:** Stands for *Unsigned Long* to ensure it's treated as a 32-bit constant.

### `#define AHB1PERIPH_OFFSET (0x00020000)`
- **Purpose:** Offset to AHB1 peripheral block from `PERIPH_BASE`.

### `#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)`
- **Usage:** Base address for AHB1 peripherals like GPIO, RCC, etc.

---

## 🧩 Peripheral Base Addresses

### `#define GPIOA_OFFSET (0x0000)`
- **GPIOA offset** from AHB1 base.

### `#define GPIOA_BASE (AHB1PERIPH_BASE + GPIOA_OFFSET)`
- **Usage:** Base address for GPIOA registers.

### `#define RCC_OFFSET (0x3800)`
- **RCC (Reset and Clock Control) offset** from AHB1 base.

### `#define RCC_BASE (AHB1PERIPH_BASE + RCC_OFFSET)`
- Base address for RCC control registers.

---

## 🔌 RCC and GPIO Control Macros

### `#define RCC_AHB1ENR_OFFSET (0x30UL)`
- Offset of the **AHB1 peripheral clock enable register**.

### `#define RCC_AHB1ENR_BASE (*(volatile unsigned int *)(RCC_BASE + RCC_AHB1ENR_OFFSET))`
- Points to RCC register enabling AHB1 clocks (like GPIOA).

### `#define GPIOA_MODE_R (*(volatile unsigned int *)(GPIOA_BASE + 0x00))`
- Points to GPIOA’s **mode register** (MODER).

---

## 💡 Output Data Register

### `#define ODR_OFFSET (0x14)`
- Offset of **Output Data Register (ODR)** in GPIO.

### `#define ODR_BASE (*(volatile unsigned int *)(GPIOA_BASE + ODR_OFFSET))`
- Used to **set or clear GPIO output pins** like PA5.

---

## 📍 Pin-Level Macros

### `#define GPIOAEN (1U << 0)`
- Enables GPIOA clock in RCC register.

### `#define PIN5_H (1U << 5)`
- Bitmask for **setting** Pin 5 of GPIOA.

### `#define PIN5_L (~(1U << 5))`
- Bitmask for **clearing** Pin 5 of GPIOA.

---

## ⏲️ Delay Function

```c
void delay(volatile unsigned int time)
```
- A simple software delay using nested loops.
- Not accurate for real-time use.

---

## 📌 Summary

This project demonstrates:
- Enabling GPIOA via RCC.
- Setting PA5 as output.
- Writing `1` and `0` to PA5 using ODR for LED on/off.
- Using only low-level register macros without any libraries.
