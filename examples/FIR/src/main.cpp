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


#include <stdio.h>
#include <systemc-ams.h>

#include "SCA_TDF_Lua.h"
#include "SCA_TDF_Module__FIR.h"


const int16_t B[55] = {
  2785,  -1584,  -1470,  -1444,  -1392,  -1227,   -915,   -457,     79,
   599,    999,   1175,   1064,    653,      1,   -776,  -1513,  -2022,
 -2131,  -1713,   -718,    811,   2739,   4852,   6888,   8582,   9703,
 10095,   9703,   8582,   6888,   4852,   2739,    811,   -718,  -1713,
 -2131,  -2022,  -1513,   -776,      1,    653,   1064,   1175,    999,
   599,     79,   -457,   -915,  -1227,  -1392,  -1444,  -1470,  -1584,
  2785
};

#define FIR_ORDER  ((int)(sizeof(B)/sizeof(int16_t)))



int sc_main ( int argc, char *argv[] )
{
  sca_signal<double>  node_01;
  sca_signal<double>  node_02;

  Source_Lua<double, 1> Source("Source", "./from_wave.lua", 1, 20.8333/*(1/48000)*/, SC_US );
  Source.out[0](node_01);

  FIR_Filter_to_mcu FIR("FIR", B, FIR_ORDER, 1, 16);
  FIR.in(node_01);
  FIR.out(node_02);

  Sink_Lua<double, 1> Sink_01("Sink_01", "./to_wave_and_table.lua");
  Sink_01.in[0](node_02);

  sc_start(30000, SC_MS);

  return 0;
}

