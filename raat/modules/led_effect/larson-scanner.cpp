/* C/C++ Includes */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Module Includes */

#include "led-effect.hpp"

/* Public Member Functions */

LarsonScanner::LarsonScanner(uint8_t * dst, uint8_t n_strip_leds, uint8_t n_larson_leds) :
	mp_leds(dst), m_n_strip_leds(n_strip_leds), m_n_larson_leds(n_larson_leds),
	m_half_width(n_larson_leds/2), m_location(n_larson_leds/2), m_top(n_strip_leds - 1 - n_larson_leds/2),
	m_bottom(n_larson_leds/2)
{
	mp_values = (uint8_t*)malloc(n_larson_leds * 3);
}

#ifndef ARDUINO
void LarsonScanner::print()
{
	this->print(mp_leds);
}

void LarsonScanner::print(uint8_t * pleds)
{
	uint8_t min_index = m_location-m_half_width;
	if (min_index > 0)
	{
		min_index--;	
	}

	uint8_t max_index = m_location+m_half_width;

	if (max_index < m_n_strip_leds)
	{
		max_index++;	
	}

	this->print(pleds, min_index, max_index);
}

void LarsonScanner::print(uint8_t * pleds, uint8_t min_index, uint8_t max_index)
{
	std::cout << "LED values " << (int)min_index << "-" << (int)max_index << ":" << std::endl;
	for (uint8_t i=min_index; i<=max_index; i++)
	{
		std::cout << (int)pleds[i*3] << ","<< (int)pleds[i*3+1] << ","<< (int)pleds[i*3+2] << ",";
	}
	std::cout << std::endl;
}
#endif

void LarsonScanner::start(uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t middle_led_index = m_n_larson_leds/2;
	uint8_t divisor = (m_n_larson_leds + 1) / 2;
	divisor = divisor * divisor * divisor;
	for (uint8_t low_index=0; low_index<=middle_led_index; low_index++)
	{
		uint8_t high_index = m_n_larson_leds - low_index - 1;
		uint8_t multiplier = low_index+1;
		multiplier = multiplier * multiplier * multiplier;
		mp_values[low_index*3] = (r*multiplier)/divisor;
		mp_values[low_index*3+1] = (g*multiplier)/divisor;
		mp_values[low_index*3+2] = (b*multiplier)/divisor;

		mp_values[high_index*3] = (r*multiplier)/divisor;
		mp_values[high_index*3+1] = (g*multiplier)/divisor;
		mp_values[high_index*3+2] = (b*multiplier)/divisor;
	}
	m_direction = DIR_POS;

	uint8_t * pDst = &mp_leds[(m_location - m_half_width)*3];
	memcpy(pDst, mp_values, m_n_larson_leds*3);
}

void LarsonScanner::clear_last_pixel()
{
	uint8_t idx = 0;
	if (m_direction == DIR_POS)
	{
		idx = m_location-m_half_width;
	}
	else
	{
		idx = m_location+m_half_width;		
	}
	mp_leds[idx*3] = 0;
	mp_leds[idx*3+1] = 0;
	mp_leds[idx*3+2] = 0;
}

void LarsonScanner::set_next()
{
	if (m_direction == DIR_POS)
	{
		if (m_location < m_top)
		{
			m_location++;
		}

		if (m_location == m_top)
		{
			m_direction = DIR_NEG;
		}
	}
	else
	{
		if (m_location > m_bottom)
		{
			m_location--;
		}

		if (m_location == m_bottom)
		{
			m_direction = DIR_POS;
		}
	}
}

void LarsonScanner::update()
{
	this->clear_last_pixel();
	this->set_next();

	uint8_t * pDst = &mp_leds[(m_location - m_half_width)*3];
	memcpy(pDst, mp_values, m_n_larson_leds*3);
}
