maximum_args = Array.new(21697) { "arg" }
too_many_args = Array.new(21698) { "arg" }

puts `./ex10 #{maximum_args.join " "}`
puts `./ex10 #{too_many_args.join " "}`
