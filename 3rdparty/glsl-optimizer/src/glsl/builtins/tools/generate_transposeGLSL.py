#!/usr/bin/python

def gen(x, y):
    origtype = "mat" + str(x)
    trantype = "mat" + str(y)
    if x != y:
        origtype = origtype + "x" + str(y)
        trantype = trantype + "x" + str(x)
    print trantype + " transpose(" + origtype + " m)\n{"
    print "    " + trantype + " t;"

    # The obvious implementation of transpose
    for i in range(x):
        for j in range(y):
            print "    t[" + str(j) + "][" + str(i) + "] =",
            print "m[" + str(i) + "][" + str(j) + "];"
    print "    return t;\n}"

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
