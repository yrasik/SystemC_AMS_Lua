--[==[
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
]==]

local file
local self_name = 'Sink_Lua_00.lua'
local name = "example_00"

function initialize ()
  file = io.open(name..".dat", "w")
  if( file == nil ) then
    print('ERROR: '..self_name..': initialize:  file == nil')
    return
  end
  file:write(string.format("#TIME\tsig_from_gain\tsig_filters1_out\n"))
end


function set_attributes ()

end


function processing( time, in_00, in_01 )
    file:write(string.format("%e\t%e\t%e\n",time, in_00, in_01))
end


function destructor( )
  file:close()
  
  local pattern_gnuplot =
[====[rem=rem --[[--lua
@echo off
set PATH_TO_GNUPLOT="c:\Program Files\gnuplot\bin"
set PATH=%PATH_TO_GNUPLOT%;%PATH%
@setlocal&  set luafile="%~f0" & if exist "%~f0.bat" set luafile="%~f0.bat"
%CD%/../../../systemc/lua-5.3.5/bin/lua53  %luafile% %*& pause ]]  

local gnuplot_dem =
[[
# gnuplot script:
set xlabel "__x_label__"
set ylabel "__y_label__"
set key title "__title__"
set mytics (1) 
set grid xtics ytics mytics 

plot \
'__name__.dat' u 1:2   with lines   lw 2   title '__title_12__',\
'__name__.dat' u 1:3   with lines   lw 2   title '__title_13__'

pause -1 "Hit return to continue"
]]

file_dem = io.open("__name__.dem", "w")
file_dem:write(gnuplot_dem)
file_dem:close()

os.execute('gnuplot "__name__.dem" ')

]====]  

  local gnuplot = pattern_gnuplot:gsub('__name__', name)
  local gnuplot = gnuplot:gsub('__x_label__', 'Time, ñ')
  local gnuplot = gnuplot:gsub('__y_label__', 'Voltage, Â')
  local gnuplot = gnuplot:gsub('__title__', 'sin(x) and cos(x)')
  local gnuplot = gnuplot:gsub('__title_12__', 'sin(x)')
  local gnuplot = gnuplot:gsub('__title_13__', 'cos(x)') 
  
  file_dem = io.open(name..".bat", "w")
  file_dem:write(gnuplot)
  file_dem:close()
end

