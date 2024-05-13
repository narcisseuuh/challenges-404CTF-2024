import random

def extract():
    l = []
    with open('shellcode1.h', 'r') as f:
        l.append(f.read().split('\n')[1:-3])
    with open ('shellcode2.h', 'r') as f:
        l.append(f.read().split('\n')[1:-3])
    with open('shellcode3.h', 'r') as f:
        l.append(f.read().split('\n')[1:-3])
    return l

def parse_integers(file):
    l = []
    for elem in file:
        nocomma = elem.split(',')
        for i in nocomma:
            if '\n' not in i and i != '':
                l.append(int(i, 16))
            elif i != '':
                l.append(int(i[:-1], 16))
    return l

def recreate_buffer(elements):
    res = '   '
    for i in range(len(elements)):
        res += hex(elements[i]) + ', '
        if i % 10 == 0 and i != 0:
            res += '\n   '
    return res

def write_to_file(files_packed):
    with open('shellcode_xor.h', 'w') as f:
        f.writelines(files_packed)
    
def find_0xcc(list):
    index = []
    for i in range(len(list)):
        if list[i] == 0xcc and list[i+1] == 0x90:
            index.append(i)
    return index

def align_shellcodes(shellcodes):
    indexes = [find_0xcc(elem) for elem in shellcodes]
    for i in range(len(indexes[0])):
        m = max(indexes[0][i], indexes[1][i], indexes[2][i])
        for j in range(len(shellcodes)):
            for _ in range(m - indexes[j][i]):
                shellcodes[j].insert(indexes[j][i], 0x90)
        indexes = [find_0xcc(elem) for elem in shellcodes]
    return shellcodes

def compute_distances(list):
    res = []
    for i in range(len(list) - 1):
        res.append(list[i+1] - list[i])
    return res

def xor_parts(shellcode, xor_keys):
    cces = find_0xcc(shellcode)
    res = []
    for i in range(len(shellcode)):
        if (i in cces):
            res.append(shellcode[i])
        else:
            res.append(shellcode[i] ^ xor_keys[i])
    return res

def main():
    files = extract()
    shellcodes = [parse_integers(elem) for elem in files]
    shellcodes = align_shellcodes(shellcodes)
    first_keys = [random.randint(0, 0xff) for _ in shellcodes[0]]
    last0xcc = find_0xcc(shellcodes[0])[-2]

    files_packed = ['unsigned char last_xor[] = {\n' + recreate_buffer(xor_parts(shellcodes[2][:last0xcc] + [elem ^ 0x90 for elem in shellcodes[2][last0xcc:]], shellcodes[1][:last0xcc] + [0 for _ in range(len(shellcodes[0]) - last0xcc)])) + '};\n']
    files_packed = ['unsigned char mid_xor[] = {\n' + recreate_buffer(xor_parts(shellcodes[1], shellcodes[0][:last0xcc] + [0 for _ in range(len(shellcodes[0]) - last0xcc)])) + '};\n'] + files_packed
    files_packed = ['unsigned char shellcode[] = {\n' + recreate_buffer(xor_parts(shellcodes[0], first_keys[:last0xcc] + [0 for _ in range(len(shellcodes[0]) - last0xcc)])) + '};\n'] + files_packed
    files_packed = ['unsigned char first_xor[] = {\n' + recreate_buffer(first_keys) + '};\n'] + files_packed
    files_packed.append('unsigned int shellcode_len = ' + str(len(first_keys)) + ';\n')
    files_packed.append('int offset[] = {' + recreate_buffer(find_0xcc(shellcodes[0])) + '};\n')
    files_packed.append('int lengthes[] = {' + recreate_buffer(compute_distances(find_0xcc(shellcodes[0]))) + '};')

    write_to_file(files_packed)

if __name__ == '__main__':
    main()