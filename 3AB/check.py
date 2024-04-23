def compare_files(file1_path, file2_path):
    # Open both files and read the lines
    with open(file1_path, 'r') as file1, open(file2_path, 'r') as file2:
        file1_lines = file1.readlines()
        file2_lines = file2.readlines()

    # Check the length of files
    max_length = max(len(file1_lines), len(file2_lines))
    differences = []

    # Compare each line
    for i in range(max_length):
        # Check if line exists in both files
        line1 = file1_lines[i].strip() if i < len(file1_lines) else ''
        line2 = file2_lines[i].strip() if i < len(file2_lines) else ''
        
        # If lines are different, note the line number
        if line1 != line2:
            differences.append(i + 1)  # +1 to make line number human-readable

    # Output results
    if not differences:
        print("The files are identical.")
    else:
        print("The files are different.")
        print("Differences found at line numbers:", differences)

# Example usage
compare_files('output.txt', 'output1.txt')
