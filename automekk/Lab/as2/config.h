#ifndef CONFIG_H
#define CONFIG_H

#define F_CPU 4000000UL

#define B_RATE(BAUD) ((64 * F_CPU) / (16 * (float)baud)+0.5)

#endif // CONFIG_H

