a = 65000000
b = 2345678
c = 99999999

a_seg = a//1000
b_seg = b//1000
c_seg = c//1000

#print(a_seg, b_seg, c_seg)

a_hour = a_seg//3600
b_hour = b_seg//3600
c_hour = c_seg//3600

#print(a_hour, b_hour, c_hour)

a_min = (a_seg%3600)//60
b_min = (b_seg%3600)//60
c_min = (c_seg%3600)//60

#print(a_min, b_min, c_min)

print(f'O evento A terá {a_hour}h {a_min}min e {(a_seg%3600)%60}segundos!')
print(f'O evento B terá {b_hour}h {b_min}min e {(b_seg%3600)%60}segundos!')
print(f'O evento C terá {c_hour}h {c_min}min e {(c_seg%3600)%60}segundos!')

segundos = b // 1000
horas = segundos // 3600
resto = segundos % 3600
minutos = resto // 60
segs = resto % 60
print(f'O evento terá {horas}h {minutos}min e {segs}segundos!!!')
