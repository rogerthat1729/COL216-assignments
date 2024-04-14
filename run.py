import subprocess

# Path to the compiled C++ executable
executable = "./cacheSim"

# List of commands to run. You can add more commands here.
commands = [
    "./cacheSim 8 16 32 no-write-allocate write-back lru < testgen.txt",
    "./cacheSim 8 16 32 no-write-allocate write-back fifo < testgen.txt ",
    "./cacheSim 8 16 32 no-write-allocate write-through lru < testgen.txt",
    "./cacheSim 8 16 32 no-write-allocate write-through fifo < testgen.txt",
    "./cacheSim 16 4 8 write-allocate write-back lru < testgen.txt",
    "./cacheSim 16 4 8 write-allocate write-back fifo < testgen.txt",
    "./cacheSim 16 4 8 write-allocate write-through lru < testgen.txt",
    "./cacheSim 16 4 8 write-allocate write-through fifo < testgen.txt"
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

