/*
 * This file is part of the "SystemC AMS Lua" distribution (https://github.com/yrasik/SystemC_AMS_Lua).
 * Copyright (c) 2020 Yuri Stepanenko.
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

#ifndef SCA_TDF_MODULE__FIR_H
#define SCA_TDF_MODULE__FIR_H

#include <systemc-ams.h>
#include <stdint.h>

#include "fir/fir.h"


SCA_TDF_MODULE ( FIR_Filter_to_mcu )
{
  sca_tdf::sca_in<double>  in;
  sca_tdf::sca_out<double> out;

  FIR_Filter_to_mcu (sc_module_name nm, const int16_t *coeffs, int size, double prev_mul = 1, uint8_t akk_rshift = 0, int rate = 1)
  {
    this->rate = rate;
    this->coeff = coeff;
    this->prev_mul = prev_mul;
    this->Buf_size = size;
    i = 0;
    cout << name () << " FIR_Filter "  << endl;

    signal_in = new int16_t[this->Buf_size];
    signal_out = new int16_t[this->Buf_size];

    std::memset(signal_in, 0, ((this->Buf_size)*sizeof(int16_t)) );
    std::memset(signal_out, 0, ((this->Buf_size)*sizeof(int16_t)) );

    signal = new int16_t[size];
    if(signal == NULL)
    {
      cout << name () << " ERROR: if(signal == NULL) "  << endl;
    }

    fir_init(&Fir, coeffs, signal, size, akk_rshift);
  }

  ~FIR_Filter_to_mcu()
  {
    delete signal_in;
    delete signal_out;
    delete signal;
  }

  void set_attributes ()
  {
    out.set_rate( rate );
  }

  //reads a new value from the wave file and writes it to the channel
  void processing ()
  {
    signal_in[i] = (int16_t)(in.read() * prev_mul);
    out.write((double)(signal_out[i]));

    i++;
    if(i < Buf_size)
    {

    }
    else
    {
      fir_exec(&Fir, signal_in, signal_out, Buf_size);
      i = 0;
    }
  }

private:
  int rate;
  int Buf_size;
  const int16_t *coeff;
  int16_t *signal_in;
  int16_t *signal_out;
  int i;
  double prev_mul;

  fir Fir;
  int16_t *signal;
};


#endif //SCA_TDF_MODULE__FIR_H
