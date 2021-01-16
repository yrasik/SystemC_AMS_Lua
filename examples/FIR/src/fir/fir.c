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


#include "fir.h"


int32_t fir_init(fir *f, const int16_t *coeffs, int16_t *signal, int32_t size, uint8_t akk_rshift)
{
  int32_t i;
  f->coeffs = coeffs;
  f->signal = signal;
  f->size = size;
  f->akk_rshift = akk_rshift;
  f->index = 0;

  for (i = 0; i < f->size; i++)
    f->signal[i] = 0;

  return 0;
}


int32_t fir_exec(fir *f, const int16_t *in, int16_t *out, int len)
{
  int32_t in_index;
  int32_t index_signal;
  int32_t i;
  int64_t akk;

  for(in_index = 0; in_index < len; in_index++)
  {
    akk = 0;
    f->signal[f->index] = in[in_index];

    for(i = 0; i < f->size; i++)
    {
      index_signal = f->index + i;
      index_signal = index_signal % (f->size);
      akk += f->coeffs[i] * f->signal[index_signal];
    }

    f->index--;
    if(f->index < 0)
    {
      f->index = (f->size - 1);
    }

    out[in_index] = akk >> f->akk_rshift;
  }

  return 0;
}
