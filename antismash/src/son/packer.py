with open('shellcode.h', 'r') as f:
    shellcode_lines = f.readlines()

# Find the line that declares the array son_asm[]
start_index = None
end_index = None
for i, line in enumerate(shellcode_lines):
    if 'son_bin[]' in line:
        start_index = i
    elif start_index is not None and '};' in line:
        end_index = i
        break

# Extract the lines containing the array code_bin[]
code_lines = shellcode_lines[start_index:end_index]

# Extract hex values from the array lines
code_hex_values = []
for line in code_lines:
    values = line.strip().split(',')
    for value in values:
        if '0x' in value:
            code_hex_values.append(int(value.strip(), 16))

# Perform XOR operations only on values
def genkey(curr):
    return (25 * curr + 16) % 256

key = 0x7f

for i in range(len(code_hex_values)):
    code_hex_values[i] ^= key
    key = genkey(key)

# Generate new lines with XOR-ed hex values
modified_code_lines = []
line_values = []
for i, value in enumerate(code_hex_values):
    if i % 10 == 0:
        if line_values:
            modified_code_lines.append(', '.join(line_values))
        line_values = []
    line_values.append(f"0x{value:02X}")
if line_values:
    modified_code_lines.append(', '.join(line_values))

# Insert the modified code lines within the structure
modified_lines = shellcode_lines[:start_index + 1]  # Include the line with the opening brace
modified_lines.extend(["  " + line + ",\n" for line in modified_code_lines])
modified_lines.extend(shellcode_lines[end_index:])

# Write modified lines back to shellcode_xor.h
with open('shellcode_xor.h', 'w') as f:
    f.writelines(modified_lines)

print("XOR operation completed. Output saved to shellcode_xor.h")
