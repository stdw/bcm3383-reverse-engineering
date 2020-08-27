import telnetlib

HOST = '192.168.100.1'
USER = b'technician'
PASS = b'abcd'

DEST = 0x80810000
FILE = './bin'

def main():
    t = telnetlib.Telnet(HOST)
    get(t, b'Login:')
    t.write(USER + b'\r\n')
    get(t, b'Password:')
    t.write(PASS + b'\r\n')
    if b'Console' in get(t, b'>'):
        authenticate(t)

    t.write(b'cd ..\r\n')
    if b'Scanning' in get(t, b'>'):
        stop_scan(t)

    upload_file(t, FILE, DEST)

    # execute function at start address
    #t.write(b'call func -r -a ' + bytes(hex(DEST), 'utf-8') + b'\r\n')
    #get(t, b'>')


# get/print output up to stop
def get(t, stop):
    output = t.read_until(stop)
    print(output.decode('latin-1'))
    return output

# get full permissions
def authenticate(t):
    t.write(b'su\r\n')
    get(t, b':')
    t.write(b'brcm\r\n')
    get(t, b'>')

# delete task that floods output
def stop_scan(t):
    t.write(b'taskShow\r\n')
    tasks = t.read_until(b'Scan Downstream')
    tasklist = tasks.split(b'\r\n')
    scantask = tasklist[-1].split(b' ')[0]
    
    t.write(b'taskDelete\r\n')
    get(t, b'Enter Task ID')
    t.write(scantask + b'\r\n')
    get(t, b'>')

# write file to RAM
def upload_file(t, filename, address):
    with open(filename, 'rb') as f:
        payload = f.read()
    
    dest = address
    for off in range(0, len(payload), 4):
        addr = hex(dest + off)
        val = payload[off:off+4].hex()
        cmd = bytes(f'write_memory -s 4 {addr} 0x{val}\r\n', 'utf-8')
        t.write(cmd)
        print(t.read_until(b'>'))


if __name__ == '__main__':
    main()
