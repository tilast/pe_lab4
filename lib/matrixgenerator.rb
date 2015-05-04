class MatrixGenerator
  def initialize size
    @matrix = Array.new(size) { Array.new(size, 0) }
    @vector = Array.new(size)

    fill_in
    generate_vector
  end

  def fill_in
    @matrix.each_with_index do |item, index|
      c = rand 1..100
      a = c - rand(1..c) * 2
      b = rand 1..((c - a.abs).abs)

      item[index - 1] = a unless index == 0
      item[index]     = c
      item[index + 1] = b unless index == @matrix.size - 1
    end
  end

  def generate_vector
    @vector.map! do |item|
      rand 100
    end
  end

  def write_to filename
    file = File.open(filename, 'w')

    file.puts @matrix.size

    @matrix.each do |item|
      file.puts item.join ' '
    end

    file.puts @vector.join ' '
  end
end

MatrixGenerator.new(1000).write_to './data/with_ruby_10000.dat'