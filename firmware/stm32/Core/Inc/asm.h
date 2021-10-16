/*
 * asm.h
 *
 *  Created on: Oct 15, 2021
 *      Author: jerem
 */

#ifndef INC_ASM_H_
#define INC_ASM_H_

static inline uint16_t LDREXH(volatile uint16_t* addr)
{
	uint16_t result;

	__asm__ __volatile__ ("ldrexh %0, [%1]" : "=r" (result) : "r" (addr));
	return (result);
}

static inline uint32_t STREXH(uint16_t value, volatile uint16_t* addr)
{
	uint32_t result;

	__asm__ __volatile__ ("strexh %0, %2, [%1]" : "=&r" (result) : "r" (addr), "r" (value));
	return (result);
}

#endif /* INC_ASM_H_ */
