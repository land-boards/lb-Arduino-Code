import scancode_list

lowcodes={}
hicodes={}
for entry in scancode_list.codes:
    lowcodes[entry[0]] = entry[1]
    hicodes[entry[0]] = entry[2]

lowcodelist = []
hicodelist= []
for i in range(128):
    if i in lowcodes:
        lowcodelist.append("'%s'" % lowcodes[i])
    else:
        lowcodelist.append("'?'")

    if i in hicodes:
        hicodelist.append("'%s'" % hicodes[i])                 
    else:
        hicodelist.append("'?'")

print "const char lkeymap[128] PROGMEM = {%s};" % ",".join(lowcodelist)
print "const char hkeymap[128] PROGMEM = {%s};" % ",".join(hicodelist)
