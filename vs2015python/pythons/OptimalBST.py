def AIR(a, i, r):
    if r < i:
        return 0
    return a[i][r]

def ARJ(a, r, j):
    if r > j:
        return 0
    return a[r][j]

def SA(a, i, j):
    s = 0
    for k in range(i, j + 1, 1):
        s = s + a[k][k]
    return s

if __name__ == "__main__":
#    w = [5,40,8,4,10,10,23]
    w = [20, 5, 17, 10, 20, 3, 25]
    l = len(w)
    a = []
    for i in range(l):
        k = []
        for j in range(l):
            k.append(0)
        a.append(k)
        
    for i in range(l):
        a[i][i] = w[i]

    print(l)
    print()

    for s in range(1, l):
        for i in range(l):
            j = i + s
            if j >= l:
                break
            print(i, j)
            
            p = SA(a, i, j)
            m = []
            for k in range(i, j+1, 1):
                air = AIR(a, i, k-1)
                arj = ARJ(a, k+1,j)
                m.append(air + arj)
            mm = min(m)
            a[i][j] = p + mm;

            print()
    print("Optimal BST Weight:", a[0][l-1])
