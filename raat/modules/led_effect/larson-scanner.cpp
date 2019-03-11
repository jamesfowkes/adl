/* C/C++ Includes */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Module Includes */

#include "led-effect.hpp"

#include <iostream>

/* Public Member Functions */

LarsonScanner::LarsonScanner(uint8_t * dst, uint8_t n_strip_leds, uint8_t n_larson_leds) :
	mp_leds(dst), m_n_strip_leds(n_strip_leds), m_n_larson_leds(n_larson_leds),
	m_half_width(n_larson_leds/2), m_middle(n_larson_leds/2), m_top(n_strip_leds - n_larson_leds/2),
	m_bottom(n_larson_leds/2)
{
	mp_values = (uint8_t*)malloc(n_larson_leds * 3);
}

void LarsonScanner::print(uint8_t * p, uint8_t n)
{
	for (uint8_t i=0; i< n*3; i++)
	{
		std::cout << (int)p[i] << ",";
	}
	std::cout << std::endl;
}

void LarsonScanner::start(uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t middle_led_index = m_n_larson_leds/2;
	uint8_t divisor = (m_n_larson_leds + 1) / 2;
	for (uint8_t low_index=0; low_index<=middle_led_index; low_index++)
	{
		uint8_t high_index = m_n_larson_leds - low_index - 1;
		uint8_t multiplier = low_index+1;
		mp_values[low_index*3] = (r*multiplier)/divisor;
		mp_values[low_index*3+1] = (g*multiplier)/divisor;
		mp_values[low_index*3+2] = (b*multiplier)/divisor;

		mp_values[high_index*3] = (r*multiplier)/divisor;
		mp_values[high_index*3+1] = (g*multiplier)/divisor;
		mp_values[high_index*3+2] = (b*multiplier)/divisor;
	}
	for (uint8_t i=0; i< m_n_larson_leds*3; i++)
	{
		std::cout << (int)mp_values[i] << ",";
	}
	std::cout << std::endl;
}

void LarsonScanner::clear_previous_pixel()
{
	uint8_t idx = 0;
	if (m_direction == DIR_POS)
	{
		idx = m_middle-m_half_width;
	}
	else
	{
		idx = m_middle+m_half_width;		
	}
	mp_leds[idx*3] = 0;
	mp_leds[idx*3+1] = 0;
	mp_leds[idx*3+2] = 0;
}

void LarsonScanner::set_next()
{
	if (m_direction == DIR_POS)
	{
		if (m_middle < m_top)
		{
			m_middle++;
		}

		if (m_middle == m_top)
		{
			m_direction = DIR_NEG;
		}
	}
	else
	{
		if (m_middle > m_bottom)
		{
			m_middle--;
		}

		if (m_middle == m_bottom)
		{
			m_direction = DIR_POS;
		}
	}
}

void LarsonScanner::update()
{
	this->clear_previous_pixel();

	uint8_t * pSrc = &mp_values[m_middle - m_half_width];

	memcpy(mp_leds, pSrc, m_n_larson_leds*3);

	this->print(mp_leds, 5);

	this->set_next();
}
