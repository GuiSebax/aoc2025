FILE = ARGV[0] || "input.txt"

def read_lines_to_list
  lines = []
  File.open(FILE, "r:utf-8") do |f|
    f.each_line do |line|
      lines << line.strip
    end
  end
  lines
end

def parse_lines(lines)
  shapes = {}
  last_shape = nil
  regions = []

  lines.each do |line|
    next if line == ""

    if line.include?("#") || line.include?(".")
      shapes[last_shape] << line.chars
    else
      split = line.split(":")
      if split[-1] == ""
        last_shape = split[0].to_i
        shapes[last_shape] = []
      else
        area = split[0].split("x").map(&:to_i)
        regions << [area, split[-1].strip.split.map(&:to_i)]
      end
    end
  end

  [shapes, regions]
end

def part_one
  lines = read_lines_to_list
  answer = 0

  _shapes, regions = parse_lines(lines)

  regions.each do |size, presents|
    width = size[0]
    height = size[1]

    total_area = width * height

    if 9 * presents.sum <= total_area
      answer += 1
    end
  end

  puts "Part 1: #{answer}"
end

def part_two
  lines = read_lines_to_list
  answer = 0
  puts "Part 2: #{answer}"
end

part_one
part_two
