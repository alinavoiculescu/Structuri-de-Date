import time
import random

# SORTARI

# BubbleSort
def BubbleSort(v):
    n = len(v)
    for i in range(n-1):
        for j in range (n-i-1):
            if v[j] > v[j+1]:
                v[j], v[j+1] = v[j+1], v[j]
    return v



# CountingSort
def CountingSort(v):
    v_new = []
    freq = [0 for i in range (max(v) + 1)]
    for elem in v:
        freq[elem] += 1
    for i in range(len(freq)):
        for j in range(freq[i]):
            v_new.append(i)
    return v_new



# RadixSort_base10
def RadixSort_base10(v, poz_cif):
    v_new = []
    freq = [0 for i in range(10)]
    index1 = [-1 for i in range(10)]
    index2 = [-1 for i in range(10)]
    x = 10 ** (poz_cif + 1)
    i = -1
    for elem in v:
        i += 1
        cif = (elem % x) // (x // 10)
        freq[cif] += 1
        if index1[cif] == -1:
            index1[cif] = i
        index2[cif] = i
    for i in range(10):
        if freq[i] != 0:
            for j in range(index1[i], index2[i] + 1):
                if (v[j] % x) // (x // 10) == i:
                    v_new.append(v[j])
    for i in range(len(v)):
        v[i] = v_new[i]


# RadixSort_base2
def RadixSort_base2(v, poz_cif):
    v_new = []
    freq = [0 for i in range(2)]
    index1 = [-1 for i in range(2)]
    index2 = [-1 for i in range(2)]
    i = -1
    for elem in v:
        i += 1
        cif = (elem >> poz_cif) % 2
        freq[cif] += 1
        if index1[cif] == -1:
            index1[cif] = i
        index2[cif] = i
    for i in range(2):
        if freq[i] != 0:
            for j in range(index1[i], index2[i] + 1):
                if (v[j] >> poz_cif) % 2 == i:
                    v_new.append(v[j])
    for i in range(len(v)):
        v[i] = v_new[i]


# MergeSort
def MergeSort(v):
    if len(v) > 1:
        mij = len(v) // 2
        sol_st = v[:mij]
        sol_dr = v[mij:]
        MergeSort(sol_st)
        MergeSort(sol_dr)
        i = j = k = 0
        while i < len(sol_st) and j < len(sol_dr):
            if sol_st[i] < sol_dr[j]:
                v[k] = sol_st[i]
                i += 1
            else:
                v[k] = sol_dr[j]
                j += 1
            k += 1
        while i < len(sol_st):
            v[k] = sol_st[i]
            i += 1
            k += 1
        while j < len(sol_dr):
            v[k] = sol_dr[j]
            j += 1
            k += 1
    return v


# QuickSort_MedOfThree
def QuickSort_MedOfThree(v, first_idx, last_idx):
    pivot, piv_idx = Median_of_Three(v, first_idx, last_idx)
    i = first_idx
    j = last_idx
    while i <= j:
        if v[i] < pivot:
            i += 1
        elif v[j] > pivot:
            j -= 1
        elif i <= j:
            if v[i] > v[j]:
                v[i], v[j] = v[j], v[i]
            i += 1
            j -= 1
    if first_idx < j:
        QuickSort_MedOfThree(v, first_idx, j)
    if i < last_idx:
        QuickSort_MedOfThree(v, i, last_idx)
    return v


# QuickSort_MedOfFive
def QuickSort_MedOfFive(v, first_idx, last_idx):
    pivot, piv_idx = Median_of_Five(v, first_idx, last_idx)
    i = first_idx
    j = last_idx
    while i <= j:
        if v[i] < pivot:
            i += 1
        elif v[j] > pivot:
            j -= 1
        elif i <= j:
            if v[i] > v[j]:
                v[i], v[j] = v[j], v[i]
            i += 1
            j -= 1
    if first_idx < j:
        QuickSort_MedOfFive(v, first_idx, j)
    if i < last_idx:
        QuickSort_MedOfFive(v, i, last_idx)
    return v

def PythonSort(v):
    v.sort()
    return v

# Functie in plus:
def BucketSort(v):
    if len(v) == 1:
        return v
    else:
        val_max = max(v)
        if val_max == 0:
            val_max = 1
        nr = val_max / len(v)
        buckets = []
        for i in range(len(v)):
            buckets.append([])
        for i in range(len(v)):
            j = int (v[i] / nr)
            if j != len(v):
                buckets[j].append(v[i])
            else:
                buckets[len(v) - 1].append(v[i])
        for i in range(len(v)):
            buckets[i].sort()
        v_new = []
        for i in range(len(v)):
            v_new = v_new + buckets[i]
        return v_new





# FUNCTII AJUTATOARE

# Functie care afla numarul de cifre al celui mai mare numar din v
# (pentru RadixSort_base10)

def CifMax_base10(v):
    x = max(v)
    nr = 0
    while x != 0:
        nr += 1
        x = x//10
    return nr



# Functie care afla numarul de cifre al celui mai mare numar transformat in baza 2 din v
# (pentru RadixSort_base2)

def CifMax_base2(v):
    x = int(bin(max(v))[2:])
    nr = 0
    while x != 0:
        nr += 1
        x = x//10
    return nr



# Functie care afla pivotul, folosind mediana din 3
# (pentru QuickSort_MedOfThree)

def Median_of_Three(v, first_idx, last_idx):

    mij = (first_idx + last_idx + 1) // 2
    a = (v[first_idx], first_idx)
    b = (v[mij], mij)
    c = (v[last_idx], last_idx)
    return sorted([a, b, c])[1]



# Functie care afla pivotul, folosind mediana din 5
# (pentru QuickSort_MedOfFive)

def Median_of_Five(v, first_idx, last_idx):
    mij = (first_idx + last_idx + 1) // 2
    a = (v[first_idx], first_idx)
    b = (v[mij], mij)
    c = (v[last_idx], last_idx)
    d = (v[mij // 2], mij // 2)
    e = (v[(last_idx + 1 - mij) // 2 + mij], (last_idx + 1 - mij) // 2 + mij)
    return sorted([a, b, c, d, e])[2]


# Functie care verifica daca sortarea este corecta
def test_sort(v):
    for i in range(1, len(v)):
        if v[i-1] > v[i]:
            return 1
    return 0

# Functie care afiseaza RadixSort_base10
def RadixSort_b10(v):
    for i in range(CifMax_base10(v)):
        RadixSort_base10(v, i)
    return v

# Functie care afiseaza RadixSort_base2
def RadixSort_b2(v):
    for i in range(CifMax_base2(v)):
        RadixSort_base2(v, i)
    return v


# Functie care afiseaza QuickSort_MedOfThree
def QuickSort_MO3(v):
    return QuickSort_MedOfThree(v, 0, len(v) - 1)

# Functie care afiseaza QuickSort_MedOfThree
def QuickSort_MO5(v):
    return QuickSort_MedOfFive(v, 0, len(v) - 1)






# Aici incepe meniul interactiv, in care este inclusa si testarea algoritmilor.

nrTeste = int(input("Introduceti numarul de teste pe care doriti sa il efectuati:"))

teste = []

for i in range(0, nrTeste):
    print("Introduceti numarul de elemente pentru testul", i + 1)
    n = int(input("N = "))
    print("Introduceti numarul maxim din lista pe care o vom genera:")
    m = int(input("Max = "))
    teste.append([n,m])

sorts = [(BubbleSort, "BubbleSort"), (CountingSort, "CountingSort"), (RadixSort_b10, "Radix (base 10)"), (RadixSort_b2, "Radix (base 2)"), (MergeSort, "MergeSort"), (QuickSort_MO3, "QuickSort MedOfThree"), (QuickSort_MO5, "QuickSort MedOfFive"), (PythonSort, "Python Sort"), (BucketSort, "BucketSort")]

for i in range(0, nrTeste):
    teste[i].append([random.randint(0,teste[i][1]) for j in range(teste[i][0])])

for i in range(nrTeste):
    print()
    print()
    print("Testul", i + 1, "- format din", teste[i][0], "numere, avand elemente pana la numarul", teste[i][1], "inclusiv:")
    print()
    for sort, sort_name in sorts:
        timp_start = time.time()
        sort(teste[i][2])
        timp_end = time.time()
        if timp_end - timp_start > 3.00:
            print(sort_name, "a depasit cele 3 minute oferite pentru a sorta.")
        else:
            print(sort_name, ": ", timp_end - timp_start, "OK!" if test_sort(sort(teste[i][2])) == 0 else "WRONG!")
