# python code for interfacing to VC0706 cameras and grabbing a photo
# pretty basic stuff
# written by ladyada. MIT license

import serial
import time

BAUD = 38400
PORT = "/dev/ttyACM0"
TIMEOUT = 0.1

SERIALNUM = 0    # start with 0

COMMANDSEND = 0x56
COMMANDREPLY = 0x76
COMMANDEND = 0x00

CMD_GETVERSION = 0x11
CMD_RESET = 0x26
CMD_TAKEPHOTO = 0x36
CMD_READBUFF = 0x32
CMD_GETBUFFLEN = 0x34

FBUF_CURRENTFRAME = 0x00
FBUF_NEXTFRAME = 0x01
FBUF_STOPCURRENTFRAME = 0x00

getversioncommand = [COMMANDSEND, SERIALNUM, CMD_GETVERSION, COMMANDEND]
resetcommand = [COMMANDSEND, SERIALNUM, CMD_RESET, COMMANDEND]
takephotocommand = [COMMANDSEND, SERIALNUM, CMD_TAKEPHOTO, 0x01, FBUF_STOPCURRENTFRAME]
getbufflencommand = [COMMANDSEND, SERIALNUM, CMD_GETBUFFLEN, 0x01, FBUF_CURRENTFRAME]
readphotocommand = [COMMANDSEND, SERIALNUM, CMD_READBUFF, 0x0c, FBUF_CURRENTFRAME, 0x0a]

def checkreply(r, b):
    r = map (ord, r)
    #print 'checkreply: completed  map, len=', len(r)
    #print 'r =', r
    if (r[0] == 0x76 and r[1] == SERIALNUM and r[2] == b and r[3] == 0x00):
        return True
    print 'checkReply(): failed, r=', r
    return False

def reset():
    cmd = ''.join (map (chr, resetcommand))
    # print 'reset() command ', 
    # print list(cmd)
    # print 'len command', len(cmd)
    s.flushInput()
    s.write(cmd)
    s.flush()
    reply = ''
    reply = s.read(100)
    r = list(reply)
    if checkreply(r, CMD_RESET):
        print 'reset: Successful'
        return True
    print 'reset(): failure, r=', r
    return False
        
def getversion():
    cmd = ''.join (map (chr, getversioncommand))
    s.write(cmd)
    reply =  s.read(16)
    r = list(reply);
    if checkreply(r, CMD_GETVERSION):
        return True
    return False

def takephoto():
    cmd = ''.join (map (chr, takephotocommand))
    s.write(cmd)
    reply =  s.read(5)
    r = list(reply);
    if (checkreply(r, CMD_TAKEPHOTO) and r[3] == chr(0x0)):
        return True
    return False   

def getbufferlength():
    cmd = ''.join (map (chr, getbufflencommand))
    s.write(cmd)
    reply =  s.read(9)
    r = list(reply);
    if (checkreply(r, CMD_GETBUFFLEN) and r[4] == chr(0x4)):
        l = ord(r[5])
        l <<= 8
        l += ord(r[6])
        l <<= 8
        l += ord(r[7])
        l <<= 8
        l += ord(r[8])
        return l
    return 0

READSIZE = 4096

def readbuffer(bytes):
    addr = 0
    photo = []
    
    while (addr < bytes + READSIZE):
        command = readphotocommand + [(addr >> 24) & 0xFF, (addr >> 16) & 0xFF,
                                      (addr >> 8) & 0xFF, addr & 0xFF]
        command +=  [(READSIZE>>24) & 0xFF, (READSIZE>>16) & 0xFF, (READSIZE>>8) & 0xFF, READSIZE & 0xFF]
        command +=  [0x10,0]        # delay of 40.96 ms (was 10 ms)
#        print 'cmd=', map(hex, command)
        cmd = ''.join(map (chr, command))
        s.write(cmd)
        # the reply is a 5-byte header, followed by the image data
        # followed by the 5-byte header again.        reply = s.read(5 + READSIZE + 5) # added the extra 5 to match "Gordon's code" on the adafruit site
        r = list(reply)
#        print r
        if (len(r) != READSIZE + 5):
            # print 'Receive count error'
            # print 'Command sent was: ', cmd
            # print 'r is:', r
            continue
        if (not checkreply(r, CMD_READBUFF)):
            print "ERROR READING PHOTO"
            exit()
        photo += r[5:]
        addr += READSIZE
    print 'photo len=', len(photo)
    return photo
    
######## main

s = serial.Serial(PORT, baudrate=BAUD, rtscts=False, timeout=TIMEOUT)

reset()

time.sleep(2)

if (not getversion()):
    print "Camera not found"
    exit
print "VC0706 Camera found"

if takephoto():
    print "Snap!"
    
bytes2read = getbufferlength()

print bytes2read, "bytes to read"

photo = readbuffer(bytes2read)

f = open("photo.jpg", 'w')
photodata = ''.join(photo)
f.write(photodata)
f.close()
#print length(photo)

