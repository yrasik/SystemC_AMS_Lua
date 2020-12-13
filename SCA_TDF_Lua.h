/*
 * This file is part of the XXX distribution (https://github.com/yrasik/SystemC_AMS_Lua).
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

#ifndef SCA_TDF_Lua_H_
#define SCA_TDF_Lua_H_

#include <string>
#include <systemc-ams.h>

#include "lua.hpp"

using namespace sca_tdf;


template<class T, int N> SCA_TDF_MODULE ( Source_Lua )
{
    sca_tdf::sca_out<T>  out[N];  // output
  private:
    lua_State* L;
    std::string script;
    int    rate;
    double tstep;
    sc_core::sc_time_unit unit;

    void initialize ()
    {
      /* the function name */
      lua_getglobal(L, "initialize");
  	  lua_call(L, 0, 0);
    }

    void set_attributes ()
    {
      // set data rate of output ports
      for (int i = 0; i < N; i++)
      {
    	/* the first argument */
        out[i].set_rate( rate );
        out[i].set_timestep( tstep, unit ); //8 kGz (125 uS)
      }
    }

    void processing ()
    {
  	  /* the function name */
  	  lua_getglobal(L, "processing");

  	  /* call the function with N arguments, return 0 result */
  	  lua_call(L, 0, N);

      for (int i = 0; i < N; i++)
      {
    	/* the first argument */
      	out[i] = lua_tonumber(L, (i + 1));
      }

    }

  public:
    Source_Lua ( sc_core::sc_module_name n, std::string script, int rate = 1, double tstep = 0.01, sc_core::sc_time_unit unit = SC_US )
    {
      this->script = script;
      this->rate = rate;
      this->tstep = tstep;
      this->unit = unit;

      L = luaL_newstate();
      luaL_openlibs(L);
      luaL_dofile(L, this->script.c_str());
      lua_pcall(L, 0, 0, 0);
    }

    ~Source_Lua ()
    {
      lua_getglobal(L, "destructor");
  	  lua_call(L, 0, 0);
  	  lua_close(L);
    }
};


template<class T, int N> SCA_TDF_MODULE ( Sink_Lua )
{
    sca_tdf::sca_in<T>  in[N];  // input
  private:
    lua_State* L;
    std::string script;

    void initialize ()
    {
      /* the function name */
      lua_getglobal(L, "initialize");
  	  lua_call(L, 0, 0);
    }

    void set_attributes ()
    {

    }

    void processing ()
    {
  	  /* the function name */
  	  lua_getglobal(L, "processing");

      lua_pushnumber(L, in[0].get_time().to_seconds());

      for (int i = 0; i < N; i++)
      {
    	/* the first argument */
      	lua_pushnumber(L, in[i].read());
      }

  	  /* call the function with N arguments, return 0 result */
  	  lua_call(L, (N + 1), 0);
    }

  public:
    Sink_Lua ( sc_core::sc_module_name n, std::string script )
    {
      L = luaL_newstate();
      luaL_openlibs(L);
      luaL_dofile(L, script.c_str());
      lua_pcall(L, 0, 0, 0);
    }

    ~Sink_Lua ()
    {
      lua_getglobal(L, "destructor");
  	  lua_call(L, 0, 0);
  	  lua_close(L);
    }
};






#if 0

template<class T, int N> SCA_TDF_MODULE ( Lua )
{
    sca_tdf::sca_in<T>  in[N];  // input
   // sca_tdf::sca_out<T> out[M]; // output
  private:
    lua_State* L;


    void initialize ()
    {
      /* the function name */
      lua_getglobal(L, "initialize");

  	  lua_call(L, 0, 0);

    }

    void set_attributes ()
    {

    }

    void processing ()
    {
      double in_0 = in[0].read();

  	  /* the function name */
  	  lua_getglobal(L, "processing");

  	  /* the first argument */
  	  lua_pushnumber(L, in_0);

  	  /* call the function with 2 arguments, return 1 result */
  	  //lua_call(L, 2, 1);
  	  lua_call(L, 1, 0);

  	  /* get the result */
  	  //sum = (int)lua_tointeger(L, -1);
  	  //lua_pop(L, 1);

    }
    
  public:
    Lua ( sc_core::sc_module_name n, char *script )
    {
      L = luaL_newstate();
      luaL_openlibs(L);
      luaL_dofile(L, script);
      lua_pcall(L, 0, 0, 0);
    }
};
#endif



#endif /* SCA_TDF_Lua_H_ */
