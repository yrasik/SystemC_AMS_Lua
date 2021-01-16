dofile("lua/wav.lua")


function initialize ()
 -- reader = wav.create_context("./wave_in/zhirik_48000.wav", "r")
  reader = wav.create_context("./wave_in/Gauss_48000.wav", "r")
  print("Filename: " .. reader.get_filename())
  print("Mode: " .. reader.get_mode())
  print("File size: " .. reader.get_file_size())
  print("Channels: " .. reader.get_channels_number())
  print("Sample rate: " .. reader.get_sample_rate())
  print("Byte rate: " .. reader.get_byte_rate())
  print("Block align: " .. reader.get_block_align())
  print("Bitdepth: " .. reader.get_bits_per_sample())
  print("Samples per channel: " .. reader.get_samples_per_channel())
  print("Sample at 500ms: " .. reader.get_sample_from_ms(500))
  print("Milliseconds from 3rd sample: " .. reader.get_ms_from_sample(3))
  print(string.format("Min- & maximal amplitude: %d <-> %d", reader.get_min_max_amplitude()))
 -- reader.set_position(256)
 -- print("Sample 256, channel 2: " .. reader.get_samples(1)[2][1])

  -- Get first frequencies
  reader.set_position(0)
  print("--->")
  
end


function set_attributes ()

end


function processing( )
  local sample = reader.get_samples(1)[1]
  --print(sample[1])
  return sample[1]
end


function destructor( )

end


print("from_wave")