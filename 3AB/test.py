import subprocess

def find_min_total_cycles(cacheSizewidth):
    min_config = (0, 0, 0, 'write-allocate', 'write-back', 'lru')
    min_cycles = 1e20
    for numsets in range(0, cacheSizewidth-1):
        for numblocks in range(0, cacheSizewidth - numsets - 1):
            cacheSize = 2 ** cacheSizewidth
            pownumsets = 2 ** numsets
            pownumblocks = 2 ** numblocks
            pownumbytes = 2 ** (cacheSizewidth - numsets - numblocks)
            s = ' ' + str(pownumsets) + ' ' + str(pownumblocks) + ' ' + str(pownumbytes) + ' '
            commands = [
            "./cacheSim" + s + "write-allocate write-back lru < gcc.trace",
            "./cacheSim" + s + "write-allocate write-back fifo < gcc.trace",
            "./cacheSim" + s + "write-allocate write-through lru < gcc.trace",
            "./cacheSim" + s + "write-allocate write-through fifo < gcc.trace",
            "./cacheSim" + s + "no-write-allocate write-back lru < gcc.trace",
            "./cacheSim" + s + "no-write-allocate write-back fifo < gcc.trace",
            "./cacheSim" + s + "no-write-allocate write-through lru < gcc.trace",
            "./cacheSim" + s + "no-write-allocate write-through fifo < gcc.trace"
            ]
            # print(commands)
            for command in commands:
                process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                stdout, stderr = process.communicate()
                if(stdout.decode()):
                    # print(stdout.decode())
                    cycles = int(stdout.decode())
                    if cycles < min_cycles:
                        min_cycles = cycles
                        min_config = (pownumsets, pownumblocks, pownumbytes, command.split()[4], command.split()[5], command.split()[6])
            # "./cacheSim 256 4 16 write-allocate write-back fifo < gcc.trace",
            # "./cacheSim 256 4 16 write-allocate write-through lru < gcc.trace",
            # "./cacheSim 256 4 16 write-allocate write-through fifo < gcc.trace",
            # "./cacheSim 256 4 16 no-write-allocate write-back lru < gcc.trace",
            # "./cacheSim 256 4 16 no-write-allocate write-back fifo < gcc.trace",
            # "./cacheSim 256 4 16 no-write-allocate write-through lru < gcc.trace",
            # "./cacheSim 256 4 16 no-write-allocate write-through fifo < gcc.trace"
            # ]
    return min_config, min_cycles

def find_min_miss_rate(cacheSizewidth):
    min_config = (1, 2**(cacheSizewidth-2), 4, 'write-allocate', 'write-back', 'lru')
    min_miss_rate = 100
    s = ' ' + str(1) + ' ' + str(2**(cacheSizewidth-2)) + ' ' + str(4) + ' '
    commands = [
    "./cacheSim" + s + "write-allocate write-back lru < gcc.trace",
    "./cacheSim" + s + "write-allocate write-back fifo < gcc.trace",
    "./cacheSim" + s + "write-allocate write-through lru < gcc.trace",
    "./cacheSim" + s + "write-allocate write-through fifo < gcc.trace",
    "./cacheSim" + s + "no-write-allocate write-back lru < gcc.trace",
    "./cacheSim" + s + "no-write-allocate write-back fifo < gcc.trace",
    "./cacheSim" + s + "no-write-allocate write-through lru < gcc.trace",
    "./cacheSim" + s + "no-write-allocate write-through fifo < gcc.trace"
    ]
    # print(commands)
    for command in commands:
        process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        if(stdout.decode()):
            # print(stdout.decode())
            miss_rate = float(stdout.decode().split()[1])/float(stdout.decode().split()[0])
            if miss_rate < min_miss_rate:
                min_miss_rate = miss_rate
                min_config = (1, 2**(cacheSizewidth-2), 4, command.split()[4], command.split()[5], command.split()[6])
            # "./cacheSim 256 4 16 write-allocate write-back fifo < gcc.trace",
            # "./cacheSim 256 4 16 write-allocate write-through lru < gcc.trace",
            # "./cacheSim 256 4 16 write-
    return min_config, min_miss_rate

# print(find_min_total_cycles(5))
print(find_min_miss_rate(2))
print(find_min_miss_rate(5))
print(find_min_miss_rate(8))
print(find_min_miss_rate(11))
print(find_min_miss_rate(14))
# find_min_total_cycles(4)