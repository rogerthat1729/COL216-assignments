import subprocess

# List of commands to run. You can add more commands here.
commands = [
    "./cacheSim 256 4 16 write-allocate write-back lru < gcc.trace",
    "./cacheSim 256 4 16 write-allocate write-back fifo < gcc.trace",
    "./cacheSim 256 4 16 write-allocate write-through lru < gcc.trace",
    "./cacheSim 256 4 16 write-allocate write-through fifo < gcc.trace",
    "./cacheSim 256 4 16 no-write-allocate write-back lru < gcc.trace",
    "./cacheSim 256 4 16 no-write-allocate write-back fifo < gcc.trace",
    "./cacheSim 256 4 16 no-write-allocate write-through lru < gcc.trace",
    "./cacheSim 256 4 16 no-write-allocate write-through fifo < gcc.trace"
]

text = ""

# Run each command
for command in commands:
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    # Output the results
    text += command + "\n" + stdout.decode() + "\n"
    
f = open("output.txt", "w")
f.write(text)
f.close()

