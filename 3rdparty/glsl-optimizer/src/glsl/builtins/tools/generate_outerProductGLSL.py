#!/usr/bin/python

def gen(x, y):
    type = "mat" + str(x)
    if x != y:
        type = type + "x" + str(y)
    print type + " outerProduct(vec" + str(y) + " u, vec" + str(x) + " v)\n{"
    print "    " + type + " m;"

    for i in range(x):
        print "    m[" + str(i) + "] = u * v[" + str(i) + "];"
    print "    return m;\n}"

print "#version 120"
gen(2,2)
gen(2,3) # mat2x3 means 2 columns, 3 rows
gen(2,4)
gen(3,2)
gen(3,3)
gen(3,4)
gen(4,2)
gen(4,3)
gen(4,4)
