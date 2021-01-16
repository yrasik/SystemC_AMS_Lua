/*
 * This file is part of the "SystemC AMS Lua" distribution (https://github.com/yrasik/SystemC_AMS_Lua).
 * Copyright (c) 2021 Yuri Stepanenko.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _FIR_H_
#define _FIR_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

typedef struct
{
  const int16_t *coeffs;
  int16_t *signal;
  int32_t size;
  int32_t index;
  uint8_t akk_rshift;
} fir;

int32_t fir_init(fir *f, const int16_t *coeffs, int16_t *signal, int32_t size, uint8_t akk_rshift);
int32_t fir_exec(fir *f, const int16_t *in, int16_t *out, int len);


#ifdef __cplusplus
}
#endif

#endif /*_FIR_H_*/
