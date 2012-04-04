#!/usr/bin/python

def gen_matrix(x, y = 0):
    if y == 0:
        y = x
    type = "mat" + str(x)
    if x != y:
        type = type + "x" + str(y)
    print type + " matrixCompMult(" + type + " x, " + type + " y)\n{"
    print "    " + type + " z;"

    for i in range(x):
        print "    z[" + str(i) + "] = x[" + str(i) + "] * y[" + str(i) + "];"
    print "    return z;\n}"

print "#version 120"
# 1.10
gen_matrix(2)
gen_matrix(3)
gen_matrix(4)

# 1.20
gen_matrix(2,3) # mat2x3 means 2 columns, 3 rows
gen_matrix(3,2)
gen_matrix(2,4)
gen_matrix(4,2)
gen_matrix(3,4)
gen_matrix(4,3)
