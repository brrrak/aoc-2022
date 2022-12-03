def main():
    infile = open("input.txt", 'r')
    lines = infile.readlines()
    result = 0

    for line in lines:
        l = len(line) // 2
        first, second = line[:l], set(line[l:])
        common = [char for char in first if char in second][0]
        result += ord(common) - 96 if common.islower() else ord(common) - 38
    
    print(f"Part 1 Answer: {result}")

    result = 0
    for i in range(len(lines) // 3):
        first, second, third = lines[i*3], set(lines[i*3+1]), set(lines[i*3+2])
        common = [char for char in first if char in second and char in third][0]
        result += ord(common) - 96 if common.islower() else ord(common) - 38
        
    print(f"Part 2 Answer: {result}")

if __name__ == '__main__':
    main()