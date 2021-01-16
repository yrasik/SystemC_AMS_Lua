local file
dofile("lua/wav.lua")

function initialize ()
  file = io.open("example.dat", "w")
  file:write(string.format("#TIME\tVALUE\n"))
  samples = {}
end


function set_attributes ()

end


function processing( time, in_0 )
  --file:write(string.format("%f\t%f\n",time, in_0))
    file:write(string.format("%e\t%e\n",time, in_0))
    samples[#samples + 1] = in_0 --* 32767
end


function destructor( )
  local writer = wav.create_context("out.wav", "w")
  writer.init(1, 48000, 16)
  writer.write_samples_interlaced(samples)
  writer.finish()


  file:close()
  
  file_dem = io.open("example.dem", "w")
  file_dem:write("plot 'example.dat' with lines\n")
  file_dem:write("pause -1 \"Hit return to continue\"\n")
  file_dem:close()
    
  os.execute('gnuplot "example.dem" ')
end


print("Hello World")
