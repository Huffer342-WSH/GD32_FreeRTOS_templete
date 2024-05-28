#include "gd32f3x0.h"

void BSP_TimeBase_Init(void)
{
	timer_parameter_struct timer_initpara = { .alignedmode = TIMER_COUNTER_EDGE,
						  .counterdirection = TIMER_COUNTER_UP,
						  .period = 99,
						  .clockdivision = TIMER_CKDIV_DIV1,
						  .repetitioncounter = 0

	};

	/* enable the peripherals clock */
	rcu_periph_clock_enable(RCU_TIMER13);

	/* deinit a TIMER */
	rcu_periph_reset_enable(RCU_TIMER13RST);
	rcu_periph_reset_disable(RCU_TIMER13RST);

	/* TIMER13 configuration */

	timer_initpara.prescaler = SystemCoreClock / 1000 - 1;

	timer_init(TIMER13, &timer_initpara);

	/* clear channel 0 interrupt bit */
	timer_interrupt_flag_clear(TIMER13, TIMER_INT_FLAG_UP);
	/* enable the TIMER interrupt */
	timer_interrupt_enable(TIMER13, TIMER_INT_UP);
	/* enable a TIMER */
	timer_enable(TIMER13);

	nvic_irq_enable(TIMER13_IRQn, 0, 0);
}
