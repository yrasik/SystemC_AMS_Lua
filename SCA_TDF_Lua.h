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
      lua_pcall(L, 0, 0, 0);
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
      lua_pcall(L, 0, N, 0);

      for (int i = 0; i < N; i++)
      {
        /* the first argument */
        out[i] = lua_tonumber(L, -(i - 1));
        lua_pop(L, 1);
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
      lua_pcall(L, 0, 0, 0);
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
      lua_pcall(L, 0, 0, 0);
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

      /* call the function with N+1 arguments, return 0 result */
      lua_pcall(L, (N + 1), 0, 0);
    }

  public:
    Sink_Lua ( sc_core::sc_module_name n, std::string script )
    {
      this->script = script;
      L = luaL_newstate();
      luaL_openlibs(L);
      luaL_dofile(L, this->script.c_str());
      lua_pcall(L, 0, 0, 0);
    }

    ~Sink_Lua ()
    {
      lua_getglobal(L, "destructor");
      lua_pcall(L, 0, 0, 0);
      lua_close(L);
    }
};


template<class T, int N, int M> SCA_TDF_MODULE ( Converter_Lua )
{
    sca_tdf::sca_in<T>  in[N];  // input
    sca_tdf::sca_out<T> out[M]; // output
  private:
    lua_State* L;
    std::string script;

    void initialize ()
    {
      /* the function name */
      lua_getglobal(L, "initialize");
      lua_pcall(L, 0, 0, 0);
    }

    void set_attributes ()
    {

    }

    void processing ()
    {
      lua_getglobal(L, "processing");

      for (int i = 0; i < N; i++)
      {
        /* the first argument */
        lua_pushnumber(L, in[i].read());
      }

     /* call the function with N arguments, return M result */
     lua_pcall(L, N, M, 0);


     for (int i = 0; i < M; i++)
     {
        /* the first argument */
        out[i] = lua_tonumber(L, -(i - 1));
        lua_pop(L, 1);
     }
    }

  public:
    Converter_Lua ( sc_core::sc_module_name n, std::string script )
    {
      this->script = script;
      L = luaL_newstate();
      luaL_openlibs(L);
      luaL_dofile(L, this->script.c_str());
      lua_pcall(L, 0, 0, 0);
    }

    ~Converter_Lua ()
    {
      lua_getglobal(L, "destructor");
      lua_pcall(L, 0, 0, 0);
      lua_close(L);
    }
};


template<class T, class N, int M> SCA_TDF_MODULE ( sca_tdf_onverter )
{
    sca_tdf::sca_in<T>  in[M];  // input
    sca_tdf::sca_out<N> out[M]; // output
  private:
    void processing ()
    {
      for (int i = 0; i < M; i++)
      {
        T din = in[i].read();
        N dout = (N)(din);
        out[i].write(dout);
      }
    }

  public:
    sca_tdf_onverter( sc_core::sc_module_name n)
    {

    }
};


template<int N> class plot_simple
{
  public:
	double axis_x;
	double axis_y[N];
  private:
    lua_State* L;
    std::string script;

  public:
    void initialize ()
    {
      /* the function name */
      lua_getglobal(L, "initialize");
      lua_pcall(L, 0, 0, 0);
    }

    void put_point()
    {
      /* the function name */
      lua_getglobal(L, "processing");
      lua_pushnumber(L, axis_x);

      for (int i = 0; i < N; i++)
      {
        /* the first argument */
        lua_pushnumber(L, axis_y[i]);
      }

      /* call the function with (N + 1) arguments, return 0 result */
      lua_pcall(L, (N + 1), 0, 0);
    }


    plot_simple (std::string script )
    {
      this->script = script;
      axis_x = 0;
      for (int i = 0; i < N; i++)
      {
        axis_y[i] = 0;
      }

      L = luaL_newstate();
      luaL_openlibs(L);
      luaL_dofile(L, this->script.c_str());
      lua_pcall(L, 0, 0, 0);
    }

    ~plot_simple ()
    {
      lua_getglobal(L, "destructor");
      lua_pcall(L, 0, 0, 0);
      lua_close(L);
    }
};


#endif /* SCA_TDF_Lua_H_ */
